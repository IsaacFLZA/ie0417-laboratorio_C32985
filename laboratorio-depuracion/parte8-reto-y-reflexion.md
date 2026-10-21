# Partes 8 y 9: Mini reto de depuración y reflexión final

## Parte 8: Mini reto de depuración

### 1. Objetivo

Aplicar las herramientas y técnicas de depuración estudiadas durante el laboratorio para identificar y corregir diferentes errores presentes en un mismo programa de C++.

El programa contiene problemas de lógica, acceso a memoria y administración de memoria dinámica.

Para investigar estos problemas se utilizaron tres herramientas estudiadas previamente:

- GDB.
- Valgrind.
- AddressSanitizer.

El propósito es identificar las causas de los errores, aplicar las correcciones necesarias y comprobar que el programa finalmente produce los resultados esperados sin errores de memoria detectados.

---

### 2. Herramientas utilizadas

| Herramienta | Uso en el ejercicio |
|---|---|
| g++ | Compilar el programa original y el corregido |
| GDB | Inspeccionar variables y funciones |
| Valgrind | Detectar accesos inválidos y pérdidas de memoria |
| AddressSanitizer | Detectar el acceso fuera de los límites del arreglo |
| GitHub Codespaces | Ejecutar el laboratorio en un entorno Linux |

El entorno utilizado corresponde a Ubuntu 24.04.5 LTS, con g++ 13.3.0 y Valgrind 3.22.0.

---

### 3. Código original

Se creó el archivo:

`codigo/10_reto.cpp`

El código original fue:

```cpp
#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = 0;

    for (int i = 0; i <= tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return suma;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano]{-10, -20, -5, -30, -15};

    std::cout << "Mayor: " << obtener_mayor(datos, tamano) << std::endl;
    std::cout << "Promedio: " << calcular_promedio(datos, tamano) << std::endl;

    return 0;
}
```

Posteriormente, este código se conservó en el archivo:

`codigo/10_reto_original.cpp`

Esto permitió mantener una copia de la versión con errores mientras se realizaban las correcciones en `codigo/10_reto.cpp`.

---

### 4. Análisis inicial del programa

El programa trabaja con el siguiente arreglo:

```cpp
{-10, -20, -5, -30, -15}
```

Contiene cinco números enteros negativos.

La función `obtener_mayor()` debe identificar el valor más grande del arreglo.

La función `calcular_promedio()` debe calcular el promedio aritmético de sus elementos.

#### 4.1. Valor mayor esperado

Los elementos son:

```text
-10
-20
-5
-30
-15
```

El mayor es:

```text
-5
```

#### 4.2. Promedio esperado

La suma de los elementos es:

\[
-10-20-5-30-15=-80
\]

El promedio corresponde a:

\[
\frac{-80}{5}=-16
\]

Por lo tanto, la salida correcta debería ser:

```text
Mayor: -5
Promedio: -16
```

---

### 5. Compilación original

Se ejecutó:

```bash
g++ -g -O0 -o reto codigo/10_reto.cpp && echo "Compilacion exitosa"
```

Resultado obtenido:

```text
Compilacion exitosa
```

El programa compiló sin errores.

Esto demuestra que los problemas presentes no impedían generar el ejecutable.

Sin embargo, la compilación exitosa no garantizaba que el programa realizara los cálculos correctamente ni que utilizara adecuadamente la memoria.

---

### 6. Ejecución original

Se ejecutó:

```bash
./reto
```

Resultado:

```text
Mayor: 0
Promedio: -80
```

Se ejecutó por segunda vez:

```bash
./reto
```

Resultado:

```text
Mayor: 0
Promedio: -80
```

#### 6.1. Interpretación

El programa mostró resultados incorrectos.

El mayor debería ser `-5`, pero devolvió `0`.

El promedio debería ser `-16`, pero devolvió `-80`.

La salida también permitió observar que el programa aparentemente podía finalizar sin mostrar un error de ejecución, aunque posteriormente se comprobaría que contenía problemas relacionados con la memoria.

Era necesario investigar las causas de estos resultados.

---

### 7. Análisis del programa original con Valgrind

Se ejecutó:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./reto
```

Valgrind identificó dos problemas.

#### 7.1. Primer problema: lectura inválida

El reporte incluyó:

```text
==19731== Invalid read of size 4
==19731==    at 0x10925C: obtener_mayor(int*, int) (10_reto.cpp:7)
==19731==    by 0x1093C6: main (10_reto.cpp:29)
==19731==  Address 0x4e1f094 is 0 bytes after a block of size 20 alloc'd
```

Este mensaje indica que el programa intentó leer cuatro bytes fuera de un bloque de memoria válido.

El arreglo tiene cinco elementos enteros.

En este entorno, cada elemento ocupa cuatro bytes.

Por lo tanto, el arreglo ocupa:

\[
5 \times 4=20\text{ bytes}
\]

Valgrind indicó que la lectura se realizó inmediatamente después de esos 20 bytes.

El problema se encontraba en la condición del ciclo de la función `obtener_mayor()`:

```cpp
for (int i = 0; i <= tamano; i++)
```

Como `tamano` vale `5`, el ciclo también permite el valor `i = 5`.

Sin embargo, los índices válidos son únicamente:

```text
0, 1, 2, 3, 4
```

Por lo tanto, el programa intenta acceder a:

```cpp
datos[5]
```

Esta posición está fuera del arreglo.

#### 7.2. Segundo problema: pérdida de memoria

El reporte también indicó:

```text
==19731== HEAP SUMMARY:
==19731==     in use at exit: 20 bytes in 1 blocks
==19731==   total heap usage: 3 allocs, 2 frees, 74,772 bytes allocated
```

Posteriormente mostró:

```text
==19731== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
```

Y:

```text
==19731== LEAK SUMMARY:
==19731==    definitely lost: 20 bytes in 1 blocks
```

Finalmente:

```text
==19731== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

El programa reservaba memoria mediante:

```cpp
int* datos = new int[tamano]{-10, -20, -5, -30, -15};
```

Sin embargo, nunca ejecutaba:

```cpp
delete[] datos;
```

Por esta razón, Valgrind identificó una pérdida de memoria de 20 bytes.

#### 7.3. Evidencia guardada

Se ejecutó:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./reto > evidencia-reto-valgrind-original.txt 2>&1
```

El archivo guardado permitió conservar el reporte original.

Su resumen fue:

```text
==19878== Invalid read of size 4
==19878== 20 bytes in 1 blocks are definitely lost in loss record 1 of 1
==19878==    definitely lost: 20 bytes in 1 blocks
==19878== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

---

### 8. Análisis del programa original con AddressSanitizer

Se compiló utilizando:

```bash
g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer \
-o reto_asan codigo/10_reto.cpp \
&& echo "Compilacion con AddressSanitizer exitosa"
```

Resultado:

```text
Compilacion con AddressSanitizer exitosa
```

Posteriormente se ejecutó:

```bash
./reto_asan
```

#### 8.1. Resultado obtenido

AddressSanitizer reportó:

```text
==20404==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x503000000054
READ of size 4 at 0x503000000054 thread T0
```

El reporte señaló:

```text
#0 0x560793b2137a in obtener_mayor(int*, int) codigo/10_reto.cpp:7
#1 0x560793b216bd in main codigo/10_reto.cpp:29
```

También indicó:

```text
0x503000000054 is located 0 bytes after 20-byte region
```

Y concluyó:

```text
SUMMARY: AddressSanitizer: heap-buffer-overflow codigo/10_reto.cpp:7 in obtener_mayor(int*, int)
==20404==ABORTING
```

#### 8.2. Interpretación

AddressSanitizer detectó un acceso fuera de los límites de un bloque de memoria dinámica.

El error `heap-buffer-overflow` ocurrió al intentar leer una posición que no pertenecía al arreglo.

Esto confirmó el problema previamente identificado mediante Valgrind.

AddressSanitizer también señaló la función y línea responsables del acceso inválido.

#### 8.3. Evidencia guardada

Se ejecutó:

```bash
./reto_asan > evidencia-reto-asan-original.txt 2>&1
```

El reporte guardado confirmó:

```text
==20593==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x503000000054
SUMMARY: AddressSanitizer: heap-buffer-overflow codigo/10_reto.cpp:7 in obtener_mayor(int*, int)
==20593==ABORTING
```

El programa instrumentado fue detenido al detectarse el acceso inválido.

---

### 9. Análisis del programa original con GDB

También se utilizó GDB para investigar el error lógico de la función `obtener_mayor()`.

#### 9.1. Inicio de GDB

Se ejecutó:

```bash
gdb -q -iex "set debuginfod enabled off" ./reto
```

Resultado:

```text
Reading symbols from ./reto...
```

#### 9.2. Establecimiento de un breakpoint

Dentro de GDB se ejecutó:

```gdb
break obtener_mayor
```

Resultado:

```text
Breakpoint 1 at 0x1238: file codigo/10_reto.cpp, line 4.
```

Después:

```gdb
run
```

GDB detuvo el programa:

```text
Breakpoint 1, obtener_mayor (datos=0x55555556b2b0, tamano=5) at codigo/10_reto.cpp:4
4           int mayor = 0;
```

#### 9.3. Inspección del tamaño del arreglo

Se ejecutó:

```gdb
print tamano
```

Resultado:

```text
$1 = 5
```

Esto confirmó que el arreglo tenía cinco elementos.

#### 9.4. Inspección de la variable `mayor`

Primero se ejecutó:

```gdb
next
```

GDB avanzó hasta el ciclo:

```text
6           for (int i = 0; i <= tamano; i++) {
```

Después:

```gdb
print mayor
```

Resultado:

```text
$2 = 0
```

Esto confirmó que la función comenzaba la búsqueda utilizando el valor `0`.

Como todos los elementos del arreglo eran negativos, esa inicialización era incorrecta para este caso.

#### 9.5. Inspección de los elementos

Se ejecutaron:

```gdb
print datos[0]
print datos[1]
print datos[2]
print datos[3]
print datos[4]
```

Los resultados fueron:

```text
$3 = -10
$4 = -20
$5 = -5
$6 = -30
$7 = -15
```

Esto confirmó que todos los elementos eran negativos.

También permitió comprobar que el mayor era `-5`.

#### 9.6. Inspección de la pila de llamadas

Se ejecutó:

```gdb
backtrace
```

Resultado:

```text
#0  obtener_mayor (datos=0x55555556b2b0, tamano=5) at codigo/10_reto.cpp:6
#1  0x00005555555553c7 in main () at codigo/10_reto.cpp:29
```

El reporte mostró que `main()` había llamado a `obtener_mayor()`.

Este análisis permitió observar cómo se utilizaban las variables dentro de la función y confirmar la causa del resultado lógico incorrecto.

---

### 10. Identificación de los cuatro errores

Después de analizar el programa se identificaron cuatro problemas.

| Número | Tipo de error | Causa | Consecuencia |
|---|---|---|---|
| 1 | Lógico | Inicializar `mayor` en `0` | Resultado incorrecto para un arreglo de números negativos |
| 2 | Acceso inválido | Utilizar `i <= tamano` | Lectura fuera del arreglo |
| 3 | Lógico | Devolver `suma` en lugar del promedio | Resultado `-80` en lugar de `-16` |
| 4 | Memoria | No utilizar `delete[]` | Pérdida de 20 bytes |

#### Error 1. Inicialización incorrecta del mayor

Código original:

```cpp
int mayor = 0;
```

Esta inicialización falla cuando todos los valores del arreglo son negativos.

Como ninguno supera a cero, la función devuelve un valor que ni siquiera está presente en el arreglo.

#### Error 2. Acceso fuera del arreglo

Código original:

```cpp
for (int i = 0; i <= tamano; i++)
```

El ciclo intenta acceder al índice `tamano`, aunque el último índice válido es `tamano - 1`.

#### Error 3. Promedio incorrecto

Código original:

```cpp
return suma;
```

La función calcula correctamente la suma, pero no la divide entre la cantidad de elementos.

Por esa razón, muestra `-80` en lugar de `-16`.

#### Error 4. Pérdida de memoria

El programa utiliza:

```cpp
new int[tamano]
```

Pero termina sin liberar el arreglo.

Esto provoca una pérdida de memoria dinámica.

---

### 11. Correcciones aplicadas

Antes de modificar el programa se guardó el código original:

```bash
cp codigo/10_reto.cpp codigo/10_reto_original.cpp
```

Posteriormente se corrigió `codigo/10_reto.cpp`.

#### 11.1. Corrección del valor mayor

Antes:

```cpp
int mayor = 0;
```

Después:

```cpp
int mayor = datos[0];
```

Ahora el valor inicial pertenece al arreglo.

Además, el ciclo comienza en la posición `1`, ya que la primera posición se utilizó para inicializar `mayor`.

#### 11.2. Corrección del límite del ciclo

Antes:

```cpp
for (int i = 0; i <= tamano; i++)
```

Después:

```cpp
for (int i = 1; i < tamano; i++)
```

Con este cambio solamente se accede a las posiciones válidas.

#### 11.3. Corrección del promedio

Antes:

```cpp
return suma;
```

Después:

```cpp
return static_cast<double>(suma) / tamano;
```

La conversión a `double` permite efectuar una división apropiada para obtener un promedio con posibles decimales.

#### 11.4. Corrección de la pérdida de memoria

Se agregó:

```cpp
delete[] datos;
```

Esto permite liberar correctamente el arreglo dinámico después de utilizarlo.

---

### 12. Código corregido completo

El archivo final `codigo/10_reto.cpp` contiene:

```cpp
#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = datos[0];

    for (int i = 1; i < tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return static_cast<double>(suma) / tamano;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano]{-10, -20, -5, -30, -15};

    std::cout << "Mayor: " << obtener_mayor(datos, tamano) << std::endl;
    std::cout << "Promedio: " << calcular_promedio(datos, tamano) << std::endl;

    delete[] datos;

    return 0;
}
```

**Consideración:** La función `obtener_mayor()` corregida supone que el arreglo contiene al menos un elemento. Esto se cumple en el ejercicio porque `tamano = 5`. En una aplicación general convendría validar el tamaño antes de acceder a `datos[0]`.

---

### 13. Compilación del programa corregido

Se ejecutó:

```bash
g++ -g -O0 -o reto codigo/10_reto.cpp && echo "Compilacion corregida exitosa"
```

Resultado:

```text
Compilacion corregida exitosa
```

---

### 14. Ejecución del programa corregido

Se ejecutó:

```bash
./reto
```

Resultado:

```text
Mayor: -5
Promedio: -16
```

#### 14.1. Interpretación

Ambos resultados coinciden con los valores esperados.

El programa ahora identifica correctamente el mayor elemento del arreglo y calcula su promedio.

Esto confirma que los dos errores lógicos fueron corregidos para los datos utilizados en el ejercicio.

---

### 15. Verificación del programa corregido con Valgrind

Se ejecutó:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./reto
```

Resultado:

```text
==23362== Memcheck, a memory error detector
==23362== Using Valgrind-3.22.0 and LibVEX
==23362== Command: ./reto

Mayor: -5
Promedio: -16

==23362== HEAP SUMMARY:
==23362==     in use at exit: 0 bytes in 0 blocks
==23362==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated

==23362== All heap blocks were freed -- no leaks are possible

==23362== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

#### 15.1. Interpretación

El reporte confirmó que ya no existían bloques de memoria sin liberar al finalizar el programa.

Además, Valgrind no reportó accesos inválidos durante esta ejecución.

Esto indica que los errores de memoria identificados originalmente fueron corregidos.

#### 15.2. Evidencia guardada

Se ejecutó:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./reto > evidencia-reto-valgrind-corregido.txt 2>&1
```

El archivo guardado incluyó:

```text
==23554== All heap blocks were freed -- no leaks are possible
==23554== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

### 16. Verificación del programa corregido con AddressSanitizer

Se compiló:

```bash
g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer \
-o reto_asan codigo/10_reto.cpp \
&& echo "Compilacion corregida con AddressSanitizer exitosa"
```

Resultado:

```text
Compilacion corregida con AddressSanitizer exitosa
```

Posteriormente se ejecutó:

```bash
./reto_asan
```

Resultado:

```text
Mayor: -5
Promedio: -16
```

AddressSanitizer no reportó errores durante esta ejecución.

#### 16.1. Evidencia guardada

Se ejecutó:

```bash
./reto_asan > evidencia-reto-asan-corregido.txt 2>&1
```

El archivo contenía:

```text
Mayor: -5
Promedio: -16
```

Esto confirma que el programa corregido produjo los resultados esperados durante el análisis con AddressSanitizer.

---

### 17. Comparación antes y después de la corrección

| Característica | Programa original | Programa corregido |
|---|---|---|
| Compilación | Exitosa | Exitosa |
| Número mayor | `0` | `-5` |
| Promedio | `-80` | `-16` |
| Inicialización de `mayor` | `0` | `datos[0]` |
| Límite del ciclo | `i <= tamano` | `i < tamano` |
| Cálculo del promedio | Devuelve suma | Divide suma entre cantidad |
| Liberación de memoria | No | Sí |
| Valgrind | 2 errores | 0 errores |
| Memoria definitivamente perdida | 20 bytes | 0 bytes |
| AddressSanitizer | `heap-buffer-overflow` | Sin errores reportados |

---

### 18. Herramientas utilizadas y aportes

#### 18.1. GDB

Permitió inspeccionar:

- El tamaño del arreglo.
- La inicialización de la variable `mayor`.
- Los valores almacenados.
- La pila de llamadas.

Fue especialmente útil para comprender el error lógico de la función `obtener_mayor()`.

#### 18.2. Valgrind

Permitió identificar dos problemas:

- Una lectura fuera de los límites del arreglo.
- Una pérdida de memoria de 20 bytes.

También permitió comprobar que después de la corrección no se reportaron errores.

#### 18.3. AddressSanitizer

Permitió identificar el acceso inválido mediante el mensaje:

```text
heap-buffer-overflow
```

El reporte señaló la línea donde se produjo el problema.

Después de la corrección, el programa instrumentado se ejecutó sin reportar errores.

---

### 19. Evidencias guardadas

Durante la actividad se generaron los siguientes archivos:

| Archivo | Contenido |
|---|---|
| `codigo/10_reto_original.cpp` | Código original con errores |
| `codigo/10_reto.cpp` | Código corregido |
| `evidencia-reto-valgrind-original.txt` | Reporte original de Valgrind |
| `evidencia-reto-valgrind-corregido.txt` | Reporte de Valgrind después de corregir |
| `evidencia-reto-asan-original.txt` | Reporte original de AddressSanitizer |
| `evidencia-reto-asan-corregido.txt` | Ejecución corregida con AddressSanitizer |

Estos archivos permiten conservar las evidencias de los errores encontrados y de las soluciones aplicadas.

---

### 20. Conclusión de la Parte 8

Se completó correctamente el mini reto de depuración.

El programa original contenía cuatro errores: dos relacionados con la lógica, uno relacionado con un acceso inválido a memoria y otro relacionado con una pérdida de memoria dinámica.

La ejecución inicial mostró resultados incorrectos:

```text
Mayor: 0
Promedio: -80
```

Mediante GDB se identificó que la variable `mayor` estaba inicializada incorrectamente.

Valgrind detectó una lectura inválida y una pérdida de memoria de 20 bytes.

AddressSanitizer confirmó el acceso fuera de los límites mediante un reporte `heap-buffer-overflow`.

Después de aplicar las correcciones, el programa produjo:

```text
Mayor: -5
Promedio: -16
```

Además, Valgrind reportó cero errores y AddressSanitizer no reportó accesos inválidos durante la ejecución corregida.

Esta actividad permitió integrar los conocimientos adquiridos durante el laboratorio y comprobar la utilidad de combinar diferentes herramientas de depuración.

---

# Parte 9: Reflexión final del laboratorio

## 21. Objetivo

Reflexionar sobre los conceptos, herramientas y procedimientos estudiados durante el laboratorio de depuración de programas en C++.

Se busca identificar los conocimientos adquiridos y comprender cómo pueden aplicarse en el desarrollo de software.

---

## 22. Preguntas de reflexión final

### 1. ¿Qué es la depuración de programas?

La depuración es el proceso de identificar, analizar y corregir errores presentes en un programa.

Este proceso puede incluir la revisión del código fuente, la ejecución de pruebas, la inspección de variables y el uso de herramientas especializadas.

Durante el laboratorio se utilizaron GDB, Valgrind, AddressSanitizer, ThreadSanitizer y Helgrind para investigar diferentes tipos de errores.

La depuración es importante porque permite comprender las causas de los problemas y corregirlos de manera fundamentada, en lugar de realizar modificaciones sin conocer su origen.

### 2. ¿Por qué no es suficiente con que un programa compile correctamente?

Porque el compilador comprueba ciertos aspectos del programa, pero no garantiza que todas sus operaciones sean correctas durante la ejecución.

Un programa puede compilar y aun así contener errores lógicos, pérdidas de memoria, accesos inválidos o condiciones de carrera.

Durante el laboratorio se observaron varios ejemplos.

En la Parte 5, los programas compilaban correctamente, pero Valgrind detectó errores de memoria.

En la Parte 8, el programa también compilaba correctamente, aunque mostraba un mayor y un promedio incorrectos, además de contener problemas de memoria.

Por lo tanto, es necesario complementar la compilación con pruebas y herramientas de depuración.

### 3. ¿Cuál es la diferencia entre un error de sintaxis y un error lógico?

Un error de sintaxis ocurre cuando el código no cumple las reglas de escritura del lenguaje de programación.

Por ejemplo, olvidar un punto y coma puede impedir que el compilador genere el ejecutable.

Un error lógico ocurre cuando el programa puede ejecutarse, pero realiza operaciones incorrectas y produce resultados distintos a los esperados.

En la Parte 2 se corrigió un error de sintaxis relacionado con un punto y coma faltante.

También se corrigió un cálculo incorrecto del promedio.

En la Parte 8, inicializar el mayor en cero para un arreglo de números negativos fue otro ejemplo de error lógico.

### 4. ¿Qué ventaja ofrece GDB durante la depuración?

GDB permite detener la ejecución de un programa e inspeccionar su estado interno.

Entre sus funciones se encuentran establecer puntos de interrupción, ejecutar instrucciones paso a paso, consultar variables y analizar la pila de llamadas.

Durante el laboratorio fue útil para investigar la división entre cero de la Parte 4.

También permitió identificar la inicialización incorrecta de la variable `mayor` en la Parte 8.

Su principal ventaja es que permite comprender qué está ocurriendo dentro del programa en un momento determinado de la ejecución.

### 5. ¿Qué ventaja ofrece Valgrind?

Valgrind permite identificar problemas relacionados con el uso de memoria que pueden pasar desapercibidos durante una ejecución normal.

En el laboratorio permitió detectar pérdidas de memoria y accesos fuera de los límites de arreglos.

En la Parte 5 identificó una pérdida de 40 bytes y una escritura inválida.

En la Parte 8 detectó una lectura inválida y una pérdida de 20 bytes.

También permitió comprobar que los problemas habían sido corregidos.

Por esta razón, Valgrind es útil para mejorar la seguridad y confiabilidad de los programas.

### 6. ¿Qué ventaja ofrece AddressSanitizer?

AddressSanitizer permite detectar errores de acceso a memoria durante la ejecución de programas instrumentados.

Su principal ventaja es que genera reportes que identifican el tipo de problema y las líneas relacionadas.

En la Parte 6 detectó un error `heap-use-after-free`.

En la Parte 8 identificó un `heap-buffer-overflow`.

Estos reportes facilitaron la identificación de las operaciones incorrectas y permitieron aplicar correcciones específicas.

### 7. ¿Cuáles son algunos errores comunes relacionados con la memoria?

Entre los errores comunes se encuentran las pérdidas de memoria, los accesos fuera de los límites de un arreglo y el uso de memoria después de liberarla.

Una pérdida de memoria ocurre cuando se reserva memoria dinámica y no se libera correctamente.

Un acceso fuera de los límites ocurre cuando se intenta leer o escribir una posición que no pertenece al bloque reservado.

El error `use-after-free` ocurre cuando se intenta utilizar memoria que ya fue liberada.

Durante el laboratorio se estudiaron estos tres problemas mediante Valgrind y AddressSanitizer.

### 8. ¿Qué errores pueden ocurrir en programas concurrentes?

En los programas concurrentes pueden producirse condiciones de carrera, bloqueos mutuos y otros problemas de sincronización.

Una condición de carrera de datos ocurre cuando varios hilos acceden simultáneamente a una misma ubicación de memoria, al menos uno de esos accesos modifica los datos y no existe sincronización adecuada.

En la Parte 7, dos hilos incrementaban una variable global sin utilizar un mutex.

Esto produjo resultados diferentes entre ejecuciones.

La solución consistió en proteger el acceso al contador mediante `std::mutex` y `std::lock_guard`.

### 9. ¿Cuál fue el error más fácil de identificar durante el laboratorio?

El error de sintaxis relacionado con la ausencia de un punto y coma fue uno de los más fáciles de identificar.

Esto se debe a que el compilador mostró directamente un mensaje señalando el problema.

La corrección consistió en agregar el símbolo faltante.

A diferencia de los errores de memoria o concurrencia, no fue necesario realizar un análisis detallado de la ejecución.

Esto permitió comprobar que algunos errores se detectan rápidamente durante la compilación, mientras que otros requieren herramientas especializadas.

### 10. ¿Cuál fue el error más difícil de identificar?

Las condiciones de carrera fueron uno de los errores más difíciles de analizar.

Esto se debe a que sus efectos no aparecen necesariamente en todas las ejecuciones.

Durante la Parte 7, algunas ejecuciones mostraron el valor esperado de `200000`, mientras que otras produjeron resultados inferiores.

Además, ThreadSanitizer presentó dificultades de ejecución en GitHub Codespaces, por lo que fue necesario complementar el análisis con Helgrind.

Esta experiencia permitió comprender que los errores de concurrencia pueden depender de factores difíciles de reproducir.

### 11. Si un programa produce un valor incorrecto, ¿qué herramienta utilizaría primero?

Utilizaría primero GDB.

Esta herramienta permite detener la ejecución e inspeccionar las variables que intervienen en los cálculos.

También permite avanzar paso a paso para identificar dónde aparece un valor inesperado.

En la Parte 8, GDB permitió observar que la variable `mayor` estaba inicializada en cero, aunque todos los elementos del arreglo eran negativos.

Por esta razón, GDB sería una buena primera opción para investigar un resultado lógico incorrecto.

### 12. Si un programa presenta un error de segmentación, ¿qué herramienta utilizaría primero?

Utilizaría GDB para identificar el punto donde ocurre el fallo.

Mediante el comando `run` se puede ejecutar el programa y, cuando aparece el error, utilizar `backtrace` para revisar la pila de llamadas.

Esto permite localizar la función y la instrucción involucradas.

Si sospechara que el fallo está relacionado con accesos inválidos a memoria, complementaría el análisis utilizando AddressSanitizer o Valgrind.

La elección depende de la naturaleza del problema y de la información disponible.

### 13. Si sospecha que un programa tiene pérdidas de memoria, ¿qué herramienta utilizaría primero?

Utilizaría Valgrind con la herramienta Memcheck.

Esta herramienta permite identificar bloques de memoria que permanecen reservados al finalizar el programa.

Por ejemplo, se puede ejecutar:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./programa
```

Durante el laboratorio, este procedimiento permitió identificar pérdidas de 40 bytes y 20 bytes en diferentes ejercicios.

Valgrind también ayudó a comprobar que las pérdidas desaparecieron después de agregar las instrucciones de liberación correspondientes.

### 14. Si un programa utiliza varios hilos, ¿qué herramienta utilizaría para buscar problemas?

Utilizaría ThreadSanitizer o Helgrind.

Ambas herramientas permiten analizar problemas de concurrencia.

ThreadSanitizer se activa durante la compilación mediante:

```bash
-fsanitize=thread
```

Helgrind puede utilizarse mediante:

```bash
valgrind --tool=helgrind ./programa
```

En la Parte 7, ambas herramientas detectaron problemas en el programa original.

Después de corregirlo con un mutex, Helgrind no reportó errores no suprimidos.

Esto demostró la utilidad de estas herramientas para investigar accesos simultáneos a variables compartidas.

### 15. ¿Cómo aplicaría lo aprendido en futuros proyectos de programación?

Aplicaría los conocimientos adquiridos realizando pruebas frecuentes durante el desarrollo de los programas.

También utilizaría GDB cuando necesite comprender el estado interno de una aplicación o investigar resultados incorrectos.

En programas que utilicen memoria dinámica, emplearía herramientas como Valgrind y AddressSanitizer para detectar problemas relacionados con accesos inválidos y pérdidas de memoria.

Si desarrollo programas concurrentes, utilizaría mecanismos de sincronización adecuados y herramientas como ThreadSanitizer o Helgrind para analizar posibles condiciones de carrera.

Además, procuraría escribir código más seguro desde el inicio mediante validaciones de entrada, uso correcto de los límites de arreglos y administración adecuada de los recursos.

Estos conocimientos permitirán desarrollar programas más confiables y facilitarán la identificación de errores durante proyectos futuros.

---

## 23. Resumen de las herramientas estudiadas

| Herramienta | Propósito principal | Ejemplo del laboratorio |
|---|---|---|
| Compilador g++ | Detectar errores de compilación | Punto y coma faltante |
| GDB | Inspeccionar la ejecución | División entre cero y variables incorrectas |
| Valgrind | Detectar errores de memoria | Pérdidas y accesos inválidos |
| AddressSanitizer | Detectar errores de acceso a memoria | `heap-use-after-free` y `heap-buffer-overflow` |
| ThreadSanitizer | Detectar carreras de datos | Acceso concurrente a `contador` |
| Helgrind | Analizar problemas de concurrencia | Condición de carrera en dos hilos |

---

## 24. Aprendizajes obtenidos

Durante el laboratorio se reforzaron varios conceptos importantes.

**Primero**, se comprendió que los errores de programación pueden manifestarse de diferentes maneras.

Algunos impiden la compilación, mientras que otros solamente aparecen durante la ejecución.

**Segundo**, se aprendió a utilizar GDB para investigar el estado interno de los programas.

Esto incluyó el uso de puntos de interrupción, inspección de variables, ejecución paso a paso y análisis de pilas de llamadas.

**Tercero**, se comprobó que los errores de memoria pueden permanecer ocultos aunque los programas aparenten funcionar correctamente.

Valgrind y AddressSanitizer permitieron identificar estos problemas y verificar las correcciones.

**Cuarto**, se comprendió la importancia de sincronizar los accesos a memoria compartida en programas multihilo.

El uso de mutex permitió corregir una condición de carrera que generaba resultados inconsistentes.

**Finalmente**, el mini reto permitió aplicar varias herramientas sobre un mismo programa e integrar los conocimientos adquiridos.

---

## 25. Conclusión general del laboratorio

El laboratorio permitió conocer y utilizar diferentes herramientas para identificar, analizar y corregir errores en programas desarrollados en C++.

Se estudiaron errores de sintaxis, errores lógicos, errores de ejecución, pérdidas de memoria, accesos inválidos y condiciones de carrera.

Mediante GDB se aprendió a inspeccionar variables, utilizar puntos de interrupción y analizar la secuencia de llamadas de un programa.

Con Valgrind se identificaron problemas de memoria que no siempre producían fallos visibles.

AddressSanitizer permitió detectar accesos inválidos, incluyendo el uso de memoria después de liberarla y las lecturas fuera de los límites de arreglos.

También se utilizaron ThreadSanitizer y Helgrind para estudiar las condiciones de carrera en programas concurrentes.

Finalmente, en el mini reto se identificaron cuatro errores diferentes y se corrigieron satisfactoriamente.

El programa original producía:

```text
Mayor: 0
Promedio: -80
```

Después de la corrección produjo:

```text
Mayor: -5
Promedio: -16
```

Además, Valgrind y AddressSanitizer permitieron comprobar que los errores de memoria detectados originalmente habían desaparecido durante las ejecuciones de verificación.

En conclusión, la depuración es una parte fundamental del desarrollo de software, porque permite encontrar problemas que no siempre son evidentes mediante la lectura del código o la ejecución normal.

Los conocimientos adquiridos en este laboratorio serán útiles para desarrollar programas más correctos, seguros, confiables y fáciles de mantener.
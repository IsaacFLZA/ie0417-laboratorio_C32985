# Parte 6: AddressSanitizer

## 1. Objetivo

Utilizar AddressSanitizer para identificar y corregir errores de acceso a memoria en programas escritos en C++.

En esta actividad se analiza un programa que presenta un error conocido como `heap-use-after-free`, el cual ocurre cuando se intenta acceder a una región de memoria después de haberla liberado.

Se busca comparar el comportamiento del programa durante una ejecución normal y durante una ejecución utilizando AddressSanitizer.

Finalmente, se corregirá el error y se comprobará que el programa funciona correctamente.

---

## 2. Herramientas utilizadas

Para desarrollar el ejercicio se utilizaron las siguientes herramientas:

- **GitHub Codespaces:** entorno de desarrollo Linux en la nube.
- **g++:** compilador utilizado para generar los programas ejecutables.
- **AddressSanitizer (ASan):** herramienta utilizada para detectar accesos inválidos a memoria.
- **Terminal Linux:** utilizada para compilar, ejecutar y analizar los resultados.

Las versiones del entorno fueron:

| Herramienta | Versión |
|---|---|
| Sistema operativo | Ubuntu 24.04.5 LTS |
| g++ | 13.3.0 |
| Valgrind | 3.22.0 |

AddressSanitizer se habilitó mediante la opción `-fsanitize=address` del compilador.

---

## 3. Código original

Se creó el archivo:

`codigo/07_use_after_free.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    delete numero;

    std::cout << "Número: " << *numero << std::endl;

    return 0;
}
```

### 3.1. Explicación del programa

El programa comienza reservando memoria dinámica para almacenar un número entero:

```cpp
int* numero = new int;
```

Posteriormente, asigna el valor `42` a la dirección de memoria reservada:

```cpp
*numero = 42;
```

Después libera la memoria utilizando:

```cpp
delete numero;
```

Sin embargo, posteriormente intenta acceder nuevamente al contenido de esa dirección:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

Esto constituye un error porque el programa intenta utilizar memoria que ya fue liberada.

Este problema se conoce como `use-after-free`.

---

## 4. Compilación original sin AddressSanitizer

Se ejecutó el siguiente comando:

```bash
g++ -g -O0 -o use_after_free codigo/07_use_after_free.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

El programa compiló correctamente.

Esto demuestra que el compilador no identificó un error que impidiera generar el ejecutable.

Sin embargo, el código contenía un acceso inválido a memoria que podía provocar comportamiento indefinido durante su ejecución.

---

## 5. Ejecución original sin AddressSanitizer

Se ejecutó:

```bash
./use_after_free
```

### 5.1. Primera ejecución

El resultado obtenido fue:

```text
Número: -1435005129
```

### 5.2. Segunda ejecución

Se ejecutó nuevamente el mismo programa:

```bash
./use_after_free
```

El resultado obtenido fue:

```text
Número: -435883491
```

### 5.3. Análisis de los resultados

Los resultados obtenidos fueron diferentes entre las dos ejecuciones.

El programa originalmente almacenaba el valor `42`, pero después de liberar la memoria mostró valores distintos.

Esto ocurrió porque se intentó acceder a una región de memoria que ya había sido liberada.

Una vez ejecutada la instrucción:

```cpp
delete numero;
```

El puntero dejó de ser válido para acceder al objeto que anteriormente almacenaba.

Por lo tanto, la instrucción:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

produjo comportamiento indefinido.

Esto significa que el lenguaje C++ no garantiza cuál será el resultado de esa operación.

El programa podría mostrar un valor incorrecto, aparentar funcionar correctamente o terminar inesperadamente.

En este caso, las dos ejecuciones produjeron números diferentes, lo que permitió observar directamente un efecto del comportamiento indefinido.

---

## 6. Compilación con AddressSanitizer

Para detectar el problema se compiló el programa utilizando AddressSanitizer.

Se ejecutó:

```bash
g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer \
-o use_after_free_asan codigo/07_use_after_free.cpp \
&& echo "Compilacion con AddressSanitizer exitosa"
```

### Resultado obtenido

```text
Compilacion con AddressSanitizer exitosa
```

### 6.1. Explicación de las opciones utilizadas

| Opción | Función |
|---|---|
| `-g` | Incluye información de depuración |
| `-O0` | Desactiva las optimizaciones |
| `-fsanitize=address` | Habilita AddressSanitizer |
| `-fno-omit-frame-pointer` | Facilita la generación de trazas de llamadas |
| `-o use_after_free_asan` | Define el nombre del ejecutable |

AddressSanitizer permite detectar diferentes errores relacionados con el acceso a memoria durante la ejecución.

Entre ellos se encuentran los accesos fuera de los límites de arreglos y el uso de memoria después de haber sido liberada.

---

## 7. Ejecución original con AddressSanitizer

Se ejecutó:

```bash
./use_after_free_asan
```

### 7.1. Resultado obtenido

AddressSanitizer detectó el siguiente error:

```text
==4620==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010
READ of size 4 at 0x502000000010 thread T0
```

El reporte identificó la línea donde ocurrió el acceso:

```text
#0 0x5cd42a2a034d in main codigo/07_use_after_free.cpp:9
```

También indicó que la memoria había sido liberada previamente:

```text
freed by thread T0 here:
    #0 0x77350f24f5e8 in operator delete(void*, unsigned long)
    #1 0x5cd42a2a02f9 in main codigo/07_use_after_free.cpp:7
```

Y mostró dónde se había reservado originalmente:

```text
previously allocated by thread T0 here:
    #0 0x77350f24e548 in operator new(unsigned long)
    #1 0x5cd42a2a029e in main codigo/07_use_after_free.cpp:4
```

Finalmente, el reporte mostró:

```text
SUMMARY: AddressSanitizer: heap-use-after-free codigo/07_use_after_free.cpp:9 in main
==4620==ABORTING
```

### 7.2. Interpretación del reporte

AddressSanitizer identificó que el programa intentó leer una región de memoria después de haberla liberado.

El mensaje principal fue:

```text
heap-use-after-free
```

Esto significa que se intentó utilizar memoria dinámica que ya había sido liberada.

La siguiente línea indicó el tamaño del acceso inválido:

```text
READ of size 4
```

Esto significa que el programa intentó leer cuatro bytes de memoria.

En este caso, los cuatro bytes corresponden al tamaño de la variable de tipo `int` utilizada.

El reporte también mostró la dirección de memoria involucrada:

```text
0x502000000010
```

Esta dirección identificó el bloque de memoria donde ocurrió el problema durante esa ejecución.

---

## 8. Identificación de las líneas problemáticas

AddressSanitizer permitió identificar tres puntos importantes.

### 8.1. Reserva de memoria

El reporte señaló la línea 4:

```cpp
int* numero = new int;
```

Aquí se reservó memoria dinámica para almacenar un entero.

### 8.2. Liberación de memoria

El reporte señaló la línea 7:

```cpp
delete numero;
```

Aquí se liberó la memoria previamente reservada.

### 8.3. Acceso inválido

El reporte señaló la línea 9:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

Aquí se intentó leer el contenido de la memoria que ya había sido liberada.

### 8.4. Resumen

| Operación | Línea | Instrucción |
|---|---:|---|
| Reserva de memoria | 4 | `new int` |
| Asignación del valor | 5 | `*numero = 42` |
| Liberación de memoria | 7 | `delete numero` |
| Acceso inválido | 9 | `*numero` |

Esta información permitió identificar exactamente la causa del error.

---

## 9. Explicación de `heap-use-after-free`

Un error `heap-use-after-free` ocurre cuando un programa intenta utilizar una región de memoria dinámica después de que esta fue liberada.

En C++, es posible reservar memoria mediante `new` y liberarla mediante `delete`.

Sin embargo, después de liberar un objeto, ya no se debe acceder a él utilizando el puntero anterior.

En el programa original se ejecutaba:

```cpp
delete numero;
```

Y posteriormente:

```cpp
std::cout << "Número: " << *numero << std::endl;
```

Esta secuencia es incorrecta porque el objeto ya no existe.

El error es peligroso debido a que la memoria liberada puede ser reutilizada para otros datos.

Acceder a ella puede provocar resultados incorrectos, corrupción de memoria o fallos de ejecución.

AddressSanitizer permitió identificar el problema indicando la ubicación del acceso inválido y las operaciones de reserva y liberación relacionadas.

---

## 10. Evidencia adicional del error original

Para conservar el reporte se ejecutó:

```bash
./use_after_free_asan > evidencia-asan-original.txt 2>&1
```

Posteriormente se consultó el archivo utilizando:

```bash
cat evidencia-asan-original.txt
```

El reporte guardado volvió a confirmar el mismo problema.

Los principales resultados fueron:

```text
==4945==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010
READ of size 4 at 0x502000000010 thread T0
```

La ubicación del acceso inválido fue:

```text
#0 0x65135839734d in main codigo/07_use_after_free.cpp:9
```

La liberación de memoria se identificó mediante:

```text
freed by thread T0 here:
    #1 0x6513583972f9 in main codigo/07_use_after_free.cpp:7
```

La reserva original se identificó mediante:

```text
previously allocated by thread T0 here:
    #1 0x65135839729e in main codigo/07_use_after_free.cpp:4
```

Finalmente:

```text
SUMMARY: AddressSanitizer: heap-use-after-free codigo/07_use_after_free.cpp:9 in main
==4945==ABORTING
```

La segunda ejecución confirmó que el error podía detectarse de manera consistente mediante AddressSanitizer.

El archivo `evidencia-asan-original.txt` conserva el reporte completo generado durante el análisis.

---

## 11. Corrección realizada

Para solucionar el problema se modificó el orden de las instrucciones.

En el programa original se realizaba:

```cpp
delete numero;

std::cout << "Número: " << *numero << std::endl;
```

La corrección consistió en utilizar el valor almacenado antes de liberar la memoria.

El código corregido fue:

```cpp
std::cout << "Número: " << *numero << std::endl;

delete numero;
numero = nullptr;
```

### 11.1. Explicación

Primero se utiliza el contenido de la variable mientras la memoria todavía es válida.

Posteriormente, se libera la memoria mediante `delete`.

Finalmente, se asigna `nullptr` al puntero.

Esto permite indicar que el puntero ya no apunta al objeto anterior.

Es importante mencionar que asignar `nullptr` no libera memoria por sí mismo.

La liberación se realiza mediante `delete`.

Además, asignar `nullptr` únicamente modifica ese puntero; no impide que otros punteros que todavía apunten a la misma región de memoria puedan utilizarse incorrectamente.

---

## 12. Código corregido completo

El contenido final de `codigo/07_use_after_free.cpp` fue:

```cpp
#include <iostream>

int main() {
    int* numero = new int;
    *numero = 42;

    std::cout << "Número: " << *numero << std::endl;

    delete numero;
    numero = nullptr;

    return 0;
}
```

Este código corresponde a la corrección propuesta en el enunciado del laboratorio.

---

## 13. Compilación del programa corregido

Primero se realizó una compilación normal:

```bash
g++ -g -O0 -o use_after_free codigo/07_use_after_free.cpp \
&& echo "Compilacion normal exitosa"
```

### Resultado obtenido

```text
Compilacion normal exitosa
```

Después se compiló utilizando AddressSanitizer:

```bash
g++ -g -O0 -fsanitize=address -fno-omit-frame-pointer \
-o use_after_free_asan codigo/07_use_after_free.cpp \
&& echo "Compilacion con AddressSanitizer exitosa"
```

### Resultado obtenido

```text
Compilacion con AddressSanitizer exitosa
```

Ambas compilaciones se realizaron correctamente.

---

## 14. Ejecución del programa corregido sin AddressSanitizer

Se ejecutó:

```bash
./use_after_free
```

### Resultado obtenido

```text
Número: 42
```

El programa mostró correctamente el valor almacenado.

A diferencia de la versión original, ahora se accede al contenido de la memoria antes de liberarla.

---

## 15. Ejecución del programa corregido con AddressSanitizer

Se ejecutó:

```bash
./use_after_free_asan
```

### Resultado obtenido

```text
Número: 42
```

### 15.1. Análisis

El programa mostró correctamente el valor esperado.

Además, AddressSanitizer no generó ningún reporte de `heap-use-after-free`.

Esto permite confirmar que el acceso inválido detectado originalmente fue corregido.

El programa ya no intenta leer la memoria después de liberarla.

---

## 16. Comparación antes y después de la corrección

| Característica | Programa original | Programa corregido |
|---|---|---|
| Compilación normal | Exitosa | Exitosa |
| Acceso después de `delete` | Sí | No |
| Primera ejecución normal | `-1435005129` | `42` |
| Segunda ejecución normal | `-435883491` | `42` |
| Reporte de AddressSanitizer | `heap-use-after-free` | Sin errores reportados |
| Resultado final | Comportamiento indefinido | Resultado correcto |
| Asignación de `nullptr` | No | Sí |

La comparación demuestra que la corrección eliminó el acceso a memoria liberada.

También permite observar la diferencia entre detectar un problema mediante la ejecución normal y utilizar una herramienta especializada.

---

## 17. Comparación entre Valgrind y AddressSanitizer

Durante la Parte 5 se utilizó Valgrind para identificar pérdidas de memoria y accesos inválidos.

En esta parte se utilizó AddressSanitizer para identificar un acceso a memoria después de su liberación.

Ambas herramientas permiten analizar problemas relacionados con la memoria, pero presentan algunas diferencias.

| Característica | Valgrind | AddressSanitizer |
|---|---|---|
| Detección de accesos inválidos | Sí | Sí |
| Detección de memoria liberada utilizada nuevamente | Sí, mediante Memcheck | Sí |
| Detección de pérdidas de memoria | Sí | Puede realizarse mediante LeakSanitizer cuando está disponible |
| Forma de utilización | Ejecuta el programa bajo Valgrind | Requiere compilar con `-fsanitize=address` |
| Reportes | Información sobre bloques, accesos y pérdidas | Información sobre accesos, reservas y liberaciones |
| Impacto en ejecución | Generalmente mayor | Generalmente menor que Memcheck |

### 17.1. Diferencia observada en los ejercicios

En la Parte 5, Valgrind mostró reportes como:

```text
definitely lost: 40 bytes in 1 blocks
```

Y:

```text
Invalid write of size 4
```

En esta parte, AddressSanitizer mostró:

```text
ERROR: AddressSanitizer: heap-use-after-free
```

Además, identificó las líneas donde ocurrió la reserva de memoria, la liberación y el acceso inválido.

Ambas herramientas proporcionaron información útil para comprender y corregir los problemas.

---

## 18. Preguntas de reflexión

### 18.1. ¿Qué significa usar memoria después de liberarla?

Significa intentar acceder a una región de memoria dinámica después de haber ejecutado una operación que libera el objeto almacenado.

En C++, esto puede ocurrir cuando se utiliza un puntero después de llamar a `delete`.

En el ejercicio, el programa liberaba la memoria mediante:

```cpp
delete numero;
```

Pero posteriormente intentaba consultar su contenido mediante:

```cpp
*numero
```

Este comportamiento no es válido porque el objeto ya había sido destruido.

El problema se conoce como `use-after-free`.

### 18.2. ¿Por qué este error puede ser difícil de detectar sin herramientas?

Porque no siempre produce un fallo visible.

En algunos casos, el programa puede continuar ejecutándose y mostrar resultados aparentemente correctos.

En otros casos, puede mostrar valores incorrectos o terminar inesperadamente.

En este ejercicio, las ejecuciones normales produjeron dos números diferentes:

```text
Número: -1435005129
Número: -435883491
```

Aunque estos resultados indicaban que algo estaba mal, no permitían conocer directamente la causa.

AddressSanitizer identificó el acceso a memoria liberada y señaló la ubicación exacta del problema.

Por esta razón, las herramientas de análisis son importantes para detectar errores difíciles de identificar mediante la ejecución normal.

### 18.3. ¿Qué ventaja tiene AddressSanitizer sobre ejecutar el programa normalmente?

AddressSanitizer permite identificar errores de memoria que pueden pasar desapercibidos durante una ejecución convencional.

En este ejercicio, la ejecución normal mostró valores incorrectos, pero no explicó la causa.

En cambio, AddressSanitizer generó el reporte:

```text
ERROR: AddressSanitizer: heap-use-after-free
```

También mostró que el acceso inválido ocurrió en la línea 9, que la memoria se había liberado en la línea 7 y que originalmente se había reservado en la línea 4.

Esta información facilitó la identificación del problema y permitió aplicar una corrección específica.

### 18.4. ¿Qué diferencia observó entre el reporte de Valgrind y el reporte de AddressSanitizer?

En los ejercicios realizados con Valgrind se observaron reportes relacionados con pérdidas de memoria y accesos fuera de los límites de un arreglo.

Por ejemplo, Valgrind mostró:

```text
definitely lost: 40 bytes in 1 blocks
```

Y:

```text
Invalid write of size 4
```

Por otro lado, AddressSanitizer identificó un acceso a memoria liberada mediante:

```text
heap-use-after-free
```

El reporte de AddressSanitizer también mostró claramente dónde se reservó, liberó y utilizó incorrectamente la memoria.

Ambas herramientas proporcionaron información sobre los errores, pero los reportes observados se enfocaron en problemas diferentes debido a los ejercicios analizados.

En general, Valgrind puede utilizarse para realizar análisis detallados de memoria sin compilar específicamente con AddressSanitizer, mientras que AddressSanitizer requiere instrumentar el programa durante la compilación.

### 18.5. ¿Por qué es buena práctica asignar `nullptr` después de liberar un puntero?

Porque permite indicar explícitamente que el puntero ya no apunta a un objeto válido.

Después de liberar memoria mediante `delete`, el puntero conserva una dirección que ya no debe utilizarse para acceder al objeto anterior.

Al asignar:

```cpp
numero = nullptr;
```

Se evita conservar esa dirección en la variable.

Esto puede facilitar la identificación de errores y permite comprobar si el puntero es nulo antes de utilizarlo.

Sin embargo, asignar `nullptr` no libera memoria automáticamente ni garantiza que no existan otros punteros que conserven la dirección anterior.

Por lo tanto, debe considerarse una medida adicional de seguridad y no un reemplazo de una administración correcta de memoria.

---

## 19. Reflexión general

Esta actividad permitió comprender la importancia de administrar correctamente la memoria dinámica en C++.

El programa original compilaba correctamente, pero intentaba acceder a una región de memoria después de haberla liberado.

Durante las ejecuciones normales se observaron resultados incorrectos y diferentes, lo que evidenció que el comportamiento del programa no era confiable.

La utilización de AddressSanitizer permitió identificar claramente el problema y conocer las líneas donde se reservó, liberó y utilizó incorrectamente la memoria.

También se comprendió la utilidad de acceder a los datos antes de liberar los recursos y de asignar `nullptr` cuando un puntero deja de utilizarse.

Finalmente, se comprobó que la corrección permitió obtener el resultado esperado sin errores reportados por AddressSanitizer.

---

## 20. Conclusión

Se completó correctamente el ejercicio de análisis de memoria utilizando AddressSanitizer.

El programa original contenía un error `heap-use-after-free`, provocado por intentar leer una variable después de liberar su memoria dinámica.

Durante las ejecuciones normales se observaron valores incorrectos:

```text
Número: -1435005129
Número: -435883491
```

Posteriormente, AddressSanitizer identificó el problema mediante:

```text
ERROR: AddressSanitizer: heap-use-after-free
```

El reporte señaló que el acceso inválido ocurrió en la línea 9 del programa original.

Después de identificar la causa, se modificó el código para mostrar el valor antes de liberar la memoria y se asignó `nullptr` al puntero.

Finalmente, el programa corregido se compiló y ejecutó correctamente.

El resultado final fue:

```text
Número: 42
```

AddressSanitizer no reportó errores durante la ejecución corregida.

Esta actividad permitió comprender que una compilación exitosa no garantiza que un programa esté libre de problemas de memoria y demostró la utilidad de AddressSanitizer para identificar errores que pueden resultar difíciles de detectar mediante una ejecución normal.
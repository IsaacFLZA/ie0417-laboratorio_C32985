# Parte 5: Análisis de memoria con Valgrind

## 1. Objetivo

Utilizar Valgrind para identificar, analizar y corregir errores relacionados con la administración de memoria en programas escritos en C++.

Durante esta actividad se desarrollan dos ejercicios:

1. Identificación y corrección de una pérdida de memoria (*memory leak*).
2. Identificación y corrección de un acceso fuera de los límites de un arreglo (*invalid write*).

El propósito es comprender cómo algunos programas pueden compilar y ejecutarse aparentemente bien, aunque internamente presenten problemas de memoria.

Además, se busca aprender a interpretar los reportes de Valgrind y comprobar que los errores desaparecen después de aplicar las correcciones.

---

## 2. Herramientas utilizadas

Para realizar los ejercicios se utilizaron las siguientes herramientas:

- **GitHub Codespaces:** entorno de desarrollo Linux en la nube.
- **g++:** compilador utilizado para generar los ejecutables.
- **Valgrind:** herramienta utilizada para detectar errores de memoria.
- **Memcheck:** herramienta de Valgrind utilizada para identificar pérdidas de memoria y accesos inválidos.
- **Terminal Linux:** utilizada para ejecutar los comandos y observar los resultados.

Las versiones utilizadas fueron:

| Herramienta | Versión |
|---|---|
| Sistema operativo | Ubuntu 24.04.5 LTS |
| g++ | 13.3.0 |
| Valgrind | 3.22.0 |

Los programas se compilaron utilizando `-g` para incluir información de depuración y `-O0` para desactivar las optimizaciones del compilador.

---

# 3. Ejercicio 1: Pérdida de memoria

## 3.1. Objetivo

Identificar una pérdida de memoria en un programa que utiliza memoria dinámica mediante `new[]`.

Posteriormente, corregir el problema utilizando `delete[]` y verificar mediante Valgrind que la memoria se libera correctamente.

## 3.2. Código original

Se creó el archivo:

`codigo/05_memory_leak.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

void crear_arreglo() {
    int* datos = new int[10];

    for (int i = 0; i < 10; i++) {
        datos[i] = i * 2;
    }

    std::cout << "Primer elemento: " << datos[0] << std::endl;
}

int main() {
    crear_arreglo();
    return 0;
}
```

## 3.3. Explicación del programa

El programa contiene una función llamada `crear_arreglo()`.

Dentro de esta función se reserva memoria dinámica para diez números enteros mediante:

```cpp
int* datos = new int[10];
```

Posteriormente, se utiliza un ciclo `for` para almacenar números pares dentro del arreglo:

```cpp
for (int i = 0; i < 10; i++) {
    datos[i] = i * 2;
}
```

Finalmente, se muestra el primer elemento:

```cpp
std::cout << "Primer elemento: " << datos[0] << std::endl;
```

El problema es que el programa termina la función sin liberar la memoria reservada dinámicamente.

Esto provoca una pérdida de memoria.

## 3.4. Compilación del programa original

Se ejecutó el siguiente comando:

```bash
g++ -g -O0 -o memory_leak codigo/05_memory_leak.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

El programa compiló correctamente.

Esto demuestra que el compilador no identificó errores que impidieran generar el ejecutable.

Sin embargo, una compilación exitosa no garantiza que el programa administre correctamente la memoria.

## 3.5. Ejecución normal

Se ejecutó:

```bash
./memory_leak
```

### Resultado obtenido

```text
Primer elemento: 0
```

### Análisis

El programa mostró correctamente el primer elemento del arreglo.

Durante la ejecución normal no apareció ningún mensaje indicando que existiera una pérdida de memoria.

Esto demuestra que un programa puede producir el resultado esperado y, al mismo tiempo, presentar problemas internos relacionados con la administración de memoria.

Por esta razón, se utilizó Valgrind para realizar un análisis más detallado.

---

## 3.6. Análisis inicial con Valgrind

Se ejecutó el comando:

```bash
valgrind --leak-check=yes ./memory_leak
```

### Resultado obtenido

```text
==54775== Memcheck, a memory error detector
==54775== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==54775== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==54775== Command: ./memory_leak
==54775==

Primer elemento: 0

==54775== HEAP SUMMARY:
==54775==     in use at exit: 40 bytes in 1 blocks
==54775==   total heap usage: 3 allocs, 2 frees, 74,792 bytes allocated
==54775==

==54775== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==54775==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==54775==    by 0x1091BE: crear_arreglo() (05_memory_leak.cpp:4)
==54775==    by 0x10923E: main (05_memory_leak.cpp:14)
==54775==

==54775== LEAK SUMMARY:
==54775==    definitely lost: 40 bytes in 1 blocks
==54775==    indirectly lost: 0 bytes in 0 blocks
==54775==      possibly lost: 0 bytes in 0 blocks
==54775==    still reachable: 0 bytes in 0 blocks
==54775==         suppressed: 0 bytes in 0 blocks
==54775==

==54775== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

## 3.7. Interpretación del reporte

Valgrind identificó una pérdida de memoria.

La sección `HEAP SUMMARY` indicó:

```text
in use at exit: 40 bytes in 1 blocks
```

Esto significa que, cuando terminó el programa, todavía existían 40 bytes de memoria dinámica que no habían sido liberados.

El reporte también mostró:

```text
40 bytes in 1 blocks are definitely lost
```

Esto confirma que la memoria reservada dejó de estar accesible sin haber sido liberada.

La pérdida corresponde al arreglo creado mediante:

```cpp
int* datos = new int[10];
```

En este entorno, cada elemento de tipo `int` ocupa cuatro bytes.

Por lo tanto:

\[
10 \times 4 = 40 \text{ bytes}
\]

Esto coincide con la cantidad de memoria perdida reportada por Valgrind.

El reporte también identificó que la reserva se realizó dentro de la función `crear_arreglo()`.

## 3.8. ¿Qué significa `definitely lost`?

La expresión `definitely lost` significa que Valgrind encontró memoria reservada dinámicamente para la cual ya no existe un puntero que permita acceder al bloque al finalizar el programa.

En este caso, la memoria se reservó utilizando `new[]`, pero nunca se ejecutó una instrucción para liberarla.

Cuando terminó la función `crear_arreglo()`, el puntero local `datos` dejó de existir y la memoria asignada permaneció sin liberar.

Esta situación representa una pérdida de memoria.

---

## 3.9. Identificación de la causa del error

El problema se encontraba en la ausencia de una instrucción para liberar la memoria dinámica.

El programa reservaba memoria mediante:

```cpp
int* datos = new int[10];
```

Sin embargo, después de utilizar el arreglo, la función terminaba sin ejecutar:

```cpp
delete[] datos;
```

Por esta razón, la memoria permanecía reservada hasta la finalización del proceso.

## 3.10. Corrección realizada

Se agregó la siguiente instrucción al final de la función, después de utilizar el arreglo:

```cpp
delete[] datos;
```

La instrucción `delete[]` permite liberar la memoria que fue reservada mediante `new[]`.

De esta manera, el programa devuelve correctamente la memoria dinámica que ya no necesita.

---

## 3.11. Código corregido completo

El contenido final de `codigo/05_memory_leak.cpp` fue:

```cpp
#include <iostream>

void crear_arreglo() {
    int* datos = new int[10];

    for (int i = 0; i < 10; i++) {
        datos[i] = i * 2;
    }

    std::cout << "Primer elemento: " << datos[0] << std::endl;

    delete[] datos;
}

int main() {
    crear_arreglo();
    return 0;
}
```

La única modificación necesaria fue agregar la liberación de memoria.

---

## 3.12. Compilación después de la corrección

Se ejecutó:

```bash
g++ -g -O0 -o memory_leak codigo/05_memory_leak.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

## 3.13. Ejecución después de la corrección

Se ejecutó:

```bash
./memory_leak
```

### Resultado obtenido

```text
Primer elemento: 0
```

El programa continuó mostrando el mismo resultado.

Esto demuestra que la corrección no alteró su funcionamiento esperado.

---

## 3.14. Verificación final con Valgrind

Se ejecutó:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
```

### Resultado obtenido

```text
==56039== Memcheck, a memory error detector
==56039== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==56039== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==56039== Command: ./memory_leak
==56039==

Primer elemento: 0

==56039== HEAP SUMMARY:
==56039==     in use at exit: 0 bytes in 0 blocks
==56039==   total heap usage: 3 allocs, 3 frees, 74,792 bytes allocated
==56039==

==56039== All heap blocks were freed -- no leaks are possible

==56039== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Análisis

Después de aplicar la corrección, Valgrind confirmó:

```text
in use at exit: 0 bytes in 0 blocks
```

También mostró:

```text
All heap blocks were freed -- no leaks are possible
```

Esto significa que todos los bloques de memoria dinámica reservados durante la ejecución fueron liberados correctamente.

La sección `ERROR SUMMARY` indicó:

```text
0 errors from 0 contexts
```

Por lo tanto, se confirmó que la pérdida de memoria fue corregida.

## 3.15. Comparación de resultados

| Característica | Código original | Código corregido |
|---|---|---|
| Compilación | Exitosa | Exitosa |
| Ejecución | Correcta aparentemente | Correcta |
| Memoria perdida | 40 bytes | 0 bytes |
| Bloques sin liberar | 1 | 0 |
| Errores de Valgrind | 1 | 0 |
| Uso de `delete[]` | No | Sí |

---

## 3.16. Preguntas de reflexión

### 1. ¿Qué es una pérdida de memoria?

Una pérdida de memoria ocurre cuando un programa reserva memoria dinámica, pero no la libera después de utilizarla.

Esto provoca que la memoria permanezca ocupada innecesariamente.

En el ejercicio, la pérdida ocurrió porque se utilizó `new[]` para crear un arreglo, pero no se incluyó la instrucción `delete[]` para liberar la memoria.

Valgrind permitió comprobar que existían 40 bytes perdidos al finalizar el programa.

### 2. ¿Por qué el programa puede terminar aparentemente bien aunque tenga una pérdida de memoria?

Porque una pérdida de memoria no necesariamente afecta de forma inmediata las operaciones que realiza el programa.

En este caso, el programa podía acceder correctamente al arreglo, almacenar valores y mostrar el primer elemento.

El problema ocurría porque la memoria no se liberaba después de utilizarla.

Por esta razón, la ejecución normal mostraba el resultado esperado, aunque Valgrind identificó una pérdida de memoria.

Esto demuestra que obtener una salida correcta no significa que el programa esté libre de errores.

### 3. ¿Qué significa liberar memoria dinámica?

Liberar memoria dinámica significa devolver al sistema de administración de memoria un bloque que fue reservado durante la ejecución del programa.

En C++, cuando se utiliza `new` o `new[]`, es necesario administrar correctamente la memoria reservada.

En este ejercicio se utilizó:

```cpp
delete[] datos;
```

Esto permitió liberar el arreglo creado mediante `new[]`.

Liberar la memoria correctamente evita que permanezcan ocupados recursos que el programa ya no necesita.

### 4. ¿Por qué se usa `delete[]` y no solo `delete`?

Porque la memoria fue reservada para un arreglo utilizando `new[]`.

En C++ existe una correspondencia entre las operaciones de reserva y liberación:

- `new` debe utilizarse con `delete`.
- `new[]` debe utilizarse con `delete[]`.

Utilizar `delete` para liberar memoria reservada con `new[]` produce comportamiento indefinido.

Por esta razón, en este ejercicio era necesario utilizar `delete[] datos`.

### 5. ¿Qué tipo de problemas podrían aparecer en programas grandes si no se libera memoria?

En programas grandes, las pérdidas de memoria pueden provocar un aumento progresivo del consumo de recursos.

Esto puede ocasionar:

- Uso excesivo de memoria RAM.
- Disminución del rendimiento.
- Agotamiento de los recursos disponibles.
- Fallos al intentar reservar nueva memoria.
- Terminación inesperada del programa o del proceso.
- Problemas de estabilidad en aplicaciones que funcionan durante mucho tiempo.

Por esta razón, es importante administrar correctamente la memoria dinámica y utilizar herramientas como Valgrind para detectar posibles pérdidas.

## 3.17. Reflexión del ejercicio

Este ejercicio permitió comprender que un programa puede ejecutarse correctamente y aun así presentar pérdidas de memoria.

La herramienta Valgrind permitió identificar exactamente cuánta memoria no se había liberado y dónde se había realizado la reserva.

También se comprendió la importancia de utilizar `delete[]` cuando se reserva memoria para arreglos mediante `new[]`.

Después de aplicar la corrección, Valgrind confirmó que todos los bloques de memoria fueron liberados correctamente.

---

# 4. Ejercicio 2: Acceso fuera de los límites

## 4.1. Objetivo

Identificar un acceso inválido a memoria provocado por escribir fuera de los límites de un arreglo.

Utilizar Valgrind para localizar el problema, corregir el ciclo responsable y comprobar que desaparecen los errores de memoria.

---

## 4.2. Código original

Se creó el archivo:

`codigo/06_invalid_access.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    int* arreglo = new int[5];

    for (int i = 0; i <= 5; i++) {
        arreglo[i] = i * 10;
    }

    std::cout << "Programa finalizado" << std::endl;

    delete[] arreglo;

    return 0;
}
```

## 4.3. Explicación del programa

El programa reserva memoria dinámica para cinco números enteros:

```cpp
int* arreglo = new int[5];
```

Posteriormente, utiliza un ciclo `for` para almacenar valores dentro del arreglo:

```cpp
for (int i = 0; i <= 5; i++) {
    arreglo[i] = i * 10;
}
```

Finalmente, muestra un mensaje y libera la memoria:

```cpp
delete[] arreglo;
```

El problema se encuentra en la condición del ciclo.

El arreglo tiene espacio para cinco elementos, pero el ciclo intenta escribir seis.

---

## 4.4. Compilación del programa original

Se ejecutó:

```bash
g++ -g -O0 -o invalid_access codigo/06_invalid_access.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

El compilador generó correctamente el ejecutable.

No se identificaron errores de sintaxis que impidieran la compilación.

---

## 4.5. Ejecución normal

Se ejecutó:

```bash
./invalid_access
```

### Resultado obtenido

```text
Programa finalizado
```

### Análisis

El programa mostró el mensaje esperado y aparentemente terminó correctamente.

Sin embargo, el hecho de que no se produjera un fallo visible no significa que el programa haya utilizado correctamente la memoria.

En este caso existía un acceso fuera de los límites del arreglo que no fue detectado durante la ejecución normal.

Para identificarlo se utilizó Valgrind.

---

## 4.6. Análisis original con Valgrind

Se ejecutó:

```bash
valgrind --leak-check=full ./invalid_access
```

### Resultado obtenido

```text
==56999== Memcheck, a memory error detector
==56999== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==56999== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==56999== Command: ./invalid_access
==56999==

==56999== Invalid write of size 4
==56999==    at 0x1091ED: main (06_invalid_access.cpp:7)
==56999==  Address 0x4e1f094 is 0 bytes after a block of size 20 alloc'd
==56999==    at 0x48485C3: operator new[](unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==56999==    by 0x1091BE: main (06_invalid_access.cpp:4)
==56999==

Programa finalizado

==56999== HEAP SUMMARY:
==56999==     in use at exit: 0 bytes in 0 blocks
==56999==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==56999==

==56999== All heap blocks were freed -- no leaks are possible

==56999== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

---

## 4.7. Interpretación del reporte

Valgrind identificó el siguiente problema:

```text
Invalid write of size 4
```

Esto significa que el programa intentó escribir cuatro bytes en una dirección de memoria que no pertenecía al bloque reservado.

El reporte indicó:

```text
main (06_invalid_access.cpp:7)
```

Por lo tanto, el error se encontraba en la línea 7 del archivo fuente original.

Esa línea corresponde a:

```cpp
arreglo[i] = i * 10;
```

También se mostró:

```text
Address 0x4e1f094 is 0 bytes after a block of size 20 alloc'd
```

Esto significa que la escritura se realizó inmediatamente después del bloque de memoria reservado.

El arreglo contiene cinco enteros.

Como cada entero ocupa cuatro bytes en este entorno:

\[
5 \times 4 = 20 \text{ bytes}
\]

Por lo tanto, la memoria reservada tiene un tamaño de 20 bytes.

---

## 4.8. Identificación de la causa del error

La causa se encontraba en la condición del ciclo:

```cpp
for (int i = 0; i <= 5; i++)
```

El arreglo tiene cinco elementos, cuyos índices válidos son:

```text
0, 1, 2, 3, 4
```

Sin embargo, la condición `i <= 5` permite que el ciclo también se ejecute cuando `i` vale `5`.

Esto provoca un intento de escritura en:

```cpp
arreglo[5] = 50;
```

Esa posición se encuentra fuera del bloque de memoria reservado.

Por esta razón, Valgrind reportó un acceso inválido.

---

## 4.9. Corrección realizada

Se modificó la condición del ciclo.

Código original:

```cpp
for (int i = 0; i <= 5; i++) {
    arreglo[i] = i * 10;
}
```

Código corregido:

```cpp
for (int i = 0; i < 5; i++) {
    arreglo[i] = i * 10;
}
```

La modificación consistió en sustituir `<=` por `<`.

De esta manera, el ciclo solamente se ejecuta cuando `i` tiene valores entre `0` y `4`.

Esto evita escribir fuera de los límites del arreglo.

La corrección se realizó mediante:

```bash
sed -i 's/i <= 5/i < 5/' codigo/06_invalid_access.cpp
```

---

## 4.10. Código corregido completo

El contenido final de `codigo/06_invalid_access.cpp` fue:

```cpp
#include <iostream>

int main() {
    int* arreglo = new int[5];

    for (int i = 0; i < 5; i++) {
        arreglo[i] = i * 10;
    }

    std::cout << "Programa finalizado" << std::endl;

    delete[] arreglo;

    return 0;
}
```

---

## 4.11. Compilación después de la corrección

Se ejecutó:

```bash
g++ -g -O0 -o invalid_access codigo/06_invalid_access.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

---

## 4.12. Ejecución después de la corrección

Se utilizó:

```bash
./invalid_access
```

### Resultado obtenido

```text
Programa finalizado
```

El programa continuó mostrando el mismo mensaje que antes de la corrección.

Sin embargo, ahora el ciclo solamente escribe dentro de las posiciones válidas del arreglo.

---

## 4.13. Verificación final con Valgrind

Se ejecutó:

```bash
valgrind --leak-check=full ./invalid_access
```

### Resultado obtenido

```text
==57911== Memcheck, a memory error detector
==57911== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==57911== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==57911== Command: ./invalid_access
==57911==

Programa finalizado

==57911== HEAP SUMMARY:
==57911==     in use at exit: 0 bytes in 0 blocks
==57911==   total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated
==57911==

==57911== All heap blocks were freed -- no leaks are possible

==57911== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Análisis

Después de corregir la condición del ciclo, Valgrind no detectó accesos inválidos a memoria.

La sección final indicó:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

Esto demuestra que el error detectado originalmente desapareció.

Además, el reporte indicó:

```text
All heap blocks were freed -- no leaks are possible
```

Esto confirma que el programa también liberó correctamente los bloques de memoria dinámica.

---

## 4.14. Comparación antes y después de la corrección

| Característica | Código original | Código corregido |
|---|---|---|
| Compilación | Exitosa | Exitosa |
| Ejecución normal | Programa finalizado | Programa finalizado |
| Condición del ciclo | `i <= 5` | `i < 5` |
| Acceso a `arreglo[5]` | Sí | No |
| Error `Invalid write` | Detectado | No detectado |
| Errores reportados | 1 | 0 |
| Pérdidas de memoria | 0 bytes | 0 bytes |

---

## 4.15. Preguntas de reflexión

### 1. ¿Por qué el programa podría no fallar aunque acceda fuera del arreglo?

Porque acceder fuera de los límites de un arreglo produce comportamiento indefinido.

Esto significa que el lenguaje C++ no garantiza qué ocurrirá cuando se realice esa operación.

En algunos casos, el programa puede continuar ejecutándose aparentemente bien.

En otros casos, puede mostrar resultados incorrectos, modificar memoria que pertenece a otros datos o terminar inesperadamente.

En este ejercicio, el programa mostró `Programa finalizado` a pesar de realizar una escritura inválida.

Sin embargo, Valgrind permitió detectar el problema.

### 2. ¿Qué significa escribir fuera de los límites de un arreglo?

Significa intentar almacenar información en una posición que no pertenece al espacio de memoria reservado para ese arreglo.

En este ejercicio se creó un arreglo de cinco elementos:

```cpp
int* arreglo = new int[5];
```

Sus índices válidos eran del `0` al `4`.

Sin embargo, el ciclo original también intentaba escribir en `arreglo[5]`.

Esto representaba una escritura fuera de los límites del arreglo.

### 3. ¿Por qué este tipo de error es peligroso?

Es peligroso porque puede provocar corrupción de memoria y comportamientos inesperados.

Por ejemplo, una escritura fuera de los límites puede modificar datos que pertenecen a otras estructuras o componentes del programa.

También puede generar fallos difíciles de reproducir y problemas de seguridad.

Además, estos errores no siempre producen mensajes visibles, por lo que pueden permanecer ocultos durante las pruebas normales.

Por esta razón, es importante verificar los límites de los arreglos y utilizar herramientas que permitan detectar accesos inválidos.

### 4. ¿Qué diferencia hay entre un error visible y un comportamiento indefinido?

Un error visible es un problema que produce una manifestación observable, como un mensaje de error, un resultado incorrecto o la terminación inesperada del programa.

El comportamiento indefinido ocurre cuando el programa realiza una operación para la cual el lenguaje no establece un resultado garantizado.

Un comportamiento indefinido puede producir un error visible, pero también puede permitir que el programa continúe aparentemente bien.

En este ejercicio, la escritura fuera del arreglo produjo comportamiento indefinido, aunque la ejecución normal mostró el mensaje esperado.

Valgrind permitió identificar el acceso inválido que no había sido evidente durante la ejecución normal.

---

## 4.16. Reflexión del ejercicio

Este ejercicio permitió comprender la importancia de respetar los límites de los arreglos en C++.

Aunque el programa parecía funcionar correctamente, Valgrind identificó una escritura inválida que podía provocar problemas de memoria.

También se comprendió que los índices de un arreglo comienzan en cero y que, para un arreglo de cinco elementos, el último índice válido es cuatro.

La corrección consistió en modificar la condición del ciclo para evitar acceder a una posición fuera del arreglo.

Después de realizar el cambio, Valgrind confirmó que el error había desaparecido.

---

# 5. Comparación de los errores analizados

Durante esta parte se identificaron dos problemas diferentes relacionados con la memoria.

| Característica | Pérdida de memoria | Acceso fuera de límites |
|---|---|---|
| Archivo | `05_memory_leak.cpp` | `06_invalid_access.cpp` |
| Problema | Memoria no liberada | Escritura fuera del arreglo |
| Reporte de Valgrind | `definitely lost` | `Invalid write` |
| Causa | Ausencia de `delete[]` | Condición incorrecta en el ciclo |
| Corrección | Agregar `delete[] datos` | Cambiar `i <= 5` por `i < 5` |
| Errores iniciales | 1 | 1 |
| Errores finales | 0 | 0 |

Ambos programas compilaban correctamente y producían una salida aparentemente normal.

Sin embargo, Valgrind permitió identificar errores internos que no eran evidentes durante la ejecución convencional.

---

# 6. Evidencias generales de la Parte 5

## 6.1. Pérdida de memoria

**Comando utilizado:**

```bash
valgrind --leak-check=yes ./memory_leak
```

**Resultado original:**

```text
HEAP SUMMARY:
    in use at exit: 40 bytes in 1 blocks
    total heap usage: 3 allocs, 2 frees, 74,792 bytes allocated

LEAK SUMMARY:
    definitely lost: 40 bytes in 1 blocks

ERROR SUMMARY: 1 errors from 1 contexts
```

**Resultado después de corregir:**

```text
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
    total heap usage: 3 allocs, 3 frees, 74,792 bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
```

## 6.2. Acceso fuera de límites

**Comando utilizado:**

```bash
valgrind --leak-check=full ./invalid_access
```

**Resultado original:**

```text
Invalid write of size 4
   at 0x1091ED: main (06_invalid_access.cpp:7)

Address 0x4e1f094 is 0 bytes after a block of size 20 alloc'd

ERROR SUMMARY: 1 errors from 1 contexts
```

**Resultado después de corregir:**

```text
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
    total heap usage: 3 allocs, 3 frees, 74,772 bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
```

---

# 7. Reflexión general

Esta actividad permitió comprender que los problemas relacionados con la memoria pueden permanecer ocultos durante la ejecución normal de un programa.

En el primer ejercicio se identificó una pérdida de memoria que no afectaba directamente el resultado mostrado en pantalla.

En el segundo ejercicio se detectó un acceso fuera de los límites de un arreglo, aunque el programa aparentemente finalizaba correctamente.

El uso de Valgrind permitió identificar ambos problemas y obtener información sobre sus causas.

También se comprendió la importancia de liberar correctamente la memoria dinámica y verificar los límites de los arreglos.

Finalmente, se confirmó que las correcciones realizadas eliminaron los errores reportados.

---

# 8. Conclusión

Se completaron correctamente los dos ejercicios de análisis de memoria utilizando Valgrind.

En el primer ejercicio se identificó una pérdida de memoria de 40 bytes causada por no liberar un arreglo creado mediante `new[]`.

La corrección consistió en agregar `delete[] datos`, después de lo cual Valgrind confirmó que no existían bloques de memoria sin liberar.

En el segundo ejercicio se identificó una escritura inválida de cuatro bytes provocada por una condición incorrecta en un ciclo.

La corrección consistió en modificar el ciclo para que únicamente accediera a las posiciones válidas del arreglo.

Después de aplicar ambas correcciones, los reportes de Valgrind mostraron:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

Esto permitió comprobar que los problemas detectados inicialmente habían sido corregidos.

La actividad demostró la importancia de utilizar herramientas de análisis de memoria y confirmó que una compilación y ejecución exitosas no garantizan que un programa esté libre de errores.

Los conocimientos adquiridos serán útiles para desarrollar programas más seguros, estables y eficientes en el uso de memoria.
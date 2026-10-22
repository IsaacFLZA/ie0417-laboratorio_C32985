# Laboratorio de depuración de programas en C++

**Curso:** IE0417  
**Repositorio:** [ie0417-laboratorio_C32985](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985)  
**Entorno de desarrollo:** GitHub Codespaces (Ubuntu 24.04.5 LTS)  
**Lenguaje:** C++  

---

## 1. Descripción

Este laboratorio tiene como objetivo aprender a identificar, analizar y corregir errores en programas desarrollados en C++ mediante diferentes herramientas de depuración.

Durante las actividades se estudian errores de sintaxis, errores lógicos, problemas de ejecución, pérdidas de memoria, accesos inválidos y condiciones de carrera en programas concurrentes.

Para realizar los ejercicios se utilizaron herramientas como GDB, Valgrind, AddressSanitizer, ThreadSanitizer y Helgrind.

Cada parte incluye explicaciones, comandos utilizados, resultados obtenidos, correcciones y respuestas a las preguntas de reflexión correspondientes.

---

## 2. Objetivos

### Objetivo general

Desarrollar habilidades de depuración de programas en C++ mediante el uso de herramientas especializadas que permitan identificar y corregir diferentes tipos de errores.

### Objetivos específicos

- Reconocer las diferencias entre errores de sintaxis, errores lógicos y errores de ejecución.
- Utilizar GDB para inspeccionar variables, establecer puntos de interrupción y analizar llamadas a funciones.
- Identificar pérdidas de memoria y accesos inválidos mediante Valgrind.
- Detectar errores de acceso a memoria mediante AddressSanitizer.
- Analizar condiciones de carrera utilizando ThreadSanitizer y Helgrind.
- Aplicar mecanismos de sincronización mediante `std::mutex` y `std::lock_guard`.
- Comprobar que las correcciones eliminan los errores identificados.
- Documentar los resultados y reflexionar sobre la importancia de la depuración.

---

## 3. Herramientas utilizadas

| Herramienta | Versión o característica | Propósito |
|---|---|---|
| Ubuntu | 24.04.5 LTS | Sistema operativo |
| g++ | 13.3.0 | Compilación de programas C++ |
| GDB | 15.1 | Depuración paso a paso |
| Valgrind | 3.22.0 | Detección de errores de memoria |
| AddressSanitizer | `-fsanitize=address` | Detección de accesos inválidos |
| ThreadSanitizer | `-fsanitize=thread` | Análisis de condiciones de carrera |
| Helgrind | `valgrind --tool=helgrind` | Análisis de concurrencia |
| GitHub Codespaces | Entorno Linux en la nube | Desarrollo y ejecución |
| Git y GitHub | Control de versiones | Almacenamiento de archivos y evidencias |

---

## 4. Contenido del laboratorio

El laboratorio se divide en nueve partes.

| Parte | Tema | Documentación |
|---|---|---|
| 1 | Instalación y verificación de herramientas | [Parte 1](parte1-instalacion.md) |
| 2 | Errores de sintaxis y errores lógicos | [Parte 2](parte2-tipos-errores.md) |
| 3 | Introducción a GDB | [Parte 3](parte3-gdb-basico.md) |
| 4 | Uso de `step`, `next` y `backtrace` | [Parte 4](parte4-gdb-funciones.md) |
| 5 | Análisis de memoria con Valgrind | [Parte 5](parte5-valgrind.md) |
| 6 | Detección de errores con AddressSanitizer | [Parte 6](parte6-asan.md) |
| 7 | Condiciones de carrera y sincronización | [Parte 7](parte7-hilos.md) |
| 8 | Mini reto de depuración | [Parte 8](parte8-reto-y-reflexion.md) |
| 9 | Reflexión final | [Parte 9](parte8-reto-y-reflexion.md#parte-9-reflexión-final-del-laboratorio) |

**Nota:** Las partes 8 y 9 se encuentran documentadas en el mismo archivo Markdown.

---

## 5. Descripción de las actividades

### Parte 1: Instalación y verificación

Se verificó la disponibilidad de las herramientas necesarias para realizar el laboratorio.

Se comprobó el funcionamiento de:

- Compilador g++.
- Depurador GDB.
- Valgrind.
- Entorno Linux.

También se compiló y ejecutó un programa sencillo de prueba.

**Documentación:** [parte1-instalacion.md](parte1-instalacion.md)

### Parte 2: Errores de sintaxis y errores lógicos

Se analizaron dos tipos de errores.

**Error de sintaxis:** un programa que no compilaba debido a la ausencia de un punto y coma.

**Error lógico:** un programa que calculaba incorrectamente el promedio de un conjunto de notas.

Se comprobó que los errores de sintaxis pueden impedir la compilación, mientras que los errores lógicos pueden producir resultados incorrectos aunque el programa compile.

**Documentación:** [parte2-tipos-errores.md](parte2-tipos-errores.md)

### Parte 3: Introducción a GDB

Se utilizaron los comandos básicos del depurador GDB para analizar un programa.

Entre las operaciones realizadas se encuentran:

- Establecer puntos de interrupción.
- Ejecutar el programa dentro del depurador.
- Inspeccionar variables.
- Avanzar por las instrucciones.
- Finalizar una sesión de depuración.

**Documentación:** [parte3-gdb-basico.md](parte3-gdb-basico.md)

### Parte 4: Depuración de funciones

Se analizó un programa que intentaba realizar una división entre cero.

Se utilizaron los comandos:

```gdb
break main
run
next
step
print
backtrace
```

GDB permitió identificar que la función `dividir()` recibía un divisor igual a cero.

Posteriormente, se agregó una validación para evitar la operación inválida.

**Documentación:** [parte4-gdb-funciones.md](parte4-gdb-funciones.md)

### Parte 5: Análisis de memoria con Valgrind

Se realizaron dos ejercicios.

**Ejercicio 1: Pérdida de memoria**

Valgrind identificó 40 bytes de memoria dinámica que no habían sido liberados.

La corrección consistió en utilizar:

```cpp
delete[] datos;
```

**Ejercicio 2: Acceso fuera de los límites**

Valgrind identificó una escritura fuera de un arreglo mediante:

```text
Invalid write of size 4
```

La corrección consistió en modificar la condición del ciclo para respetar los índices válidos.

Después de las correcciones, ambos programas produjeron reportes de Valgrind con cero errores.

**Documentación:** [parte5-valgrind.md](parte5-valgrind.md)

### Parte 6: AddressSanitizer

Se analizó un error conocido como `heap-use-after-free`.

El programa original intentaba acceder a memoria dinámica después de haberla liberado.

AddressSanitizer permitió identificar las líneas donde se reservó, liberó y utilizó incorrectamente la memoria.

La corrección consistió en acceder al valor antes de liberar la memoria y posteriormente asignar `nullptr` al puntero.

**Documentación:** [parte6-asan.md](parte6-asan.md)

### Parte 7: Condiciones de carrera

Se desarrolló un programa con dos hilos que incrementaban una variable global compartida.

Debido a la falta de sincronización, algunas ejecuciones mostraron resultados diferentes del valor esperado de `200000`.

ThreadSanitizer y Helgrind permitieron detectar condiciones de carrera en el programa original.

La corrección consistió en utilizar:

```cpp
std::mutex mtx;
```

Y:

```cpp
std::lock_guard<std::mutex> lock(mtx);
```

Después de aplicar la corrección, Helgrind no reportó errores no suprimidos.

**Observación:** ThreadSanitizer presentó problemas de ejecución relacionados con el entorno de GitHub Codespaces durante algunas pruebas. Esta limitación quedó documentada en el informe correspondiente.

**Documentación:** [parte7-hilos.md](parte7-hilos.md)

### Parte 8: Mini reto de depuración

Se analizó un programa que debía obtener el número mayor y calcular el promedio de un arreglo.

El programa contenía cuatro errores:

1. Inicialización incorrecta del número mayor.
2. Acceso fuera de los límites del arreglo.
3. Cálculo incorrecto del promedio.
4. Pérdida de memoria dinámica.

Para identificarlos se utilizaron GDB, Valgrind y AddressSanitizer.

El programa original mostraba:

```text
Mayor: 0
Promedio: -80
```

Después de corregir los cuatro errores, se obtuvo:

```text
Mayor: -5
Promedio: -16
```

Valgrind reportó cero errores y AddressSanitizer no detectó accesos inválidos durante la ejecución corregida.

**Documentación:** [parte8-reto-y-reflexion.md](parte8-reto-y-reflexion.md)

### Parte 9: Reflexión final

Se respondieron las quince preguntas de reflexión del laboratorio.

Estas preguntas abarcan:

- Importancia de la depuración.
- Diferencias entre errores de programación.
- Utilidad de GDB.
- Detección de problemas de memoria.
- Uso de Valgrind y AddressSanitizer.
- Detección de condiciones de carrera.
- Selección de herramientas según el error.
- Aplicación de los conocimientos en futuros proyectos.

**Documentación:** [Parte 9: Reflexión final](parte8-reto-y-reflexion.md#parte-9-reflexión-final-del-laboratorio)

---

## 6. Archivos de código fuente

Los programas desarrollados durante el laboratorio se encuentran en la carpeta `codigo/`.

| Archivo | Descripción |
|---|---|
| `01_error_sintaxis.cpp` | Ejercicio de error de sintaxis |
| `02_error_logico.cpp` | Ejercicio de error lógico |
| `03_gdb_basico.cpp` | Introducción al uso de GDB |
| `04_gdb_funciones.cpp` | Depuración de funciones y división entre cero |
| `05_memory_leak.cpp` | Identificación y corrección de pérdidas de memoria |
| `06_invalid_access.cpp` | Análisis de accesos fuera de los límites |
| `07_use_after_free.cpp` | Detección de accesos a memoria liberada |
| `08_race_condition.cpp` | Programa original con condición de carrera |
| `09_race_condition_corregido.cpp` | Programa corregido mediante mutex |
| `10_reto.cpp` | Mini reto corregido |
| `10_reto_original.cpp` | Versión original del mini reto |

Los archivos contienen los programas trabajados durante las actividades.

Los errores originales y sus correcciones se documentan en los archivos Markdown correspondientes.

---

## 7. Evidencias de depuración

Durante el laboratorio se conservaron reportes de herramientas de análisis para documentar los errores encontrados.

### AddressSanitizer

- `evidencia-asan-original.txt`
- `evidencia-reto-asan-original.txt`
- `evidencia-reto-asan-corregido.txt`

### Valgrind

- `evidencia-reto-valgrind-original.txt`
- `evidencia-reto-valgrind-corregido.txt`

### ThreadSanitizer

- `evidencia-tsan-original.txt`
- `evidencia-tsan-corregido.txt`

### Helgrind

- `evidencia-helgrind-original.txt`
- `evidencia-helgrind-corregido.txt`

Estos archivos permiten consultar los resultados originales y las verificaciones posteriores a las correcciones.

Las demás evidencias de compilación, ejecución y depuración se encuentran documentadas directamente en los informes Markdown.

---

## 8. Compilación y ejecución

Para compilar los programas se utiliza el compilador g++.

Los siguientes ejemplos deben ejecutarse desde la carpeta `laboratorio-depuracion`.

### Ejemplo 1: Compilación normal

```bash
g++ -g -O0 -o reto codigo/10_reto.cpp
```

Ejecución:

```bash
./reto
```

### Ejemplo 2: GDB

Compilar con información de depuración:

```bash
g++ -g -O0 -o gdb_funciones codigo/04_gdb_funciones.cpp
```

Abrir GDB:

```bash
gdb ./gdb_funciones
```

### Ejemplo 3: Valgrind

Compilar:

```bash
g++ -g -O0 -o memory_leak codigo/05_memory_leak.cpp
```

Analizar:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./memory_leak
```

### Ejemplo 4: AddressSanitizer

Compilar:

```bash
g++ -g -O0 -fsanitize=address -o use_after_free_asan codigo/07_use_after_free.cpp
```

Ejecutar:

```bash
./use_after_free_asan
```

### Ejemplo 5: ThreadSanitizer

Compilar:

```bash
g++ -g -fsanitize=thread -pthread -o race_condition_tsan codigo/08_race_condition.cpp
```

Ejecutar:

```bash
./race_condition_tsan
```

### Ejemplo 6: Helgrind

Compilar:

```bash
g++ -g -pthread -o race_condition codigo/08_race_condition.cpp
```

Analizar:

```bash
valgrind --tool=helgrind ./race_condition
```

### Ejemplo 7: Programa multihilo corregido

Compilar:

```bash
g++ -g -pthread -o race_condition_corregido codigo/09_race_condition_corregido.cpp
```

Ejecutar:

```bash
./race_condition_corregido
```

Resultado esperado:

```text
Contador final: 200000
```

---

## 9. Resultados generales

| Actividad | Error identificado | Solución aplicada |
|---|---|---|
| Sintaxis | Punto y coma faltante | Corregir la sintaxis |
| Lógica | Promedio incorrecto | Corregir la operación |
| GDB básico | Inspección de variables | Seguimiento paso a paso |
| GDB funciones | División entre cero | Validar el divisor |
| Valgrind | Pérdida de memoria | Agregar `delete[]` |
| Valgrind | Escritura fuera de límites | Corregir el ciclo |
| AddressSanitizer | Uso de memoria liberada | Reordenar las operaciones |
| ThreadSanitizer y Helgrind | Condición de carrera | Utilizar mutex |
| Mini reto | Cuatro errores combinados | Aplicar correcciones lógicas y de memoria |

Las pruebas realizadas permitieron identificar las causas de los problemas y comprobar el comportamiento de los programas después de corregirlos.

---

## 10. Conclusiones

El laboratorio permitió comprender que los errores de programación no siempre son detectados durante la compilación.

Algunos programas pueden compilar correctamente y producir resultados incorrectos o presentar problemas de memoria que no son evidentes durante una ejecución normal.

El uso de GDB permitió investigar variables, funciones y errores de ejecución.

Valgrind y AddressSanitizer resultaron útiles para identificar pérdidas de memoria y accesos inválidos.

ThreadSanitizer y Helgrind permitieron analizar problemas relacionados con la ejecución concurrente.

Además, el uso de mutex demostró la importancia de sincronizar los accesos a recursos compartidos.

Finalmente, el mini reto permitió integrar las herramientas estudiadas y aplicar diferentes técnicas de depuración sobre un mismo programa.

En conclusión, el uso de herramientas de depuración es fundamental para desarrollar software más correcto, seguro, confiable y fácil de mantener.

---

## 11. Organización de la entrega

La entrega incluye:

- Programas fuente en C++.
- Programas corregidos.
- Documentación de cada actividad.
- Comandos utilizados.
- Evidencias de los errores encontrados.
- Resultados posteriores a las correcciones.
- Respuestas a las preguntas de reflexión.
- Conclusión general del laboratorio.

El código y la documentación se encuentran organizados dentro de la carpeta `laboratorio-depuracion` del repositorio.

**Repositorio:** [ie0417-laboratorio_C32985](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985)
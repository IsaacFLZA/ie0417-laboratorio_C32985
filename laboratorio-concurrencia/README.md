# Laboratorio de programación concurrente y paralela en C++

## Información general

- **Universidad:** Universidad de Costa Rica
- **Curso:** IE0417 - Diseño de Software para Ingeniería
- **Laboratorio:** Introducción práctica a programación concurrente y paralela en C++

## Estudiante

- **Nombre:** [Isaac Flores Zamora]
- **Carné:** [C32985]


## Descripción

Este laboratorio tiene como objetivo estudiar los fundamentos de la programación concurrente y paralela utilizando C++. A través de diferentes ejercicios prácticos se exploran la creación y administración de hilos, las condiciones de carrera, los mecanismos de sincronización, la comparación del rendimiento entre ejecuciones secuenciales y paralelas y los problemas de interbloqueo.

El laboratorio se divide en seis partes prácticas y una sección de reflexión final. Los resultados experimentales y sus respectivos análisis se encuentran documentados en el archivo `resultados/analisis.md`.

## Requisitos

Para compilar y ejecutar los programas se necesita:

- Compilador GCC con soporte para C++17 o superior.
- Sistema operativo Linux, macOS o Windows con un entorno de compilación compatible.
- Soporte para la biblioteca estándar de hilos de C++.
- Terminal para ejecutar los comandos de compilación.

Los programas fueron desarrollados y ejecutados utilizando GitHub Codespaces, con Ubuntu 24.04, g++ 13.3.0 y 2 procesadores lógicos disponibles.

## Estructura del proyecto

```text
laboratorio-concurrencia/
├── README.md
├── .gitignore
├── src/
│   ├── parte1_threads.cpp
│   ├── parte2_race_condition.cpp
│   ├── parte3_mutex.cpp
│   ├── parte4_benchmark.cpp
│   ├── parte5_hilos_vs_rendimiento.cpp
│   ├── parte6_deadlock.cpp
│   └── parte6_deadlock_corregido.cpp
└── resultados/
    └── analisis.md
```

## Compilación y ejecución

Los siguientes comandos deben ejecutarse desde la carpeta principal `laboratorio-concurrencia`.

### Parte 1: Creación básica de hilos

Este programa crea cinco hilos que ejecutan una función encargada de imprimir un mensaje. Permite observar el comportamiento concurrente de los hilos y la importancia de utilizar `join()`.

**Compilación:**

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte1_threads.cpp -o parte1
```

**Ejecución:**

```bash
./parte1
```

### Parte 2: Condición de carrera

Este programa crea cuatro hilos que realizan incrementos sobre una variable global compartida sin mecanismos de sincronización, permitiendo observar los problemas de acceso concurrente.

**Compilación:**

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte2_race_condition.cpp -o parte2
```

**Ejecución:**

```bash
./parte2
```

### Parte 3: Corrección usando mutex

Este programa corrige la condición de carrera de la parte anterior mediante el uso de `std::mutex` y `std::lock_guard`, garantizando que solamente un hilo a la vez modifique el contador compartido.

**Compilación:**

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte3_mutex.cpp -o parte3
```

**Ejecución:**

```bash
./parte3
```

### Parte 4: Benchmark secuencial vs. paralelo

Este programa compara los tiempos de ejecución de una suma secuencial y una suma paralela utilizando un vector de 100 000 000 de elementos.

**Compilación:**

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pthread src/parte4_benchmark.cpp -o parte4
```

**Ejecución:**

```bash
./parte4
```

### Parte 5: Cantidad de hilos vs. rendimiento

Este programa evalúa el rendimiento de una suma paralela utilizando diferentes cantidades de hilos: 1, 2, 4, 8 y 16.

**Compilación:**

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pthread src/parte5_hilos_vs_rendimiento.cpp -o parte5
```

**Ejecución:**

```bash
./parte5
```

### Parte 6: Ejemplo de deadlock

Este programa presenta un caso de interbloqueo en el que dos hilos intentan adquirir dos recursos compartidos en órdenes diferentes.

**Compilación:**

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte6_deadlock.cpp -o parte6
```

**Ejecución:**

```bash
./parte6
```

**Advertencia:** Este programa está diseñado para producir un deadlock, por lo que puede quedar bloqueado indefinidamente. En Linux se recomienda ejecutarlo con un límite de tiempo:

```bash
timeout 5s ./parte6
```

### Parte 6: Versión corregida

Esta versión utiliza `std::scoped_lock` para adquirir ambos mutex de manera segura y evitar el interbloqueo.

**Compilación:**

```bash
g++ -std=c++17 -Wall -Wextra -pthread src/parte6_deadlock_corregido.cpp -o parte6_corregido
```

**Ejecución:**

```bash
./parte6_corregido
```

## Resultados y análisis

Los resultados de las ejecuciones y las respuestas a las preguntas de análisis de cada parte se encuentran en:

`resultados/analisis.md`

Este archivo también incluye la reflexión final y las conclusiones generales del laboratorio.

## Conclusión

El laboratorio permitió comprender los fundamentos de la programación concurrente y paralela mediante ejemplos prácticos desarrollados en C++. Se observaron problemas como las condiciones de carrera y los interbloqueos, así como las estrategias utilizadas para resolverlos mediante mecanismos de sincronización.

Además, las mediciones de rendimiento demostraron que aumentar la cantidad de hilos no garantiza una mejora continua en los tiempos de ejecución, ya que deben considerarse los recursos disponibles y los costos asociados con la administración de los hilos.
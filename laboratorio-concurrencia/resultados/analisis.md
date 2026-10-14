# Análisis de resultados
## Laboratorio de programación concurrente y paralela en C++

### Entorno de ejecución

- **Plataforma:** GitHub Codespaces
- **Sistema operativo:** Ubuntu 24.04
- **Compilador:** g++ 13.3.0
- **Procesadores lógicos disponibles:** 2

---

## Parte 1: Creación básica de hilos

### Resultados obtenidos

Se ejecutó el programa cinco veces utilizando cinco hilos. Durante las primeras tres ejecuciones se observaron variaciones en el orden de impresión y mensajes mezclados en la consola, mientras que en las ejecuciones 4 y 5 los mensajes aparecieron ordenados del hilo 0 al hilo 4. En todos los casos se mostró el mensaje "Todos los hilos finalizaron", lo que confirma que el programa principal esperó a que terminaran los cinco hilos.

### Preguntas de análisis

**1. ¿Los mensajes aparecen siempre en el mismo orden?**

No. Durante las cinco ejecuciones se observaron diferentes órdenes de impresión. En algunas ejecuciones los mensajes aparecieron mezclados, mientras que en otras se imprimieron ordenadamente. Esto demuestra que el orden de ejecución de los hilos no está garantizado.

**2. ¿Por qué podría cambiar el orden de impresión?**

El orden puede cambiar porque los hilos se ejecutan concurrentemente y el sistema operativo determina cuándo se ejecuta cada uno. Aunque los hilos se crean en un orden específico, esto no garantiza que sus instrucciones se ejecuten ni que sus mensajes se impriman en ese mismo orden.

**3. ¿Qué función cumple join()?**

La función `join()` permite que el hilo principal espere a que un hilo termine su ejecución antes de continuar. En este programa se utiliza para garantizar que los cinco hilos finalicen antes de imprimir el mensaje "Todos los hilos finalizaron".

**4. ¿Qué podría pasar si no se llama a join()?**

Si un objeto `std::thread` sigue siendo *joinable* cuando se destruye, el programa llama a `std::terminate()`, lo que provoca su terminación. Por esta razón, es importante utilizar `join()` o `detach()` según las necesidades del programa, evitando que los objetos `std::thread` sean destruidos mientras todavía se encuentran en estado *joinable*.

### Conclusión de la parte 1

Se observó que la ejecución concurrente de varios hilos no garantiza un orden determinado de impresión, debido a que el sistema operativo puede intercalar sus operaciones. Además, se comprobó que el uso de `join()` permite esperar a que todos los hilos finalicen antes de continuar con la ejecución del programa principal. Los resultados también demostraron que, cuando varios hilos escriben simultáneamente en la consola, sus mensajes pueden mezclarse.

---

## Parte 2: Condición de carrera

### Resultados obtenidos

Se ejecutó el programa cinco veces utilizando cuatro hilos, donde cada uno realizó 1 000 000 de incrementos sobre una variable global compartida. El valor esperado en cada ejecución era de 4 000 000; sin embargo, los resultados obtenidos fueron inferiores y variaron entre ejecuciones, lo que permitió observar los efectos de una condición de carrera.

| Ejecución | Valor esperado | Valor obtenido |
|-----------|----------------|----------------|
| 1 | 4000000 | 1360955 |
| 2 | 4000000 | 2127788 |
| 3 | 4000000 | 1996023 |
| 4 | 4000000 | 2226778 |
| 5 | 4000000 | 2095508 |

### Preguntas de análisis

**1. ¿El valor obtenido siempre coincide con el valor esperado?**

No. En ninguna de las cinco ejecuciones se obtuvo el valor esperado de 4 000 000. Además, los resultados cambiaron entre ejecuciones, lo que evidencia un comportamiento no determinista provocado por el acceso concurrente a una variable compartida sin mecanismos de sincronización.

**2. ¿Por qué se pierden incrementos?**

Los incrementos se pierden porque varios hilos modifican simultáneamente la misma variable compartida sin sincronización. Por ejemplo, dos hilos pueden leer el mismo valor del contador, incrementarlo y escribir el mismo resultado. Esto provoca que una actualización sobrescriba a otra, por lo que no todos los incrementos realizados se reflejan en el valor final.

**3. ¿La operación contador++ es realmente una sola operación a nivel de CPU?**

No necesariamente. La expresión `contador++` no garantiza una operación atómica, ya que conceptualmente implica leer el valor actual, incrementarlo y almacenar el resultado. Estas operaciones pueden intercalarse con las de otros hilos, ocasionando resultados incorrectos cuando no se utilizan mecanismos de sincronización.

**4. ¿Qué problema de concurrencia se está observando?**

Se está observando una condición de carrera de datos (*data race*), debido a que varios hilos acceden a una misma variable compartida y al menos uno modifica su valor sin utilizar mecanismos de sincronización. En C++, este tipo de acceso concurrente produce comportamiento indefinido, lo que explica que el resultado del programa no sea confiable.

### Conclusión de la parte 2

Se comprobó que utilizar múltiples hilos para modificar una variable compartida sin sincronización puede producir resultados incorrectos. Aunque se esperaban 4 000 000 de incrementos, ninguna de las cinco ejecuciones alcanzó ese valor y los resultados fueron diferentes en cada ocasión. Esto demuestra la importancia de utilizar mecanismos de sincronización cuando varios hilos trabajan sobre un mismo recurso compartido, especialmente cuando realizan operaciones que modifican su estado.

---

## Parte 3: Corrección usando mutex

### Resultados obtenidos

Se ejecutó el programa cinco veces utilizando cuatro hilos, donde cada uno realizó 1 000 000 de incrementos sobre una variable global compartida. A diferencia de la parte anterior, se utilizó `std::mutex` junto con `std::lock_guard` para proteger el contador y evitar que varios hilos lo modificaran simultáneamente. Como resultado, en las cinco ejecuciones se obtuvo correctamente el valor esperado de 4 000 000.

| Ejecución | Valor esperado | Valor obtenido |
|-----------|----------------|----------------|
| 1 | 4000000 | 4000000 |
| 2 | 4000000 | 4000000 |
| 3 | 4000000 | 4000000 |
| 4 | 4000000 | 4000000 |
| 5 | 4000000 | 4000000 |

### Comparación con la parte 2

En la parte 2, ninguna de las cinco ejecuciones alcanzó el valor esperado de 4 000 000, debido a que los hilos modificaban el contador sin mecanismos de sincronización. En cambio, al utilizar un mutex en la parte 3, todas las ejecuciones produjeron el resultado correcto. Esta diferencia demuestra que los mecanismos de sincronización permiten controlar el acceso a los recursos compartidos y evitar las condiciones de carrera de datos.

### Preguntas de análisis

**1. ¿Qué cambió con respecto al programa anterior?**

Se agregó un objeto `std::mutex` y se utilizó `std::lock_guard` para proteger la operación `contador++`. Esto permite que solamente un hilo a la vez modifique la variable compartida, evitando que varios hilos realicen incrementos simultáneos sin sincronización.

**2. ¿Qué hace std::mutex?**

`std::mutex` es un mecanismo de sincronización que permite garantizar la exclusión mutua al acceder a un recurso compartido. Cuando un hilo adquiere el mutex, los demás hilos que intenten adquirirlo deben esperar hasta que sea liberado. De esta manera, se evita que múltiples hilos ejecuten simultáneamente una sección crítica protegida por el mismo mutex.

**3. ¿Qué hace std::lock_guard?**

`std::lock_guard` es un mecanismo que adquiere automáticamente un mutex al crearse y lo libera cuando sale de su ámbito. Esto facilita la administración del mutex y evita tener que llamar manualmente a `lock()` y `unlock()`, reduciendo el riesgo de olvidar liberar el recurso y provocando un código más seguro y fácil de mantener.

**4. ¿Por qué ahora el resultado sí debería ser correcto?**

El resultado debería ser correcto porque cada incremento se realiza dentro de una sección crítica protegida por el mutex. Esto evita que varios hilos modifiquen simultáneamente el contador y garantiza que cada operación de incremento se complete antes de que otro hilo pueda acceder a la misma variable. Como consecuencia, se conservan todos los incrementos y se obtiene el valor esperado de 4 000 000.

**5. ¿Qué desventaja podría tener proteger cada incremento individual con un mutex?**

La principal desventaja es el costo adicional de sincronización, debido a que cada incremento requiere adquirir y liberar el mutex. Estas operaciones introducen trabajo adicional y pueden provocar que los hilos tengan que esperar para acceder al contador. Como consecuencia, el rendimiento puede disminuir y los beneficios de utilizar múltiples hilos pueden verse limitados, especialmente cuando se realizan grandes cantidades de operaciones pequeñas.

### Conclusión de la parte 3

Se comprobó que utilizar `std::mutex` y `std::lock_guard` permite corregir la condición de carrera observada en la parte anterior, garantizando que solamente un hilo a la vez modifique la variable compartida. Las cinco ejecuciones produjeron correctamente los 4 000 000 de incrementos esperados, a diferencia de los resultados incorrectos obtenidos sin sincronización. Sin embargo, aunque estos mecanismos garantizan el acceso seguro a los datos compartidos, también introducen costos adicionales de ejecución que pueden afectar el rendimiento del programa.
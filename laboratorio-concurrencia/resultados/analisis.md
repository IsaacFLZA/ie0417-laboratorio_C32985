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



---

## Parte 4: Mini benchmark secuencial vs. paralelo

### Resultados obtenidos

Se realizó una comparación entre la ejecución secuencial y la ejecución paralela de un programa encargado de sumar los elementos de un vector de 100 000 000 de números enteros. La versión secuencial realizó la suma utilizando un solo hilo, mientras que la versión paralela dividió el trabajo entre cuatro hilos. Ambas implementaciones produjeron correctamente el resultado esperado de 100 000 000.

El programa se ejecutó tres veces para comparar los tiempos de ejecución de ambas implementaciones. Los resultados obtenidos fueron los siguientes:

| Ejecución | Tiempo secuencial | Tiempo paralelo | Más rápido |
|-----------|-------------------|-----------------|------------|
| 1 | 42 ms | 44 ms | Secuencial |
| 2 | 40 ms | 39 ms | Paralelo |
| 3 | 52 ms | 45 ms | Paralelo |

Adicionalmente, se realizó una ejecución inicial en la que se obtuvieron 59 ms para la versión secuencial y 42 ms para la paralela. En general, se observó que la implementación paralela presentó mejores tiempos en dos de las tres ejecuciones registradas, aunque la diferencia de rendimiento no fue constante.

### Preguntas de análisis

**1. ¿El resultado secuencial y el paralelo son iguales?**

Sí. En todas las ejecuciones, tanto la versión secuencial como la paralela produjeron el resultado esperado de 100 000 000. Esto demuestra que ambas implementaciones realizaron correctamente la suma de los elementos del vector, a pesar de utilizar diferentes estrategias de ejecución.

**2. ¿La versión paralela siempre fue más rápida?**

No. Aunque la versión paralela fue más rápida en dos de las tres ejecuciones registradas, en la primera ejecución el programa secuencial tardó 42 ms, mientras que el paralelo necesitó 44 ms. Esto demuestra que utilizar múltiples hilos no garantiza una mejora de rendimiento en todas las ejecuciones, debido a los costos adicionales asociados con la concurrencia y las condiciones de ejecución del sistema.

**3. ¿Por qué dividir el vector en bloques permite paralelizar el trabajo?**

Dividir el vector en bloques permite que diferentes hilos procesen conjuntos independientes de elementos simultáneamente. Cada hilo calcula una suma parcial de su bloque y almacena el resultado en una posición independiente. Una vez que todos los hilos terminan, las sumas parciales se combinan para obtener el resultado total. Como los hilos no necesitan modificar una misma variable compartida durante el cálculo, se evita la necesidad de utilizar un mutex para proteger las sumas parciales.

**4. ¿Qué costos adicionales tiene la versión paralela?**

La versión paralela introduce costos asociados con la creación y administración de hilos, la distribución del trabajo, la sincronización mediante `join()` y la combinación de los resultados parciales. Además, cuando existen más hilos que procesadores lógicos disponibles, el sistema operativo debe distribuir su ejecución entre los recursos existentes, lo que puede generar cambios de contexto y afectar el rendimiento. Estos costos pueden reducir o incluso eliminar las ventajas de la ejecución paralela.

**5. ¿Qué podría pasar si el vector fuera muy pequeño?**

Si el vector fuera muy pequeño, probablemente la versión secuencial resultaría más rápida, debido a que el tiempo necesario para realizar la suma sería reducido. En ese caso, los costos de crear y administrar varios hilos podrían ser mayores que el beneficio obtenido al dividir el trabajo. Por esta razón, la programación paralela suele resultar más conveniente cuando la cantidad de trabajo es suficientemente grande para compensar los costos adicionales.

### Conclusión de la parte 4

Se comprobó que la programación paralela puede mejorar el rendimiento al distribuir una tarea entre varios hilos, siempre que el trabajo pueda dividirse en operaciones independientes. En las pruebas realizadas, la versión paralela fue más rápida en dos de las tres ejecuciones registradas, aunque las diferencias de tiempo fueron relativamente pequeñas y variables. Estos resultados permiten concluir que el uso de múltiples hilos no garantiza automáticamente una ejecución más rápida, ya que el rendimiento también depende de los costos de administración de hilos, la cantidad de trabajo y los recursos disponibles en el sistema.



---

## Parte 5: Cantidad de hilos vs. rendimiento

### Resultados obtenidos

Se modificó el programa de la parte 4 para comparar el rendimiento de la suma paralela de un vector de 100 000 000 de elementos utilizando 1, 2, 4, 8 y 16 hilos. Las pruebas se realizaron en GitHub Codespaces, donde el comando `nproc` indicó que el entorno dispone de 2 procesadores lógicos.

Se realizó una ejecución inicial y posteriormente tres ejecuciones adicionales para observar las variaciones en los tiempos de ejecución. En todas las pruebas se obtuvo correctamente el resultado esperado de 100 000 000.

Los resultados de las tres ejecuciones adicionales fueron los siguientes:

| Cantidad de hilos | Ejecución 1 | Ejecución 2 | Ejecución 3 | Promedio |
|-------------------|-------------|-------------|-------------|----------|
| 1 | 43 ms | 42 ms | 50 ms | 45,00 ms |
| 2 | 43 ms | 39 ms | 38 ms | 40,00 ms |
| 4 | 53 ms | 39 ms | 55 ms | 49,00 ms |
| 8 | 43 ms | 43 ms | 39 ms | 41,67 ms |
| 16 | 40 ms | 44 ms | 43 ms | 42,33 ms |

Los resultados muestran que la configuración de 2 hilos presentó el mejor tiempo promedio, con 40 ms, mientras que la configuración de 4 hilos obtuvo el promedio más alto, con 49 ms. También se observaron variaciones entre las ejecuciones de una misma configuración, lo que indica que el rendimiento puede verse afectado por las condiciones del entorno.

### Preguntas de análisis

**1. ¿Cuál cantidad de hilos produjo el mejor tiempo?**

El mejor tiempo individual fue de 38 ms, obtenido con 2 hilos durante la tercera ejecución. Además, esta configuración presentó el mejor promedio de las tres ejecuciones, con 40 ms. Esto resulta interesante porque el entorno de GitHub Codespaces dispone de 2 procesadores lógicos, aunque no es posible determinar únicamente con estas mediciones si esa correspondencia explica el resultado.

**2. ¿El tiempo mejoró siempre al aumentar los hilos?**

No. Los resultados demostraron que aumentar la cantidad de hilos no garantiza una reducción del tiempo de ejecución. Por ejemplo, la configuración de 2 hilos obtuvo un promedio de 40 ms, mientras que la de 4 hilos presentó un promedio de 49 ms. Aunque las configuraciones de 8 y 16 hilos obtuvieron tiempos competitivos, ninguna superó el promedio registrado con 2 hilos.

**3. ¿Cuántos núcleos tiene la computadora donde se ejecutó el programa?**

Las pruebas se realizaron en GitHub Codespaces, utilizando un entorno virtual de Linux. El comando `nproc` reportó 2 procesadores lógicos disponibles para ejecutar el programa. Este valor corresponde a los recursos disponibles en el entorno virtual y no necesariamente a la cantidad de núcleos físicos de la computadora utilizada para acceder a Codespaces.

**4. ¿Qué ocurre cuando se usan más hilos que núcleos disponibles?**

Cuando se utilizan más hilos que procesadores lógicos disponibles, no todos pueden ejecutar instrucciones simultáneamente. El sistema operativo debe distribuir el tiempo de procesamiento entre ellos, alternando su ejecución según la disponibilidad de recursos. Esto puede generar costos adicionales de administración y limitar los beneficios de la programación paralela.

**5. ¿Qué relación tiene esto con el context switching?**

El *context switching* consiste en cambiar la ejecución del procesador de un hilo o proceso a otro, conservando y restaurando la información necesaria para continuar su ejecución. Cuando existen más hilos ejecutables que procesadores lógicos disponibles, pueden producirse más cambios de contexto. Estos cambios tienen un costo computacional y pueden afectar el rendimiento, ya que el procesador debe dedicar recursos a administrar la ejecución en lugar de realizar únicamente el trabajo del programa.

**6. ¿Por qué la versión con 16 hilos podría no ser la mejor?**

La versión con 16 hilos podría no ser la mejor porque el entorno dispone de solamente 2 procesadores lógicos. Al utilizar una cantidad de hilos considerablemente mayor, aparecen costos adicionales asociados con su creación, planificación y administración. Además, la suma de un vector grande puede estar limitada por la velocidad de acceso a memoria, por lo que agregar hilos no necesariamente incrementa el rendimiento. En las pruebas realizadas, los 16 hilos obtuvieron un promedio de 42,33 ms, superior a los 40 ms registrados con 2 hilos.

### Conclusión de la parte 5

Se comprobó que aumentar la cantidad de hilos no garantiza una mejora continua del rendimiento. Aunque todas las configuraciones produjeron correctamente la suma de los 100 000 000 de elementos, los tiempos variaron dependiendo de la cantidad de hilos utilizada y de las condiciones de ejecución. La configuración de 2 hilos presentó el mejor promedio, lo que resulta consistente con los 2 procesadores lógicos disponibles en el entorno virtual, aunque no demuestra una relación causal por sí sola. Estos resultados muestran la importancia de considerar los recursos disponibles, los costos de administración de hilos y las características del trabajo antes de decidir cuántos hilos utilizar.



---

## Parte 6: Ejemplo simple de deadlock

### Resultados obtenidos

Se ejecutó un programa que utiliza dos hilos y dos recursos compartidos protegidos mediante objetos `std::mutex`. El hilo A intenta adquirir primero el recurso 1 y después el recurso 2, mientras que el hilo B realiza el procedimiento en orden inverso, adquiriendo primero el recurso 2 y posteriormente el recurso 1.

Durante la ejecución, ambos hilos lograron adquirir su primer recurso, pero quedaron bloqueados al intentar obtener el segundo. El programa no finalizó normalmente, por lo que se utilizó el comando `timeout 5s ./parte6` para limitar su ejecución a cinco segundos. Posteriormente, el comando `echo $?` devolvió el código 124, confirmando que el programa fue terminado al alcanzar el tiempo límite establecido.

La salida obtenida fue la siguiente:

```text
Hilo A intentando tomar recurso 1...
Hilo B intentando tomar recurso 2...
Hilo B intentando tomar recurso 1...
Hilo A intentando tomar recurso 2...
```

Posteriormente, se ejecutó una versión corregida utilizando `std::scoped_lock` para adquirir ambos mutex de manera coordinada. En esta ocasión, el programa terminó normalmente y produjo la siguiente salida:

```text
Hilo A obtuvo ambos recursos de forma segura.
Hilo B obtuvo ambos recursos de forma segura.
```

Estos resultados permitieron observar el problema del interbloqueo y comprobar cómo puede evitarse mediante mecanismos adecuados de sincronización.

### Preguntas de análisis

**1. ¿El programa termina normalmente?**

No. En la versión original, el programa quedó bloqueado porque ambos hilos intentaron adquirir recursos que estaban siendo utilizados por el otro. Fue necesario finalizarlo mediante el comando `timeout`, que devolvió el código de salida 124 después de cinco segundos. Esto confirmó que el programa no logró completar su ejecución debido al interbloqueo.

**2. ¿Qué recurso tomó primero el hilo A?**

El hilo A adquirió primero el recurso 1 mediante la operación `recurso1.lock()`. Después de esperar 100 milisegundos, intentó adquirir el recurso 2, pero no pudo continuar porque este se encontraba ocupado por el hilo B.

**3. ¿Qué recurso tomó primero el hilo B?**

El hilo B adquirió primero el recurso 2 mediante la operación `recurso2.lock()`. Posteriormente, intentó adquirir el recurso 1, pero este ya estaba siendo utilizado por el hilo A, por lo que también quedó bloqueado.

**4. ¿Por qué ninguno de los dos hilos puede continuar?**

Ninguno puede continuar porque ambos mantienen un recurso bloqueado mientras esperan adquirir el recurso que posee el otro. El hilo A necesita el recurso 2 para continuar, pero este se encuentra bloqueado por el hilo B. Al mismo tiempo, el hilo B necesita el recurso 1, que está ocupado por el hilo A. Como ninguno libera su recurso antes de obtener el segundo, se produce un interbloqueo.

**5. ¿Qué significa espera circular?**

La espera circular ocurre cuando existe una cadena de hilos o procesos en la que cada uno espera un recurso que está siendo utilizado por otro integrante de la misma cadena. En este ejemplo, el hilo A espera un recurso que posee el hilo B, mientras que el hilo B espera uno que posee el hilo A. Esta dependencia circular impide que ambos continúen su ejecución.

**6. ¿Cómo se podría evitar este problema?**

Una forma de evitar el problema consiste en establecer un orden fijo para adquirir los recursos, de manera que todos los hilos intenten obtenerlos siguiendo la misma secuencia. Otra alternativa es utilizar `std::scoped_lock`, que permite adquirir múltiples mutex utilizando un mecanismo diseñado para evitar interbloqueos. De esta manera, se elimina el problema de que los hilos adquieran los recursos en órdenes incompatibles.

### Corrección utilizando std::scoped_lock

Después de observar el interbloqueo, se implementó una segunda versión del programa utilizando `std::scoped_lock`. En esta implementación, cada hilo solicita ambos mutex mediante una única operación de sincronización, evitando la situación de espera circular presentada en la versión original.

**¿Por qué std::scoped_lock ayuda a evitar este deadlock?**

`std::scoped_lock` permite adquirir varios mutex mediante un mecanismo de bloqueo diseñado para evitar interbloqueos entre ellos. A diferencia de adquirir manualmente cada mutex en un orden diferente, este mecanismo coordina su adquisición y garantiza que los recursos sean liberados automáticamente cuando el objeto sale de su ámbito. En el programa corregido, esto permitió que ambos hilos adquirieran los recursos necesarios y completaran su ejecución sin quedar bloqueados.

### Conclusión de la parte 6

Se comprobó que un deadlock puede ocurrir cuando varios hilos adquieren recursos compartidos en órdenes incompatibles y quedan esperando indefinidamente por recursos utilizados por otros hilos. En la primera versión del programa, ambos hilos quedaron bloqueados y fue necesario finalizar la ejecución mediante `timeout`. Sin embargo, al implementar `std::scoped_lock`, los dos hilos consiguieron adquirir los recursos y finalizar normalmente. Esta experiencia demuestra la importancia de diseñar correctamente los mecanismos de sincronización y establecer estrategias seguras para adquirir múltiples recursos compartidos.



---

## Parte 7: Reflexión final

### Preguntas de reflexión

**1. ¿Cuál fue la diferencia más clara que observó entre ejecución secuencial y ejecución con hilos?**

La diferencia más clara fue que la ejecución secuencial realiza las operaciones siguiendo un orden determinado dentro de un mismo hilo, mientras que la ejecución concurrente permite que varios hilos avancen de manera intercalada y, cuando existen recursos suficientes, ejecuten trabajo simultáneamente. En la parte 1 se observó que los mensajes de los hilos aparecían en diferentes órdenes, mientras que en la parte 4 se comprobó que dividir una tarea entre varios hilos puede reducir su tiempo de ejecución en determinadas condiciones.

**2. ¿Qué es una condición de carrera?**

Una condición de carrera ocurre cuando el resultado de un programa depende del orden o momento en que se ejecutan operaciones concurrentes. En particular, una condición de carrera de datos se produce cuando varios hilos acceden a una misma ubicación de memoria sin la sincronización adecuada y al menos uno realiza una escritura. Durante la parte 2 se observó este problema al permitir que cuatro hilos incrementaran simultáneamente un contador compartido, obteniendo valores incorrectos.

**3. ¿Por qué contador++ puede fallar cuando muchos hilos lo ejecutan al mismo tiempo?**

La operación `contador++` puede fallar porque no garantiza un incremento atómico. Conceptualmente, esta operación requiere leer el valor actual, incrementarlo y almacenar el resultado. Cuando varios hilos realizan estas acciones simultáneamente sin sincronización, pueden leer el mismo valor y sobrescribir actualizaciones realizadas por otros hilos. Esto provoca una condición de carrera de datos y genera comportamiento indefinido, como se observó en la parte 2 del laboratorio.

**4. ¿Qué problema resuelve un mutex?**

Un mutex permite evitar accesos simultáneos no seguros a recursos compartidos mediante un mecanismo de exclusión mutua. Cuando un hilo adquiere el mutex, los demás hilos que intenten adquirirlo deben esperar hasta que sea liberado. En la parte 3 se comprobó su utilidad al proteger un contador compartido, permitiendo obtener correctamente los 4 000 000 de incrementos esperados en todas las ejecuciones.

**5. ¿Qué ventaja tiene std::lock_guard sobre llamar manualmente a lock() y unlock()?**

La principal ventaja de `std::lock_guard` es que administra automáticamente el bloqueo y la liberación de un mutex mediante el principio RAII. El mutex se adquiere al crear el objeto y se libera cuando este sale de su ámbito, incluso si ocurre una excepción. Esto reduce el riesgo de olvidar liberar un recurso y permite escribir código más seguro, sencillo y fácil de mantener.

**6. ¿Por qué más hilos no siempre significan mejor rendimiento?**

Utilizar más hilos no siempre mejora el rendimiento porque su creación, administración y sincronización introducen costos adicionales. Además, la cantidad de procesadores disponibles limita el paralelismo real que puede aprovecharse. En la parte 5 se observó que la configuración de 2 hilos obtuvo el mejor tiempo promedio, mientras que utilizar 4, 8 o 16 hilos no produjo una mejora constante. Esto demuestra que la cantidad de hilos debe seleccionarse considerando los recursos disponibles y las características de la tarea.

**7. ¿Qué es un deadlock?**

Un deadlock o interbloqueo es una situación en la que dos o más hilos quedan bloqueados indefinidamente porque cada uno espera un recurso que está siendo utilizado por otro. En la parte 6 se observó este comportamiento cuando el hilo A adquirió el recurso 1 y esperó el recurso 2, mientras que el hilo B adquirió el recurso 2 y esperó el recurso 1. Como ninguno podía continuar, el programa quedó bloqueado hasta que fue terminado manualmente mediante un límite de tiempo.

**8. ¿Qué buenas prácticas aplicaría al programar con hilos?**

Al programar con hilos es importante minimizar el uso innecesario de recursos compartidos, proteger las secciones críticas mediante mecanismos de sincronización adecuados y evitar mantener mutex bloqueados durante más tiempo del necesario. También es recomendable utilizar herramientas como `std::lock_guard` y `std::scoped_lock` para administrar los bloqueos de manera segura, garantizar que los hilos finalicen correctamente mediante `join()` cuando corresponda y establecer un orden consistente para adquirir múltiples recursos. Además, es importante evaluar el rendimiento mediante mediciones reales, ya que agregar hilos no siempre mejora la ejecución.

**9. ¿En qué tipo de programas reales podría ser útil la programación concurrente?**

La programación concurrente resulta útil en aplicaciones que necesitan atender varias tareas durante un mismo período, especialmente cuando algunas operaciones requieren esperar eventos externos. Por ejemplo, puede utilizarse en servidores web que atienden múltiples solicitudes, aplicaciones con interfaces gráficas que deben mantenerse responsivas, sistemas de comunicación, programas que realizan operaciones de entrada y salida y aplicaciones que gestionan múltiples conexiones de red.

**10. ¿En qué tipo de programas reales podría ser útil la programación paralela?**

La programación paralela resulta especialmente útil en aplicaciones que realizan grandes cantidades de operaciones computacionales independientes y pueden distribuir el trabajo entre varios procesadores. Algunos ejemplos incluyen simulaciones científicas, procesamiento de imágenes y video, análisis de grandes conjuntos de datos, cálculos matemáticos intensivos, entrenamiento de modelos de inteligencia artificial y simulaciones de ingeniería. En estos casos, dividir adecuadamente el trabajo puede reducir el tiempo necesario para completar una tarea.

### Conclusión general del laboratorio

A lo largo del laboratorio se estudiaron conceptos fundamentales de programación concurrente y paralela mediante diferentes programas desarrollados en C++. Inicialmente, se observó cómo la ejecución de múltiples hilos puede producir resultados en órdenes distintos. Posteriormente, se identificaron los problemas ocasionados por el acceso simultáneo a variables compartidas y se comprobó cómo mecanismos de sincronización como `std::mutex` y `std::lock_guard` permiten evitar condiciones de carrera de datos.

También se realizaron mediciones de rendimiento para comparar implementaciones secuenciales y paralelas, observando que utilizar más hilos no garantiza necesariamente una ejecución más rápida. Finalmente, se reprodujo un caso de deadlock y se implementó una solución mediante `std::scoped_lock`, demostrando la importancia de adquirir correctamente los recursos compartidos.

En general, el laboratorio permitió comprender que la programación concurrente y paralela ofrece ventajas importantes para el desarrollo de software, pero también introduce desafíos relacionados con la sincronización, la administración de recursos y el rendimiento. 
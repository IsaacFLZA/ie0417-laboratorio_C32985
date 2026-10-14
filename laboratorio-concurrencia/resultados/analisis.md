# Análisis de resultados
## Laboratorio de programación concurrente y paralela en C++

### Entorno de ejecución

- Plataforma: GitHub Codespaces
- Sistema operativo: Ubuntu 24.04
- Compilador: g++ 13.3.0
- Procesadores lógicos disponibles: 2

---

## Parte 1: Creación básica de hilos

### Resultados obtenidos

Se ejecutó el programa cinco veces utilizando cinco hilos.

Durante las primeras tres ejecuciones se observaron
variaciones en el orden de impresión y mensajes
mezclados en la consola.

En las ejecuciones 4 y 5, los mensajes aparecieron
ordenados del hilo 0 al hilo 4.

En todas las ejecuciones apareció el mensaje
"Todos los hilos finalizaron".

### Preguntas de análisis

**1. ¿Los mensajes aparecen siempre en el mismo orden?**

No. Durante las cinco ejecuciones se observaron
diferentes órdenes de impresión. En algunas ejecuciones
los mensajes aparecieron mezclados, mientras que en
otras se imprimieron ordenadamente.

**2. ¿Por qué podría cambiar el orden de impresión?**

Porque los hilos se ejecutan concurrentemente y el
sistema operativo determina cuándo se ejecuta cada uno.
Aunque los hilos se crean en un orden específico,
esto no garantiza que sus instrucciones se ejecuten
ni que sus mensajes se impriman en ese mismo orden.

**3. ¿Qué función cumple join()?**

La función join() permite que el hilo principal espere
a que un hilo termine su ejecución antes de continuar.
En este programa se utiliza para garantizar que los
cinco hilos finalicen antes de imprimir el mensaje final.

**4. ¿Qué podría pasar si no se llama a join()?**

Si un objeto std::thread sigue siendo joinable cuando
se destruye, el programa llama a std::terminate(),
lo que provoca su terminación.

Por esta razón, es importante utilizar join() o
detach() según las necesidades del programa.

### Conclusión de la parte 1

Se observó que la ejecución concurrente de varios
hilos no garantiza un orden determinado de impresión.

Aunque todos ejecutan la misma función, el sistema
operativo puede intercalar sus operaciones.

Además, se comprobó que join() permite esperar
a que todos los hilos finalicen antes de continuar
con la ejecución del programa principal.


---

## Parte 2: Condición de carrera

### Resultados obtenidos

Se ejecutó el programa cinco veces utilizando cuatro hilos.
Cada hilo realizó 1 000 000 de incrementos sobre una
variable global compartida.

El valor esperado en cada ejecución era de 4 000 000.

| Ejecución | Valor esperado | Valor obtenido |
|-----------|----------------|----------------|
| 1 | 4000000 | 1360955 |
| 2 | 4000000 | 2127788 |
| 3 | 4000000 | 1996023 |
| 4 | 4000000 | 2226778 |
| 5 | 4000000 | 2095508 |

### Preguntas de análisis

**1. ¿El valor obtenido siempre coincide con el valor esperado?**

No. En ninguna de las cinco ejecuciones se obtuvo el
valor esperado de 4 000 000. Además, los resultados
cambiaron entre ejecuciones, lo que evidencia un
comportamiento no determinista.

**2. ¿Por qué se pierden incrementos?**

Porque varios hilos modifican simultáneamente la
misma variable compartida sin sincronización.

Por ejemplo, dos hilos pueden leer el mismo valor
del contador, incrementarlo y escribir el mismo
resultado. Esto provoca que una actualización
sobrescriba a otra.

**3. ¿La operación contador++ es realmente una sola
operación a nivel de CPU?**

No necesariamente. La expresión contador++ no
garantiza una operación atómica.

Conceptualmente, implica leer el valor actual,
incrementarlo y almacenar el resultado.

Estas operaciones pueden intercalarse con las
de otros hilos, ocasionando resultados incorrectos.

**4. ¿Qué problema de concurrencia se está observando?**

Se está observando una condición de carrera de datos
(data race), porque varios hilos acceden a una
misma variable compartida y al menos uno modifica
su valor sin utilizar mecanismos de sincronización.

En C++, este acceso concurrente produce
comportamiento indefinido.

### Conclusión de la parte 2

Se comprobó que utilizar múltiples hilos para modificar
una variable compartida sin sincronización puede
producir resultados incorrectos.

Aunque se esperaban 4 000 000 de incrementos, ninguna
ejecución alcanzó ese valor.

Esto demuestra la importancia de utilizar mecanismos
de sincronización cuando varios hilos trabajan sobre
un mismo recurso compartido.
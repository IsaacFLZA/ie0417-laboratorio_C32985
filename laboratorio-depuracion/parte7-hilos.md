# Parte 7: Análisis de hilos y condiciones de carrera

## 1. Objetivo

Identificar y corregir una condición de carrera en un programa multihilo desarrollado en C++.

Durante esta actividad se utilizan las herramientas ThreadSanitizer y Helgrind para analizar los accesos simultáneos a una variable compartida.

También se busca comprender la importancia de los mecanismos de sincronización, especialmente `std::mutex` y `std::lock_guard`, para evitar problemas de concurrencia.

Finalmente, se comparan los resultados del programa original y del programa corregido para comprobar el efecto de la sincronización.

---

## 2. Herramientas utilizadas

Para desarrollar el ejercicio se utilizaron:

- **GitHub Codespaces:** entorno de desarrollo Linux en la nube.
- **g++:** compilador de C++.
- **std::thread:** biblioteca estándar para crear y administrar hilos.
- **ThreadSanitizer:** herramienta para detectar condiciones de carrera.
- **Valgrind:** conjunto de herramientas para analizar programas.
- **Helgrind:** herramienta de Valgrind especializada en problemas de concurrencia.
- **std::mutex:** mecanismo de sincronización para proteger recursos compartidos.
- **std::lock_guard:** mecanismo para administrar automáticamente el bloqueo y desbloqueo de un mutex.

El entorno utilizado fue:

| Herramienta | Versión |
|---|---|
| Sistema operativo | Ubuntu 24.04.5 LTS |
| g++ | 13.3.0 |
| Valgrind | 3.22.0 |

---

# 3. Ejercicio 1: Programa con condición de carrera

## 3.1. Código original

Se creó el archivo:

`codigo/08_race_condition.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>
#include <thread>

int contador = 0;

void incrementar() {
    for (int i = 0; i < 100000; i++) {
        contador++;
    }
}

int main() {
    std::thread hilo1(incrementar);
    std::thread hilo2(incrementar);

    hilo1.join();
    hilo2.join();

    std::cout << "Contador final: " << contador << std::endl;

    return 0;
}
```

## 3.2. Explicación del programa

El programa define una variable global:

```cpp
int contador = 0;
```

Posteriormente, implementa la función:

```cpp
void incrementar() {
    for (int i = 0; i < 100000; i++) {
        contador++;
    }
}
```

Esta función incrementa el valor de `contador` cien mil veces.

En la función `main()` se crean dos hilos:

```cpp
std::thread hilo1(incrementar);
std::thread hilo2(incrementar);
```

Ambos ejecutan la misma función.

Después se utilizan:

```cpp
hilo1.join();
hilo2.join();
```

Estas instrucciones permiten esperar a que ambos hilos terminen antes de mostrar el resultado final.

Sin embargo, los hilos modifican la misma variable global sin ningún mecanismo de sincronización.

Esto genera una condición de carrera.

## 3.3. Resultado esperado

Cada hilo debe incrementar el contador 100000 veces.

Como existen dos hilos, el resultado esperado es:

\[
100000 + 100000 = 200000
\]

Por lo tanto, el programa debería mostrar:

```text
Contador final: 200000
```

No obstante, debido a los accesos concurrentes no sincronizados, el resultado no está garantizado.

---

## 4. Compilación del programa original

Se ejecutó:

```bash
g++ -g -O0 -pthread -o race_condition codigo/08_race_condition.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

### Explicación de las opciones

- `-g`: incluye información de depuración.
- `-O0`: desactiva las optimizaciones.
- `-pthread`: habilita el soporte necesario para programas que utilizan hilos.
- `-o race_condition`: establece el nombre del ejecutable.

El programa compiló correctamente.

Sin embargo, la compilación exitosa no garantiza que los accesos a memoria compartida sean seguros.

---

## 5. Ejecuciones originales

Se ejecutó el programa mediante:

```bash
./race_condition
```

### 5.1. Primera ejecución

```text
Contador final: 125744
```

### 5.2. Segunda ejecución

```text
Contador final: 103376
```

### 5.3. Tercera ejecución

```text
Contador final: 136893
```

### 5.4. Análisis inicial

Las tres ejecuciones produjeron resultados diferentes.

Además, ninguno coincidió con el valor esperado de `200000`.

Esto es compatible con una condición de carrera, debido a que ambos hilos modifican el contador sin sincronización.

La operación:

```cpp
contador++;
```

No es atómica.

Conceptualmente, implica leer el valor actual, incrementarlo y escribir el resultado.

Cuando dos hilos realizan estas operaciones simultáneamente, pueden producirse actualizaciones perdidas.

Por ejemplo, ambos hilos pueden leer el mismo valor y posteriormente escribir el mismo resultado incrementado.

Como consecuencia, dos incrementos pueden terminar reflejándose como uno solo.

---

## 6. Ejecuciones adicionales

Para observar si el resultado cambiaba entre ejecuciones se utilizó:

```bash
for i in $(seq 1 10); do
    echo "Ejecucion $i:"
    ./race_condition
done
```

### Resultados obtenidos

```text
Ejecucion 1:
Contador final: 200000

Ejecucion 2:
Contador final: 200000

Ejecucion 3:
Contador final: 200000

Ejecucion 4:
Contador final: 103482

Ejecucion 5:
Contador final: 200000

Ejecucion 6:
Contador final: 200000

Ejecucion 7:
Contador final: 200000

Ejecucion 8:
Contador final: 200000

Ejecucion 9:
Contador final: 200000

Ejecucion 10:
Contador final: 200000
```

### 6.1. Interpretación

En nueve ejecuciones se obtuvo el resultado esperado de `200000`.

Sin embargo, en la cuarta ejecución se obtuvo:

```text
Contador final: 103482
```

Esto demuestra que el comportamiento del programa depende de cómo se intercalan las operaciones de los hilos.

El hecho de que algunas ejecuciones produzcan el resultado esperado no significa que el programa esté libre de condiciones de carrera.

Una condición de carrera puede manifestarse solamente bajo determinadas circunstancias de planificación y ejecución.

Por lo tanto, es necesario utilizar herramientas especializadas para analizar los accesos concurrentes a memoria.

---

# 7. Análisis con ThreadSanitizer

## 7.1. Compilación

Se utilizó el siguiente comando:

```bash
g++ -g -O0 -fsanitize=thread -pthread \
-o race_condition_tsan codigo/08_race_condition.cpp
```

La compilación fue exitosa.

La opción:

```bash
-fsanitize=thread
```

Permite instrumentar el programa para detectar condiciones de carrera mediante ThreadSanitizer.

## 7.2. Primera ejecución

Se ejecutó:

```bash
./race_condition_tsan
```

Inicialmente se obtuvo:

```text
FATAL: ThreadSanitizer: unexpected memory mapping
```

Este mensaje indicó que ThreadSanitizer encontró un problema relacionado con el mapeo de memoria durante su ejecución.

El problema puede estar relacionado con las características del entorno Linux virtualizado utilizado por GitHub Codespaces.

Esta ejecución no permitió obtener un análisis válido de las condiciones de carrera.

## 7.3. Ejecución posterior

Posteriormente, al consultar la evidencia guardada, se obtuvo un reporte válido de ThreadSanitizer.

El reporte incluyó:

```text
WARNING: ThreadSanitizer: data race (pid=14130)
```

También identificó:

```text
Read of size 4
```

Y señaló la función:

```text
incrementar() codigo/08_race_condition.cpp:8
```

El reporte mostró que un hilo realizaba una lectura de cuatro bytes mientras otro hilo había realizado una escritura sobre la misma dirección de memoria.

También indicó:

```text
Location is global 'contador' of size 4
```

Esto permitió identificar claramente que el problema estaba relacionado con la variable global `contador`.

## 7.4. Identificación de los hilos

ThreadSanitizer identificó dos hilos involucrados:

- `T1`
- `T2`

Ambos ejecutaban la función `incrementar()`.

El reporte identificó operaciones conflictivas sobre la misma variable compartida.

Una de las advertencias indicó una lectura realizada por el hilo T2 y una escritura previa realizada por T1.

También identificó escrituras conflictivas entre ambos hilos.

## 7.5. Resultado del análisis

El reporte final incluyó:

```text
SUMMARY: ThreadSanitizer: data race codigo/08_race_condition.cpp:8 in incrementar()
```

Y:

```text
Contador final: 200000
ThreadSanitizer: reported 2 warnings
```

### Interpretación

ThreadSanitizer detectó dos advertencias relacionadas con condiciones de carrera.

Esto confirma que el programa original realizaba accesos conflictivos a memoria compartida sin sincronización.

También es importante observar que el contador terminó con el valor esperado de `200000` durante esa ejecución.

Sin embargo, ThreadSanitizer detectó condiciones de carrera.

Esto demuestra que un resultado numérico correcto no garantiza que un programa concurrente esté correctamente sincronizado.

---

# 8. Análisis del programa original con Helgrind

## 8.1. Comando utilizado

Se ejecutó:

```bash
valgrind --tool=helgrind ./race_condition
```

Para conservar la evidencia también se utilizó:

```bash
valgrind --tool=helgrind ./race_condition > evidencia-helgrind-original.txt 2>&1
```

## 8.2. Resultado obtenido

Helgrind reportó:

```text
Possible data race during read of size 4
```

También identificó:

```text
Possible data race during write of size 4
```

Finalmente, el reporte mostró:

```text
ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 1 from 1)
```

## 8.3. Interpretación

Helgrind identificó posibles condiciones de carrera relacionadas con accesos concurrentes a memoria.

Los mensajes indicaron que existían operaciones de lectura y escritura sobre una región compartida sin sincronización adecuada.

En este caso, el problema se relacionaba con la variable global:

```cpp
int contador = 0;
```

Esta variable era modificada desde dos hilos diferentes.

La instrucción responsable era:

```cpp
contador++;
```

Debido a que no existía un mutex, ambos hilos podían ejecutar esta operación simultáneamente.

El reporte de Helgrind confirmó la existencia de accesos potencialmente conflictivos.

---

# 9. Explicación de la condición de carrera

Una condición de carrera de datos ocurre cuando varios hilos acceden a una misma ubicación de memoria de manera concurrente, al menos uno de esos accesos modifica la memoria y no existe una sincronización adecuada entre las operaciones.

En este programa, ambos hilos ejecutaban:

```cpp
contador++;
```

La variable `contador` era compartida.

Como el incremento no era atómico, podían producirse interferencias entre las operaciones de los hilos.

Por ejemplo:

1. El hilo 1 lee el valor actual del contador.
2. El hilo 2 lee el mismo valor.
3. El hilo 1 incrementa y escribe el resultado.
4. El hilo 2 incrementa y escribe el mismo resultado.

En esta situación, uno de los incrementos se pierde.

En C++, una carrera de datos produce comportamiento indefinido.

Por lo tanto, no existe garantía de que el resultado sea correcto o de que el programa se comporte siempre de la misma manera.

Para evitar este problema, es necesario utilizar mecanismos de sincronización.

---

# 10. Corrección mediante std::mutex

## 10.1. Objetivo de la corrección

Evitar que ambos hilos modifiquen simultáneamente la variable global `contador`.

Para lograrlo se utilizó un mutex.

Un mutex permite controlar el acceso a un recurso compartido, garantizando que solamente un hilo pueda ejecutar la sección protegida en un momento determinado.

## 10.2. Archivo corregido

Se creó el archivo:

`codigo/09_race_condition_corregido.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>
#include <thread>
#include <mutex>

int contador = 0;
std::mutex mtx;

void incrementar() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        contador++;
    }
}

int main() {
    std::thread hilo1(incrementar);
    std::thread hilo2(incrementar);

    hilo1.join();
    hilo2.join();

    std::cout << "Contador final: " << contador << std::endl;

    return 0;
}
```

## 10.3. Modificaciones realizadas

Primero se agregó la biblioteca:

```cpp
#include <mutex>
```

Después se declaró un mutex global:

```cpp
std::mutex mtx;
```

Finalmente, se modificó la función `incrementar()`:

```cpp
void incrementar() {
    for (int i = 0; i < 100000; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        contador++;
    }
}
```

La instrucción:

```cpp
std::lock_guard<std::mutex> lock(mtx);
```

Bloquea el mutex antes de ejecutar el incremento.

Cuando el objeto `lock` sale de su ámbito, el mutex se libera automáticamente.

De esta manera, solamente uno de los hilos puede modificar el contador a la vez.

---

# 11. Compilación del programa corregido

Se ejecutó:

```bash
g++ -g -pthread -o race_condition_corregido codigo/09_race_condition_corregido.cpp
```

La compilación se realizó correctamente.

---

# 12. Ejecución del programa corregido

Se ejecutó:

```bash
./race_condition_corregido
```

### Resultado obtenido

```text
Contador final: 200000
```

El programa produjo el resultado esperado.

Esto es consistente con el funcionamiento del mutex, que protege la operación de incremento.

El programa corregido utiliza dos hilos, cada uno de los cuales incrementa el contador cien mil veces.

Al impedir que ambos modifiquen la variable simultáneamente, se evita la pérdida de actualizaciones.

---

# 13. Verificación con Helgrind después de la corrección

## 13.1. Comando utilizado

Se ejecutó:

```bash
valgrind --tool=helgrind ./race_condition_corregido
```

### Resultado obtenido

```text
==15129== Helgrind, a thread error detector
==15129== Using Valgrind-3.22.0 and LibVEX
==15129== Command: ./race_condition_corregido

Contador final: 200000

==15129== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 591211 from 8)
```

## 13.2. Interpretación

El programa corregido produjo el valor esperado:

```text
Contador final: 200000
```

Además, Helgrind reportó:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

Esto significa que no se reportaron errores no suprimidos durante la ejecución analizada.

El reporte también indicó que existían eventos suprimidos por las reglas de supresión de Helgrind.

Estos no deben interpretarse como condiciones de carrera reportadas en el código corregido.

## 13.3. Segunda verificación

Se guardó el reporte mediante:

```bash
valgrind --tool=helgrind ./race_condition_corregido > evidencia-helgrind-corregido.txt 2>&1
```

El resumen obtenido fue:

```text
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 520620 from 8)
```

Esta segunda ejecución volvió a confirmar que Helgrind no reportó errores no suprimidos.

---

# 14. Verificación con ThreadSanitizer después de la corrección

## 14.1. Compilación

Se ejecutó:

```bash
g++ -g -fsanitize=thread -pthread \
-o race_condition_corregido_tsan codigo/09_race_condition_corregido.cpp
```

La compilación terminó sin errores reportados.

## 14.2. Primera ejecución

Se ejecutó:

```bash
./race_condition_corregido_tsan
```

### Resultado obtenido

```text
Segmentation fault (core dumped)
```

El programa instrumentado con ThreadSanitizer terminó inesperadamente.

## 14.3. Segunda ejecución

Se intentó nuevamente mediante:

```bash
./race_condition_corregido_tsan > evidencia-tsan-corregido.txt 2>&1
```

El reporte guardado indicó:

```text
FATAL: ThreadSanitizer: unexpected memory mapping 0x61e704481000-0x61e704482000
```

## 14.4. Interpretación

ThreadSanitizer no pudo completar correctamente el análisis del programa corregido en estas ejecuciones.

El mensaje `unexpected memory mapping` indica un problema relacionado con el mapeo de memoria que requiere ThreadSanitizer para funcionar.

Este comportamiento puede presentarse en algunos entornos Linux virtualizados.

Por lo tanto, no es posible afirmar que ThreadSanitizer haya verificado exitosamente la ausencia de condiciones de carrera en el programa corregido.

Sin embargo, Helgrind sí logró ejecutar el análisis y no reportó condiciones de carrera después de aplicar la sincronización.

Además, el código corregido utiliza `std::mutex` para proteger los accesos al contador compartido.

---

# 15. Comparación antes y después de la corrección

| Característica | Programa original | Programa corregido |
|---|---|---|
| Variable compartida | `contador` | `contador` |
| Cantidad de hilos | 2 | 2 |
| Incrementos por hilo | 100000 | 100000 |
| Sincronización | Ninguna | `std::mutex` |
| Uso de `std::lock_guard` | No | Sí |
| Resultados normales | Variables | 200000 en la ejecución documentada |
| Helgrind | 2 errores | 0 errores no suprimidos |
| ThreadSanitizer | 2 advertencias de carrera detectadas | No completó el análisis |
| Protección del contador | No | Sí |

La comparación demuestra que la sincronización mediante un mutex permitió corregir el problema identificado.

---

# 16. Comparación entre ThreadSanitizer y Helgrind

Ambas herramientas permiten identificar problemas de concurrencia.

Sin embargo, presentan diferencias en su utilización.

| Característica | ThreadSanitizer | Helgrind |
|---|---|---|
| Propósito | Detectar condiciones de carrera | Detectar problemas de sincronización y carreras |
| Activación | `-fsanitize=thread` | `valgrind --tool=helgrind` |
| Requiere compilación instrumentada | Sí | No |
| Detectó el error original | Sí | Sí |
| Reporte original | 2 advertencias | 2 errores |
| Verificación corregida | Limitada por fallos de ejecución | 0 errores no suprimidos |

En este laboratorio, ambas herramientas resultaron útiles para identificar el problema original.

ThreadSanitizer permitió reconocer explícitamente los accesos conflictivos sobre la variable global `contador`.

Helgrind también identificó las posibles carreras y, además, permitió comprobar que después de la corrección no se reportaron errores.

Debido a las dificultades experimentadas con ThreadSanitizer en Codespaces, Helgrind fue la herramienta más útil para verificar la solución.

---

# 17. Preguntas de reflexión

## 17.1. ¿Por qué `contador++` no es una operación segura entre varios hilos?

Porque `contador++` no es una operación atómica cuando se utiliza sobre una variable entera convencional.

Conceptualmente, requiere leer el valor actual, incrementarlo y escribir el resultado.

Si varios hilos ejecutan estas operaciones simultáneamente, pueden producirse interferencias.

Por ejemplo, dos hilos pueden leer el mismo valor antes de que alguno escriba el resultado actualizado.

Esto provoca que algunas actualizaciones se pierdan.

En el ejercicio, esta situación produjo resultados como:

```text
Contador final: 125744
Contador final: 103376
Contador final: 136893
```

Aunque el resultado esperado era `200000`.

## 17.2. ¿Qué significa que dos hilos accedan a la misma variable compartida?

Significa que ambos hilos pueden leer o modificar una misma ubicación de memoria.

En este ejercicio, la variable global `contador` era accesible desde los dos hilos.

Ambos ejecutaban la función `incrementar()` y modificaban la variable.

Cuando varios hilos realizan accesos conflictivos sin sincronización, puede producirse una condición de carrera.

Por esta razón, es necesario proteger los recursos compartidos cuando existen operaciones concurrentes que pueden interferir entre sí.

## 17.3. ¿Qué problema resuelve `std::mutex`?

`std::mutex` permite evitar que varios hilos ejecuten simultáneamente una sección crítica del programa.

Una sección crítica es una región del código que accede a recursos compartidos y requiere sincronización.

En este ejercicio, el mutex protegió la instrucción:

```cpp
contador++;
```

De esta manera, solamente uno de los hilos podía modificar el contador en un momento determinado.

Esto evitó que se perdieran actualizaciones debido a accesos simultáneos.

## 17.4. ¿Qué hace `std::lock_guard`?

`std::lock_guard` es una herramienta de C++ que permite administrar automáticamente un mutex mediante el principio RAII.

Cuando se crea un objeto `std::lock_guard`, se adquiere el bloqueo del mutex.

Cuando el objeto sale de su ámbito, su destructor libera automáticamente el bloqueo.

En el programa se utilizó:

```cpp
std::lock_guard<std::mutex> lock(mtx);
```

Esto permitió proteger el incremento del contador sin tener que utilizar manualmente `lock()` y `unlock()`.

Su principal ventaja es que facilita una administración segura de los bloqueos, incluso cuando una función termina anticipadamente.

## 17.5. ¿Por qué los errores de concurrencia pueden ser difíciles de reproducir?

Porque su aparición depende de cómo se intercalan las operaciones de los distintos hilos.

La planificación de los hilos puede variar entre ejecuciones dependiendo del sistema operativo, la carga del procesador y otros factores.

En este ejercicio se observó que algunas ejecuciones producían valores incorrectos, mientras que otras mostraban el resultado esperado.

Por ejemplo, durante diez ejecuciones adicionales, nueve mostraron `200000`, pero una produjo:

```text
Contador final: 103482
```

Esto demuestra que una condición de carrera puede existir incluso cuando el programa parece funcionar correctamente en varias ejecuciones.

Por esta razón, las pruebas normales no siempre son suficientes y se recomienda utilizar herramientas especializadas.

## 17.6. ¿Cuál herramienta le pareció más clara para analizar este caso: ThreadSanitizer o Helgrind?

Ambas herramientas proporcionaron información útil.

ThreadSanitizer resultó claro al identificar directamente una condición de carrera mediante el mensaje:

```text
WARNING: ThreadSanitizer: data race
```

También mostró los accesos conflictivos realizados por los hilos y señaló la variable global `contador`.

Sin embargo, durante el ejercicio presentó problemas de ejecución relacionados con el mapeo de memoria en Codespaces.

Por otro lado, Helgrind permitió detectar el problema original mediante mensajes como:

```text
Possible data race during read
Possible data race during write
```

Además, después de corregir el programa con `std::mutex`, permitió verificar:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

Por esta razón, Helgrind resultó más útil para completar la verificación del ejercicio, mientras que ThreadSanitizer proporcionó un reporte claro para identificar el problema original.

---

# 18. Evidencias generales

## 18.1. Resultados originales

Las primeras ejecuciones mostraron:

```text
Contador final: 125744
Contador final: 103376
Contador final: 136893
```

El resultado esperado era:

```text
Contador final: 200000
```

## 18.2. ThreadSanitizer original

```text
WARNING: ThreadSanitizer: data race

Location is global 'contador' of size 4

SUMMARY: ThreadSanitizer: data race codigo/08_race_condition.cpp:8 in incrementar()

ThreadSanitizer: reported 2 warnings
```

## 18.3. Helgrind original

```text
Possible data race during read of size 4
Possible data race during write of size 4

ERROR SUMMARY: 2 errors from 2 contexts
```

## 18.4. Programa corregido

```text
Contador final: 200000
```

## 18.5. Helgrind corregido

```text
Contador final: 200000

ERROR SUMMARY: 0 errors from 0 contexts
```

## 18.6. ThreadSanitizer corregido

En las ejecuciones realizadas se observaron:

```text
Segmentation fault (core dumped)
```

Y:

```text
FATAL: ThreadSanitizer: unexpected memory mapping
```

Estos resultados se documentan como una limitación de ejecución de ThreadSanitizer en el entorno utilizado.

No constituyen una advertencia de carrera detectada en el programa corregido.

---

# 19. Reflexión general

Esta actividad permitió comprender la importancia de la sincronización cuando varios hilos acceden a una misma variable compartida.

En el programa original se observó que el contador podía producir resultados diferentes entre ejecuciones.

Esto permitió comprobar que la ejecución concurrente no garantiza resultados correctos cuando existen accesos no sincronizados a memoria.

El uso de ThreadSanitizer y Helgrind permitió identificar las condiciones de carrera presentes en el programa original.

Posteriormente, se utilizó `std::mutex` junto con `std::lock_guard` para proteger el incremento del contador.

Después de aplicar la corrección, el programa produjo el resultado esperado y Helgrind no reportó errores.

También se comprendió que las herramientas de análisis pueden presentar limitaciones relacionadas con el entorno de ejecución, como ocurrió con ThreadSanitizer en GitHub Codespaces.

---

# 20. Conclusión

Se completó el análisis de condiciones de carrera en un programa multihilo desarrollado en C++.

El programa original utilizaba dos hilos que incrementaban una variable global sin sincronización.

Durante las primeras ejecuciones se obtuvieron resultados diferentes del valor esperado de `200000`.

Las herramientas ThreadSanitizer y Helgrind identificaron correctamente accesos conflictivos a la variable compartida.

Para solucionar el problema se utilizó un mutex administrado mediante `std::lock_guard`.

Después de aplicar la corrección, el programa produjo:

```text
Contador final: 200000
```

Además, Helgrind reportó:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

Aunque ThreadSanitizer no pudo completar la verificación del programa corregido debido a problemas de ejecución, sus reportes del programa original permitieron identificar las condiciones de carrera.

Esta actividad permitió comprender la importancia de utilizar mecanismos de sincronización en programas concurrentes y demostró cómo las herramientas de análisis de hilos ayudan a identificar problemas que pueden ser difíciles de reproducir mediante ejecuciones normales.
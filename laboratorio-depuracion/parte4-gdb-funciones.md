# Parte 4: Step, Next y Backtrace

## 1. Objetivo

Comprender las diferencias entre los comandos `step` y `next` del depurador GDB, así como aprender a utilizar `backtrace` para inspeccionar la pila de llamadas de un programa.

En esta actividad se analiza un programa escrito en C++ que presenta un error de ejecución provocado por una división entre cero.

El objetivo es identificar la causa del fallo, inspeccionar las variables involucradas, analizar la secuencia de llamadas entre funciones y corregir el código para evitar que el programa termine inesperadamente.

## 2. Herramientas utilizadas

Para desarrollar este ejercicio se utilizaron las siguientes herramientas:

- **GitHub Codespaces:** entorno Linux en la nube utilizado para desarrollar el laboratorio.
- **g++:** compilador utilizado para generar el programa ejecutable.
- **GDB:** depurador utilizado para inspeccionar las variables, ejecutar instrucciones paso a paso y analizar la pila de llamadas.
- **Terminal Linux:** utilizada para compilar y ejecutar el programa.

Las versiones utilizadas fueron:

| Herramienta | Versión |
|---|---|
| Sistema operativo | Ubuntu 24.04.5 LTS |
| g++ | 13.3.0 |
| GDB | 15.1 |

---

## 3. Código original

Se creó el archivo:

`codigo/04_gdb_funciones.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

int dividir(int a, int b) {
    int resultado = a / b;
    return resultado;
}

int calcular(int x) {
    int divisor = x - 5;
    int resultado = dividir(100, divisor);
    return resultado;
}

int main() {
    int valor = 5;
    int respuesta = calcular(valor);

    std::cout << "Respuesta: " << respuesta << std::endl;

    return 0;
}
```

### 3.1. Explicación del programa

El programa contiene tres funciones.

**Función `main()`:**

Es el punto de entrada del programa.

Inicializa la variable `valor` con el número `5` y llama a la función `calcular()`.

**Función `calcular()`:**

Recibe un número entero mediante el parámetro `x`.

Después calcula un divisor utilizando:

```cpp
int divisor = x - 5;
```

Finalmente, llama a la función `dividir()` utilizando el número `100` y el divisor calculado.

**Función `dividir()`:**

Recibe dos números enteros y realiza una división:

```cpp
int resultado = a / b;
```

El problema es que no verifica si el divisor es igual a cero antes de realizar la operación.

---

## 4. Compilación del programa original

Se ejecutó el siguiente comando:

```bash
g++ -g -O0 -o gdb_funciones codigo/04_gdb_funciones.cpp && echo "Compilacion exitosa"
```

### 4.1. Resultado obtenido

```text
Compilacion exitosa
```

El programa compiló correctamente.

Esto demuestra que el compilador no encontró errores de sintaxis que impidieran generar el ejecutable.

Sin embargo, la compilación exitosa no garantiza que el programa funcione correctamente durante su ejecución.

### 4.2. Opciones utilizadas

- `-g`: incorpora información de depuración al ejecutable.
- `-O0`: desactiva las optimizaciones del compilador para facilitar la depuración.
- `-o gdb_funciones`: establece el nombre del ejecutable.
- `codigo/04_gdb_funciones.cpp`: indica el archivo fuente que se desea compilar.

---

## 5. Ejecución original del programa

Se utilizó el comando:

```bash
./gdb_funciones
```

### 5.1. Resultado obtenido

```text
Floating point exception (core dumped)
```

El programa terminó inesperadamente durante su ejecución.

### 5.2. Análisis inicial

Aunque el mensaje indica `Floating point exception`, en este caso el problema no está relacionado con una operación de números decimales.

El fallo ocurre debido a una división entera entre cero.

El programa intenta realizar una operación aritmética inválida, lo que provoca que el sistema genere una señal de error.

En Linux, este tipo de fallo normalmente produce la señal `SIGFPE`.

Para identificar exactamente dónde ocurre el problema se utilizó el depurador GDB.

---

## 6. Inicio de la depuración con GDB

Se abrió el programa utilizando:

```bash
gdb -q -iex "set debuginfod enabled off" ./gdb_funciones
```

La opción `-q` evita mostrar el mensaje inicial de presentación de GDB.

La instrucción `set debuginfod enabled off` desactiva la descarga automática de información de depuración adicional.

Esto permitió trabajar directamente con los símbolos incorporados mediante la opción `-g`.

### 6.1. Resultado inicial

```text
Reading symbols from ./gdb_funciones...
(gdb)
```

Esto confirmó que GDB abrió correctamente el programa y reconoció sus símbolos de depuración.

---

## 7. Establecimiento del breakpoint

Se utilizó:

```gdb
break main
```

### 7.1. Resultado obtenido

```text
Breakpoint 1 at 0x11e1: file codigo/04_gdb_funciones.cpp, line 15.
```

### 7.2. Explicación

El comando `break main` establece un punto de interrupción al comienzo de la función `main()`.

Esto permite detener el programa antes de ejecutar sus instrucciones principales.

En este caso, GDB identificó que el breakpoint corresponde a la línea 15 del archivo fuente.

---

## 8. Inicio de la ejecución

Se utilizó:

```gdb
run
```

### 8.1. Resultado obtenido

```text
Starting program: /workspaces/ie0417-laboratorio_C32985/laboratorio-depuracion/gdb_funciones

[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at codigo/04_gdb_funciones.cpp:15
15          int valor = 5;
```

### 8.2. Análisis

El programa comenzó su ejecución y se detuvo al alcanzar el breakpoint establecido en `main()`.

La primera instrucción mostrada corresponde a la asignación del valor inicial:

```cpp
int valor = 5;
```

Esto permitió comenzar a inspeccionar las variables antes de que se produjera el fallo.

---

## 9. Ejecución paso a paso con `next`

Se ejecutó:

```gdb
next
```

### Resultado obtenido

```text
16          int respuesta = calcular(valor);
```

El comando `next` ejecutó la asignación de `valor` y avanzó hasta la siguiente instrucción.

Posteriormente se inspeccionó la variable:

```gdb
print valor
```

Resultado:

```text
$1 = 5
```

Esto confirmó que la variable `valor` contenía el número esperado.

---

## 10. Entrada a la función `calcular()` con `step`

Se utilizó:

```gdb
step
```

### Resultado obtenido

```text
calcular (x=5) at codigo/04_gdb_funciones.cpp:9
9           int divisor = x - 5;
```

A diferencia de `next`, el comando `step` permitió entrar en la función `calcular()`.

Después se ejecutó:

```gdb
print x
```

### Resultado obtenido

```text
$2 = 5
```

Esto confirmó que la función recibió correctamente el valor enviado desde `main()`.

---

## 11. Inspección del divisor

Dentro de `calcular()` se ejecutó:

```gdb
next
```

Resultado:

```text
10          int resultado = dividir(100, divisor);
```

Después se utilizó:

```gdb
print divisor
```

### Resultado obtenido

```text
$3 = 0
```

### Análisis

La variable `divisor` se calcula mediante:

```cpp
int divisor = x - 5;
```

Como `x` contiene el valor `5`, la operación realizada es:

\[
5 - 5 = 0
\]

Por lo tanto, el divisor resultante es cero.

Este resultado permitió identificar una posible causa del fallo.

---

## 12. Entrada a la función `dividir()`

Se utilizó:

```gdb
step
```

### Resultado obtenido

```text
dividir (a=100, b=0) at codigo/04_gdb_funciones.cpp:4
4           int resultado = a / b;
```

Esto confirmó que la función `dividir()` recibió dos parámetros:

- `a = 100`
- `b = 0`

Para verificar los valores individualmente se utilizaron los siguientes comandos.

### 12.1. Inspección de `a`

```gdb
print a
```

Resultado:

```text
$4 = 100
```

### 12.2. Inspección de `b`

```gdb
print b
```

Resultado:

```text
$5 = 0
```

### 12.3. Análisis

La función intenta ejecutar:

```cpp
int resultado = a / b;
```

Sustituyendo los valores observados:

```text
100 / 0
```

Esta operación no está definida matemáticamente.

Por lo tanto, el programa presenta un error de ejecución causado por intentar dividir entre cero.

---

## 13. Análisis de la pila de llamadas con `backtrace`

Se utilizó el comando:

```gdb
backtrace
```

### 13.1. Resultado obtenido

```text
#0  dividir (a=100, b=0) at codigo/04_gdb_funciones.cpp:4
#1  0x00005555555551cd in calcular (x=5) at codigo/04_gdb_funciones.cpp:10
#2  0x00005555555551f2 in main () at codigo/04_gdb_funciones.cpp:16
```

### 13.2. Interpretación

El comando `backtrace` mostró las funciones activas en la pila de llamadas.

La información permite identificar el recorrido que siguió el programa hasta llegar al error.

**Nivel 2: `main()`**

La ejecución comenzó en `main()` y se llamó a la función `calcular()` con el valor `5`.

**Nivel 1: `calcular()`**

La función recibió `x = 5`, calculó un divisor igual a cero y llamó a `dividir()`.

**Nivel 0: `dividir()`**

La función recibió `a = 100` y `b = 0`.

En esta función se encontraba la instrucción que intentaba realizar la división inválida.

La pila de llamadas permitió confirmar que el problema se originó en `dividir()`, aunque el valor incorrecto del divisor se generó previamente en `calcular()`.

---

## 14. Identificación del error mediante SIGFPE

Después de inspeccionar las variables se ejecutó:

```gdb
next
```

### Resultado obtenido

```text
Program received signal SIGFPE, Arithmetic exception.
0x000055555555519b in dividir (a=100, b=0) at codigo/04_gdb_funciones.cpp:4
4           int resultado = a / b;
```

### 14.1. Explicación

La señal `SIGFPE` indica que ocurrió una excepción aritmética.

En este programa, la señal fue provocada por intentar realizar una división entera entre cero.

GDB detuvo la ejecución e identificó exactamente la función y la línea donde se produjo el problema.

Esto confirmó que el error no estaba relacionado con la sintaxis del programa, sino con una operación inválida durante su ejecución.

---

## 15. Identificación de la causa del error

La causa principal se encontraba en la función:

```cpp
int dividir(int a, int b) {
    int resultado = a / b;
    return resultado;
}
```

Esta función realiza directamente la división sin verificar si el divisor es válido.

Por otra parte, en la función `calcular()` se genera el valor cero:

```cpp
int divisor = x - 5;
```

Como `x` contiene el valor `5`, el divisor resulta igual a cero.

La combinación de ambas situaciones provoca el fallo.

Para corregirlo es necesario validar el divisor antes de realizar la operación.

---

## 16. Corrección realizada

Se agregó una condición dentro de la función `dividir()`:

```cpp
if (b == 0) {
    std::cout << "Error: no se puede dividir entre cero." << std::endl;
    return 0;
}
```

### 16.1. Explicación de la corrección

La condición verifica si el divisor es igual a cero.

Si se cumple, el programa muestra un mensaje de error y devuelve el valor `0` sin realizar la división.

De esta manera, se evita ejecutar la operación inválida.

Esta solución corresponde a la validación propuesta en el enunciado del laboratorio.

Es importante señalar que devolver `0` permite evitar el fallo en este ejercicio, aunque en un programa real sería recomendable utilizar un mecanismo que permita distinguir claramente entre un resultado válido y una operación fallida.

---

## 17. Código corregido completo

El contenido final de `codigo/04_gdb_funciones.cpp` fue:

```cpp
#include <iostream>

int dividir(int a, int b) {
    if (b == 0) {
        std::cout << "Error: no se puede dividir entre cero." << std::endl;
        return 0;
    }

    int resultado = a / b;
    return resultado;
}

int calcular(int x) {
    int divisor = x - 5;
    int resultado = dividir(100, divisor);
    return resultado;
}

int main() {
    int valor = 5;
    int respuesta = calcular(valor);

    std::cout << "Respuesta: " << respuesta << std::endl;

    return 0;
}
```

---

## 18. Compilación después de la corrección

Se ejecutó:

```bash
g++ -g -O0 -o gdb_funciones codigo/04_gdb_funciones.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

La compilación se realizó correctamente.

---

## 19. Ejecución del programa corregido

Se ejecutó:

```bash
./gdb_funciones
```

### Resultado obtenido

```text
Error: no se puede dividir entre cero.
Respuesta: 0
```

### 19.1. Análisis del resultado

El programa identificó correctamente que el divisor era igual a cero.

En lugar de intentar realizar la división, mostró un mensaje indicando que la operación no era válida.

Posteriormente, la función devolvió `0`, permitiendo que el programa continuara hasta finalizar normalmente.

Esto confirmó que la corrección evitó el fallo observado inicialmente.

---

## 20. Comparación antes y después de la corrección

| Característica | Programa original | Programa corregido |
|---|---|---|
| Compilación | Exitosa | Exitosa |
| Validación del divisor | No | Sí |
| División entre cero | Se intenta ejecutar | Se evita |
| Resultado | `Floating point exception` | Mensaje de error |
| Finalización | Anormal | Normal |
| Resultado mostrado | No se completa | `Respuesta: 0` |

La comparación demuestra que la validación permitió corregir el problema de ejecución.

---

## 21. Diferencia entre `next` y `step`

Durante la depuración se utilizaron ambos comandos.

### Comando `next`

Permite ejecutar la instrucción actual sin entrar en las funciones que se llaman desde ella.

Por ejemplo:

```cpp
int respuesta = calcular(valor);
```

Si se utiliza `next`, GDB intenta ejecutar toda la llamada a `calcular()` y detenerse en la siguiente instrucción de `main()`.

Sin embargo, si ocurre un error dentro de la función, GDB puede detenerse en el lugar donde se produjo el fallo.

### Comando `step`

Permite avanzar a la siguiente instrucción y entrar en una función cuando se encuentra una llamada.

En el ejercicio, `step` permitió ingresar a `calcular()` y después a `dividir()`.

Esto hizo posible inspeccionar las variables internas de ambas funciones.

### Comparación

| Comando | Comportamiento |
|---|---|
| `next` | Avanza sin entrar en las funciones llamadas |
| `step` | Permite entrar en las funciones llamadas |
| `backtrace` | Muestra la pila de llamadas activa |

---

## 22. Preguntas de reflexión

### 22.1. ¿Qué diferencia observó entre `next` y `step`?

La principal diferencia observada fue que `next` permite avanzar por las instrucciones sin entrar en las funciones llamadas, mientras que `step` permite ingresar a ellas.

Durante el ejercicio, el comando `step` permitió entrar en las funciones `calcular()` y `dividir()` para inspeccionar sus variables internas.

Esto fue importante porque permitió observar cómo se generaba el divisor igual a cero.

Por otro lado, `next` permitió ejecutar instrucciones completas sin tener que revisar todas las operaciones internas.

Ambos comandos resultan útiles dependiendo del nivel de detalle que se necesite durante la depuración.

### 22.2. ¿Para qué sirve `backtrace`?

El comando `backtrace` permite mostrar la pila de llamadas de un programa durante su ejecución.

Esto significa que muestra las funciones activas y la secuencia de llamadas que llevó hasta el punto actual.

En este ejercicio permitió observar que `main()` llamó a `calcular()` y que posteriormente `calcular()` llamó a `dividir()`.

También permitió identificar que el fallo ocurría dentro de `dividir()`, donde se intentaba realizar una división entre cero.

Esta información es especialmente útil cuando un programa tiene varias funciones relacionadas y se necesita determinar dónde se originó un problema.

### 22.3. ¿Cuál fue la causa del error?

La causa del error fue intentar realizar una división entre cero.

Dentro de la función `calcular()` se ejecutó:

```cpp
int divisor = x - 5;
```

Como `x` tenía el valor `5`, el resultado fue `0`.

Posteriormente, la función `dividir()` recibió este valor y trató de ejecutar:

```cpp
int resultado = a / b;
```

Con los valores:

```text
a = 100
b = 0
```

Esto provocó la señal `SIGFPE` y la terminación inesperada del programa.

### 22.4. ¿Por qué este error es de tiempo de ejecución?

Este error se considera de tiempo de ejecución porque el programa compila correctamente, pero falla cuando intenta ejecutar una operación inválida.

El compilador no detectó el problema porque la instrucción de división era sintácticamente válida.

El error se produjo cuando el valor del divisor resultó igual a cero durante la ejecución.

Por esta razón, fue necesario ejecutar el programa y utilizar GDB para identificar la causa exacta del fallo.

### 22.5. ¿Cómo podría prevenirse este tipo de error desde el diseño del programa?

Este tipo de error puede prevenirse mediante validaciones adecuadas antes de ejecutar operaciones que puedan producir resultados inválidos.

Por ejemplo, antes de realizar una división se debe comprobar que el divisor sea diferente de cero.

También se pueden utilizar pruebas con diferentes valores de entrada para verificar que las funciones se comporten correctamente en situaciones normales y especiales.

Otra buena práctica es definir claramente las condiciones que deben cumplir los parámetros de una función.

En programas más grandes también sería recomendable utilizar mecanismos apropiados para comunicar errores, como excepciones o valores de retorno que permitan identificar si una operación se realizó correctamente.

Estas medidas ayudan a mejorar la seguridad y confiabilidad del código.

---

## 23. Reflexión sobre la actividad

Esta actividad permitió comprender la importancia de utilizar herramientas de depuración cuando un programa compila correctamente, pero presenta errores durante su ejecución.

El uso de GDB permitió analizar el programa paso a paso e identificar los valores de las variables involucradas en el problema.

También se comprendió la diferencia entre los comandos `next` y `step`, así como la utilidad de `backtrace` para visualizar la secuencia de llamadas entre funciones.

La inspección de las variables permitió encontrar que el divisor tenía un valor igual a cero, lo que provocaba una operación aritmética inválida.

Finalmente, se comprobó que una validación sencilla puede evitar que el programa termine inesperadamente.

---

## 24. Conclusión

Se completó correctamente el ejercicio de depuración de funciones utilizando GDB.

El programa original compilaba correctamente, pero presentaba un error de ejecución debido a una división entre cero.

Mediante los comandos `break`, `run`, `next`, `step`, `print` y `backtrace`, fue posible identificar la causa del problema y comprender cómo se relacionaban las diferentes funciones.

Los valores observados durante la depuración fueron:

| Variable | Valor |
|---|---:|
| `valor` | 5 |
| `x` | 5 |
| `divisor` | 0 |
| `a` | 100 |
| `b` | 0 |

Después de identificar el error se agregó una validación que evita dividir entre cero.

La compilación y ejecución del programa corregido fueron exitosas, obteniendo:

```text
Error: no se puede dividir entre cero.
Respuesta: 0
```

Esta actividad permitió reforzar el uso de GDB como herramienta para investigar errores de ejecución y comprender la importancia de validar las operaciones antes de realizarlas.
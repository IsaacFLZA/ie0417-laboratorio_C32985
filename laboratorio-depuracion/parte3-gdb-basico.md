# Parte 3: Introducción a GDB

## 1. Objetivo

Aprender a utilizar el depurador GDB para analizar el comportamiento de un programa escrito en C++ durante su ejecución.

En esta parte se busca comprender cómo establecer puntos de interrupción, ejecutar instrucciones paso a paso e inspeccionar los valores de las variables.

También se pretende identificar las diferencias entre ejecutar un programa normalmente y ejecutarlo mediante un depurador.

## 2. Herramientas utilizadas

Para desarrollar este ejercicio se utilizaron las siguientes herramientas:

- **GitHub Codespaces:** entorno de desarrollo Linux utilizado para ejecutar el laboratorio desde el navegador.
- **g++:** compilador de C++ utilizado para generar el programa ejecutable.
- **GDB:** depurador utilizado para controlar la ejecución del programa e inspeccionar variables.
- **Terminal Linux:** utilizada para ejecutar los comandos y observar los resultados.

Las versiones utilizadas fueron:

| Herramienta | Versión |
|---|---|
| Sistema operativo | Ubuntu 24.04.5 LTS |
| g++ | 13.3.0 |
| GDB | 15.1 |

---

## 3. Código fuente del programa

Se creó el archivo:

`codigo/03_gdb_basico.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

int duplicar(int x) {
    int resultado = x * 2;
    return resultado;
}

int sumar(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int numero = 5;
    int doble = duplicar(numero);
    int total = sumar(doble, 10);

    std::cout << "Número: " << numero << std::endl;
    std::cout << "Doble: " << doble << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
```

### 3.1. Explicación del programa

El programa contiene tres funciones principales.

**Función `duplicar()`:**

```cpp
int duplicar(int x) {
    int resultado = x * 2;
    return resultado;
}
```

Recibe un número entero, lo multiplica por dos y devuelve el resultado.

**Función `sumar()`:**

```cpp
int sumar(int a, int b) {
    int resultado = a + b;
    return resultado;
}
```

Recibe dos números enteros, realiza su suma y devuelve el resultado.

**Función `main()`:**

```cpp
int main() {
    int numero = 5;
    int doble = duplicar(numero);
    int total = sumar(doble, 10);

    std::cout << "Número: " << numero << std::endl;
    std::cout << "Doble: " << doble << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
```

Es la función principal del programa.

Primero asigna el valor `5` a la variable `numero`.

Después utiliza la función `duplicar()` para obtener el doble del número.

Finalmente, utiliza la función `sumar()` para agregar `10` al resultado anterior.

Los valores esperados son:

| Variable | Valor esperado |
|---|---:|
| `numero` | 5 |
| `doble` | 10 |
| `total` | 20 |

---

## 4. Compilación del programa

Se utilizó el siguiente comando:

```bash
g++ -g -O0 -o gdb_basico codigo/03_gdb_basico.cpp
```

Para verificar el resultado también se utilizó:

```bash
g++ -g -O0 -o gdb_basico codigo/03_gdb_basico.cpp && echo "Compilacion exitosa"
```

### 4.1. Resultado obtenido

```text
Compilacion exitosa
```

Esto confirma que el programa compiló correctamente.

### 4.2. Explicación de las opciones utilizadas

El comando contiene diferentes opciones:

- `g++`: ejecuta el compilador de C++.
- `-g`: incorpora información de depuración al ejecutable.
- `-O0`: desactiva las optimizaciones del compilador.
- `-o gdb_basico`: establece el nombre del archivo ejecutable.
- `codigo/03_gdb_basico.cpp`: indica el archivo fuente que se desea compilar.

### 4.3. ¿Para qué sirve la opción `-g`?

La opción `-g` permite incluir información de depuración dentro del archivo ejecutable.

Esta información permite que GDB relacione las instrucciones ejecutadas con las líneas del código fuente original.

Gracias a esta opción, el depurador puede mostrar nombres de funciones, variables y números de línea.

También facilita establecer puntos de interrupción e inspeccionar los valores de las variables.

La opción `-O0` se utilizó adicionalmente para evitar optimizaciones que pudieran dificultar la observación del programa durante su ejecución.

---

## 5. Ejecución normal del programa

Antes de utilizar el depurador, se ejecutó el programa normalmente.

Comando utilizado:

```bash
./gdb_basico
```

### 5.1. Resultado obtenido

```text
Número: 5
Doble: 10
Total: 20
```

### 5.2. Análisis del resultado

El programa se ejecutó correctamente.

Los resultados obtenidos coinciden con los valores esperados.

La variable `numero` contiene el valor inicial `5`.

La función `duplicar()` devuelve `10`, que se almacena en `doble`.

Finalmente, la función `sumar()` recibe los valores `10` y `10`, devolviendo `20`.

Aunque el programa funciona correctamente, se utilizará GDB para observar cómo cambian las variables durante la ejecución.

---

## 6. Ejecución del programa mediante GDB

Para iniciar el depurador se utilizó:

```bash
gdb ./gdb_basico
```

Dentro de GDB se ejecutaron los siguientes comandos:

```gdb
break main
run
next
print numero
next
print doble
next
print total
continue
quit
```

Estos comandos permiten detener el programa al comenzar la función `main()`, avanzar por sus instrucciones e inspeccionar los valores de las variables.

---

## 7. Establecimiento de un breakpoint

Se utilizó el comando:

```gdb
break main
```

### 7.1. Resultado obtenido

```text
Breakpoint 1 at 0x11cb: file codigo/03_gdb_basico.cpp, line 14.
```

### 7.2. Explicación

El comando `break main` establece un punto de interrupción al inicio de la función `main()`.

Esto significa que, cuando el programa comience a ejecutarse, GDB detendrá su ejecución al llegar a esa función.

El breakpoint permite analizar el programa antes de continuar con las siguientes instrucciones.

En este caso, GDB identificó que la función `main()` comienza en la línea 14 del archivo fuente.

La dirección de memoria `0x11cb` corresponde a la ubicación reportada por GDB al establecer el breakpoint.

---

## 8. Inicio de la ejecución con `run`

Después de establecer el breakpoint se utilizó:

```gdb
run
```

### 8.1. Resultado obtenido

```text
Breakpoint 1, main () at codigo/03_gdb_basico.cpp:14
14          int numero = 5;
```

### 8.2. Explicación

El comando `run` inicia la ejecución del programa dentro del depurador.

En este caso, el programa se detuvo al llegar al breakpoint establecido en la función `main()`.

GDB mostró la primera instrucción que estaba por ejecutarse:

```cpp
int numero = 5;
```

Esto permitió observar el estado del programa antes de continuar con las siguientes instrucciones.

---

## 9. Ejecución paso a paso con `next`

Se utilizó el comando:

```gdb
next
```

### 9.1. Explicación

El comando `next` permite ejecutar la instrucción actual y detenerse en la siguiente línea del mismo nivel de ejecución.

Cuando la instrucción contiene una llamada a una función, `next` ejecuta esa función completa sin entrar a examinar sus instrucciones internas.

Esto permite avanzar por el programa de manera controlada.

En este ejercicio se utilizó para observar los valores de las variables después de ejecutar las instrucciones correspondientes.

---

## 10. Inspección de la variable `numero`

Después de ejecutar la primera instrucción mediante `next`, se utilizó:

```gdb
print numero
```

### 10.1. Resultado obtenido

```text
$1 = 5
```

### 10.2. Análisis

El resultado confirma que la variable `numero` contiene el valor `5`.

Este valor coincide con la asignación realizada dentro de la función `main()`:

```cpp
int numero = 5;
```

El comando `print` permitió consultar el contenido de la variable sin modificar su valor.

---

## 11. Inspección de la variable `doble`

Se avanzó mediante:

```gdb
next
```

Después se ejecutó:

```gdb
print doble
```

### 11.1. Resultado obtenido

```text
$2 = 10
```

### 11.2. Análisis

El resultado confirma que la variable `doble` contiene el valor `10`.

Esto corresponde a la ejecución de:

```cpp
int doble = duplicar(numero);
```

Como `numero` contiene `5`, la función `duplicar()` realiza la siguiente operación:

\[
5 \times 2 = 10
\]

GDB permitió verificar que la función devolvió el valor esperado.

---

## 12. Inspección de la variable `total`

Se ejecutó nuevamente:

```gdb
next
```

Posteriormente se utilizó:

```gdb
print total
```

### 12.1. Resultado obtenido

```text
$3 = 20
```

### 12.2. Análisis

La variable `total` contiene el valor `20`.

Esto corresponde a la instrucción:

```cpp
int total = sumar(doble, 10);
```

Como `doble` contiene `10`, la operación realizada es:

\[
10 + 10 = 20
\]

Por lo tanto, el valor observado coincide con el resultado esperado.

---

## 13. Continuación de la ejecución

Después de inspeccionar las variables se utilizó:

```gdb
continue
```

### 13.1. Resultado obtenido

```text
Número: 5
Doble: 10
Total: 20
[Inferior 1 (process 33388) exited normally]
```

### 13.2. Explicación

El comando `continue` permite reanudar la ejecución del programa después de haber sido detenido por un breakpoint.

En este caso, el programa continuó ejecutándose hasta finalizar.

La salida obtenida fue correcta y GDB indicó que el proceso terminó normalmente.

Esto demuestra que la ejecución controlada mediante el depurador no modificó los resultados del programa.

---

## 14. Evidencia completa de depuración

Para recopilar los resultados de forma ordenada se realizó una ejecución automatizada de GDB utilizando la opción `-batch`.

El comando utilizado fue:

```bash
gdb -q -batch \
  -ex "break main" \
  -ex "run" \
  -ex "next" \
  -ex "print numero" \
  -ex "next" \
  -ex "print doble" \
  -ex "next" \
  -ex "print total" \
  -ex "continue" \
  ./gdb_basico
```

### 14.1. Salida obtenida

```text
Breakpoint 1 at 0x11cb: file codigo/03_gdb_basico.cpp, line 14.

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.ubuntu.com>
Enable debuginfod for this session? (y or [n]) [answered N; input not from terminal]
Debuginfod has been disabled.
To make this setting permanent, add 'set debuginfod enabled off' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, main () at codigo/03_gdb_basico.cpp:14
14          int numero = 5;
15          int doble = duplicar(numero);
$1 = 5
16          int total = sumar(doble, 10);
$2 = 10
18          std::cout << "Número: " << numero << std::endl;
$3 = 20
Número: 5
Doble: 10
Total: 20
[Inferior 1 (process 33388) exited normally]
```

### 14.2. Interpretación de la evidencia

La salida muestra que GDB estableció correctamente un breakpoint en la función `main()`.

Después de iniciar la ejecución, el programa se detuvo en la línea 14.

Mediante el comando `next` se avanzó por las instrucciones del programa.

Se inspeccionaron las tres variables principales utilizando `print`:

| Variable | Valor observado | Valor esperado |
|---|---:|---:|
| `numero` | 5 | 5 |
| `doble` | 10 | 10 |
| `total` | 20 | 20 |

Todos los valores observados coincidieron con los esperados.

Finalmente, el programa continuó y terminó normalmente.

### 14.3. Mensaje de Debuginfod

Durante la ejecución apareció un mensaje relacionado con `debuginfod`.

Este servicio permite descargar información adicional de depuración para algunas bibliotecas del sistema.

En la ejecución automatizada, GDB desactivó esta función y continuó normalmente.

Esto no afectó la depuración del programa, ya que el ejecutable había sido compilado utilizando la opción `-g`.

---

## 15. Explicación de los comandos principales de GDB

| Comando | Función |
|---|---|
| `break main` | Establece un punto de interrupción al inicio de `main()` |
| `run` | Inicia la ejecución del programa |
| `next` | Ejecuta la instrucción actual sin entrar en las funciones llamadas |
| `print` | Permite consultar el valor de una variable o expresión |
| `continue` | Reanuda la ejecución hasta otro breakpoint o hasta finalizar |
| `quit` | Cierra el depurador GDB |

Estos comandos permiten realizar una depuración básica de manera controlada.

---

## 16. Preguntas de reflexión

### 16.1. ¿Qué es un breakpoint?

Un breakpoint es un punto de interrupción que permite detener temporalmente la ejecución de un programa en una ubicación específica.

Su propósito es permitir que el programador examine el estado del programa antes de continuar.

Por ejemplo, se puede utilizar para inspeccionar variables, revisar el flujo de ejecución e identificar posibles errores.

En este ejercicio se utilizó `break main` para detener el programa al comenzar la función principal.

### 16.2. ¿Qué diferencia hay entre ejecutar el programa normalmente y ejecutarlo dentro de GDB?

Cuando se ejecuta un programa normalmente, sus instrucciones se procesan de manera continua hasta que termina o encuentra un error.

En cambio, al ejecutarlo dentro de GDB es posible controlar su ejecución.

El depurador permite establecer puntos de interrupción, avanzar paso a paso e inspeccionar variables mientras el programa está funcionando.

En este ejercicio, la ejecución normal mostró directamente los resultados finales:

```text
Número: 5
Doble: 10
Total: 20
```

Mientras que mediante GDB fue posible observar los valores de las variables antes de que el programa terminara.

### 16.3. ¿Qué ventaja tiene inspeccionar variables mientras el programa se ejecuta?

Inspeccionar variables permite conocer el estado del programa en diferentes momentos de su ejecución.

Esto facilita identificar valores incorrectos y determinar en qué momento se produce un error.

También permite verificar que las operaciones y funciones estén generando los resultados esperados.

En este ejercicio se comprobó que las variables `numero`, `doble` y `total` contenían los valores `5`, `10` y `20`, respectivamente.

Esta técnica resulta especialmente útil cuando un programa tiene muchas operaciones y es necesario encontrar el punto donde comienza un comportamiento incorrecto.

### 16.4. ¿Por qué `next` no entra dentro de las funciones?

El comando `next` está diseñado para ejecutar la instrucción actual como una sola operación desde el punto de vista del nivel de ejecución donde se encuentra el depurador.

Cuando la instrucción contiene una llamada a una función, GDB ejecuta la función completa y se detiene en la siguiente línea del código que realizó la llamada.

Esto permite avanzar por el programa sin necesidad de revisar todas las instrucciones internas de cada función.

Si se desea entrar dentro de una función para observar su ejecución paso a paso, se utiliza el comando `step`.

En este ejercicio, `next` permitió ejecutar las funciones `duplicar()` y `sumar()` sin entrar en sus instrucciones internas.

---

## 17. Reflexión sobre la actividad

Esta actividad permitió comprender la utilidad de GDB como herramienta para analizar el comportamiento de programas escritos en C++.

A diferencia de una ejecución normal, el depurador permitió detener el programa en una línea específica y observar los valores de las variables durante su ejecución.

También se comprendió la utilidad de los puntos de interrupción y del comando `next` para avanzar de manera controlada por el código.

La inspección de las variables permitió confirmar que las funciones realizaban correctamente sus operaciones.

Aunque el programa no contenía errores, el ejercicio mostró cómo utilizar estas herramientas para investigar el comportamiento de programas más complejos.

---

## 18. Conclusión

Se completó correctamente la introducción al uso del depurador GDB.

Se compiló un programa de C++ utilizando información de depuración y se verificó su ejecución normal.

Posteriormente, se utilizó GDB para establecer un breakpoint en la función `main()`, ejecutar instrucciones paso a paso e inspeccionar los valores de las variables.

Los valores observados fueron:

- `numero = 5`
- `doble = 10`
- `total = 20`

Todos coincidieron con los resultados esperados.

Finalmente, el programa continuó ejecutándose y terminó normalmente.

Este ejercicio permitió comprender cómo GDB facilita la inspección del estado interno de un programa y cómo puede utilizarse para identificar problemas durante la ejecución.

Los conocimientos adquiridos servirán como base para analizar errores de ejecución y utilizar comandos más avanzados de depuración en las siguientes partes del laboratorio.
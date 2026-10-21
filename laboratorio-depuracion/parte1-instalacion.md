# Parte 1: Instalación y verificación del ambiente

## 1. Objetivo

Verificar que el entorno de trabajo cuenta con las herramientas necesarias para compilar, ejecutar y depurar programas escritos en C++.

En esta parte se comprueba la disponibilidad del compilador `g++`, el depurador `gdb` y la herramienta de análisis de memoria `valgrind`. Además, se compila y ejecuta un programa sencillo para verificar el funcionamiento del ambiente.

## 2. Entorno de trabajo

Para desarrollar el laboratorio se utilizó **GitHub Codespaces**, un entorno de desarrollo en la nube que permite trabajar con Linux desde el navegador.

Se seleccionó esta alternativa porque permite acceder a las herramientas de desarrollo sin necesidad de instalar programas en la computadora local.

El sistema operativo utilizado fue:

```text
Ubuntu 24.04.5 LTS (Noble Numbat)
```

Para verificar el sistema operativo se ejecutó:

```bash
cat /etc/os-release
```

Resultado obtenido:

```text
PRETTY_NAME="Ubuntu 24.04.5 LTS"
NAME="Ubuntu"
VERSION_ID="24.04"
VERSION="24.04.5 LTS (Noble Numbat)"
VERSION_CODENAME=noble
ID=ubuntu
ID_LIKE=debian
```

## 3. Verificación de herramientas

### 3.1. Compilador g++

Se ejecutó el siguiente comando:

```bash
g++ --version
```

Resultado obtenido:

```text
g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

**Explicación:**

`g++` es un compilador que permite transformar el código fuente escrito en C++ en un programa ejecutable.

Además, permite identificar errores durante la compilación, como problemas de sintaxis o declaraciones incorrectas.

En este laboratorio se utilizará para compilar los diferentes programas que contienen errores intencionales.

### 3.2. Depurador GDB

Se ejecutó:

```bash
gdb --version
```

Resultado obtenido:

```text
GNU gdb (Ubuntu 15.1-1ubuntu1~24.04.1) 15.1
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```

**Explicación:**

`gdb` es un depurador que permite analizar el comportamiento de un programa durante su ejecución.

Entre sus principales funciones se encuentran:

- Establecer puntos de interrupción o *breakpoints*.
- Ejecutar el programa paso a paso.
- Inspeccionar los valores de las variables.
- Examinar las llamadas entre funciones.
- Identificar el lugar donde ocurre un error de ejecución.

Esta herramienta resulta especialmente útil cuando un programa compila correctamente, pero presenta fallos durante su ejecución.

### 3.3. Valgrind

Se ejecutó:

```bash
valgrind --version
```

Resultado obtenido:

```text
valgrind-3.22.0
```

**Explicación:**

`valgrind` es una herramienta que permite analizar el comportamiento de los programas, especialmente en relación con la administración de memoria.

Mediante su herramienta Memcheck es posible detectar problemas como:

- Pérdidas de memoria (*memory leaks*).
- Accesos inválidos a memoria.
- Lecturas de memoria no inicializada.
- Uso incorrecto de memoria dinámica.

Su utilización permite encontrar errores que no siempre producen fallos visibles durante la ejecución normal de un programa.

## 4. Creación del programa de prueba

Se creó el archivo:

```text
codigo/prueba.cpp
```

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    std::cout << "Ambiente listo para depuración" << std::endl;
    return 0;
}
```

**Explicación del programa:**

El programa incluye la biblioteca `<iostream>` para utilizar operaciones de entrada y salida.

Dentro de la función `main()` se utiliza `std::cout` para mostrar un mensaje en la terminal.

Finalmente, la instrucción `return 0` indica que el programa terminó correctamente.

El objetivo de esta prueba es verificar que el entorno permite compilar y ejecutar programas escritos en C++.

## 5. Compilación del programa

Se utilizó el siguiente comando:

```bash
g++ -g -o prueba codigo/prueba.cpp
```

Donde:

- `g++`: ejecuta el compilador de C++.
- `-g`: incorpora información de depuración al ejecutable.
- `-o prueba`: establece el nombre del archivo ejecutable.
- `codigo/prueba.cpp`: indica el archivo fuente que se desea compilar.

### Resultado de la compilación

La compilación se realizó correctamente.

Para verificarlo también se utilizó:

```bash
g++ -g -o prueba codigo/prueba.cpp && echo "Compilacion exitosa"
```

Resultado obtenido:

```text
Compilacion exitosa
```

Esto confirma que el programa no presentó errores durante la compilación.

## 6. Ejecución del programa

Después de compilar el programa, se ejecutó mediante el comando:

```bash
./prueba
```

### Resultado esperado

```text
Ambiente listo para depuración
```

### Resultado obtenido

```text
Ambiente listo para depuración
```

### Análisis del resultado

El resultado obtenido coincide con el esperado.

Esto demuestra que el compilador funciona correctamente y que el entorno permite ejecutar programas de C++.

No se presentaron errores durante la compilación ni durante la ejecución.

Por lo tanto, se considera que el ambiente está preparado para continuar con las siguientes actividades del laboratorio.

## 7. Verificación de los archivos

Se utilizó el comando:

```bash
ls -R
```

En el momento de la verificación se obtuvo:

```text
.:
codigo  prueba

./codigo:
prueba.cpp
```

Esto permitió confirmar que el archivo fuente y el ejecutable se encontraban dentro de la carpeta del laboratorio.

El archivo `prueba.cpp` contiene el código fuente, mientras que `prueba` corresponde al ejecutable generado durante la compilación.

## 8. Preguntas de reflexión

### 8.1. ¿Para qué sirve g++?

`g++` es un compilador que permite convertir programas escritos en C++ en archivos ejecutables.

También permite detectar errores durante la compilación, como errores de sintaxis, declaraciones incorrectas o incompatibilidades de tipos.

Es una herramienta fundamental porque permite transformar el código que escribe el programador en un programa que puede ejecutar el sistema operativo.

### 8.2. ¿Para qué sirve gdb?

`gdb` es una herramienta de depuración utilizada para analizar el comportamiento de un programa mientras se ejecuta.

Permite detener la ejecución en puntos específicos, observar los valores de las variables y ejecutar instrucciones paso a paso.

Su principal utilidad es facilitar la identificación de errores que pueden resultar difíciles de encontrar únicamente leyendo el código fuente.

### 8.3. ¿Para qué sirve valgrind?

`valgrind` permite analizar diferentes aspectos del comportamiento de un programa.

Una de sus principales aplicaciones es detectar problemas relacionados con el manejo de memoria, como pérdidas de memoria, accesos inválidos y uso de memoria no inicializada.

Esto resulta importante porque algunos errores de memoria pueden pasar desapercibidos cuando se ejecuta un programa normalmente.

### 8.4. ¿Por qué se recomienda compilar con -g al depurar?

Se recomienda utilizar la opción `-g` porque incorpora información de depuración al archivo ejecutable.

Esta información permite que herramientas como GDB relacionen las instrucciones del programa con las líneas del código fuente original.

De esta manera, se facilita la inspección de variables, el establecimiento de puntos de interrupción y la identificación de errores.

Sin esta información, el proceso de depuración puede ser más complicado, ya que no siempre se dispone de los nombres de variables o de las líneas correspondientes del código fuente.

### 8.5. ¿Qué diferencia hay entre compilar un programa y depurarlo?

Compilar y depurar son procesos diferentes dentro del desarrollo de software.

**Compilar** consiste en transformar el código fuente en un programa ejecutable. Durante este proceso, el compilador revisa que el código cumpla con las reglas del lenguaje y detecta determinados errores.

**Depurar** consiste en analizar el funcionamiento de un programa para identificar y corregir errores.

Un programa puede compilar correctamente y aun así contener errores lógicos, problemas de memoria o fallos durante la ejecución.

Por esta razón, una compilación exitosa no garantiza que el programa funcione correctamente.

## 9. Reflexión sobre la actividad

Esta primera actividad permitió verificar la importancia de contar con un ambiente de desarrollo correctamente configurado antes de comenzar a depurar programas.

También permitió reconocer las funciones de tres herramientas importantes para el desarrollo en C++: `g++`, `gdb` y `valgrind`.

Aunque en esta parte únicamente se compiló y ejecutó un programa sencillo, se pudo comprobar que el entorno de GitHub Codespaces cuenta con las herramientas necesarias para realizar las siguientes actividades.

Además, se identificó la utilidad de la opción `-g` para facilitar el proceso de depuración.

## 10. Conclusión

Se completó correctamente la verificación del ambiente de desarrollo.

Se confirmó que el sistema operativo utilizado es Ubuntu 24.04.5 LTS y que se encuentran disponibles las siguientes herramientas:

| Herramienta | Versión |
|---|---|
| g++ | 13.3.0 |
| GDB | 15.1 |
| Valgrind | 3.22.0 |

También se compiló y ejecutó correctamente el programa `prueba.cpp`, obteniendo el resultado esperado.

Por lo tanto, el entorno se encuentra preparado para continuar con los ejercicios de identificación y corrección de errores que se desarrollarán en las siguientes partes del laboratorio.
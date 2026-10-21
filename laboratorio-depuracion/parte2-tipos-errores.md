# Parte 2: Tipos de errores

## 1. Objetivo

Identificar y comprender diferentes tipos de errores que pueden presentarse durante el desarrollo de programas en C++.

En esta parte se analizan dos casos:

- **Error de sintaxis:** ocurre cuando el código no cumple con las reglas del lenguaje y el compilador no puede generar el ejecutable.
- **Error lógico:** ocurre cuando el programa compila y se ejecuta, pero produce resultados incorrectos debido a un problema en su implementación.

También se busca comprender la diferencia entre los errores detectados durante la compilación y aquellos que requieren analizar el comportamiento del programa.

## 2. Herramientas utilizadas

Para desarrollar los ejercicios se utilizaron las siguientes herramientas:

- **GitHub Codespaces:** entorno Linux en la nube utilizado para escribir, compilar y ejecutar los programas.
- **g++:** compilador utilizado para detectar errores de sintaxis y generar los ejecutables.
- **Terminal Linux:** utilizada para ejecutar los programas y observar sus resultados.
- **Editor de código:** utilizado para revisar las instrucciones y aplicar las correcciones.

Los programas fueron compilados utilizando la opción `-g` para incluir información de depuración.

---

# 3. Ejercicio 1: Error de sintaxis

## 3.1. Objetivo

Identificar un error de sintaxis mediante los mensajes del compilador, corregirlo y verificar que el programa pueda ejecutarse correctamente.

## 3.2. Código original

Se creó el archivo:

`codigo/01_error_sintaxis.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>

int main() {
    std::cout << "Hola mundo" << std::endl
    return 0;
}
```

El código intenta mostrar el mensaje `Hola mundo` en la terminal.

Sin embargo, contiene un error intencional que impide su compilación.

## 3.3. Compilación del programa original

Se utilizó el siguiente comando:

```bash
g++ -g -o error_sintaxis codigo/01_error_sintaxis.cpp
```

### Resultado obtenido

El compilador mostró el siguiente mensaje:

```text
codigo/01_error_sintaxis.cpp: In function ‘int main()’:
codigo/01_error_sintaxis.cpp:4:43: error: expected ‘;’ before ‘return’
    4 |     std::cout << "Hola mundo" << std::endl
      |                                           ^
      |                                           ;
    5 |     return 0;
      |     ~~~~~~
```

Esto demuestra que el compilador identificó un problema antes de generar el programa ejecutable.

## 3.4. Identificación del error

El mensaje del compilador indica:

```text
error: expected ‘;’ before ‘return’
```

Esto significa que se esperaba un punto y coma antes de la instrucción `return`.

El error se encuentra en la línea 4:

```cpp
std::cout << "Hola mundo" << std::endl
```

En C++, las instrucciones de este tipo deben finalizar con un punto y coma.

Al faltar este símbolo, el compilador no puede interpretar correctamente la separación entre las instrucciones.

## 3.5. Corrección realizada

Se agregó el punto y coma al final de la instrucción.

Código original:

```cpp
std::cout << "Hola mundo" << std::endl
```

Código corregido:

```cpp
std::cout << "Hola mundo" << std::endl;
```

Para realizar la corrección desde la terminal se utilizó:

```bash
sed -i 's/std::endl$/std::endl;/' codigo/01_error_sintaxis.cpp
```

Este comando permitió modificar directamente la línea que contenía el error.

## 3.6. Código corregido completo

El contenido final de `codigo/01_error_sintaxis.cpp` fue:

```cpp
#include <iostream>

int main() {
    std::cout << "Hola mundo" << std::endl;
    return 0;
}
```

## 3.7. Compilación después de la corrección

Se ejecutó:

```bash
g++ -g -o error_sintaxis codigo/01_error_sintaxis.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

Esto confirma que el error de sintaxis fue corregido y que el compilador pudo generar el ejecutable.

## 3.8. Ejecución del programa corregido

Se ejecutó:

```bash
./error_sintaxis
```

### Resultado obtenido

```text
Hola mundo
```

El programa mostró correctamente el mensaje esperado.

Por lo tanto, se verificó que el problema fue solucionado.

## 3.9. Preguntas de reflexión

### 1. ¿Este error fue detectado antes o durante la ejecución?

El error fue detectado antes de la ejecución, específicamente durante el proceso de compilación.

Esto ocurrió porque el código contenía una instrucción que no cumplía con las reglas de sintaxis de C++.

El compilador identificó el problema e impidió que se generara el ejecutable a partir del código incorrecto.

### 2. ¿Qué herramienta detectó el error?

La herramienta que detectó el error fue el compilador `g++`.

Al intentar compilar el programa, mostró un mensaje indicando que faltaba un punto y coma antes de la instrucción `return`.

Además, señaló la línea y la posición donde se encontraba el problema, facilitando su identificación.

### 3. ¿Por qué este tipo de error suele ser más fácil de corregir que un error lógico?

Los errores de sintaxis suelen ser más fáciles de corregir porque el compilador puede detectarlos automáticamente.

Normalmente, proporciona información sobre el tipo de error y su ubicación aproximada dentro del código fuente.

Por el contrario, un error lógico puede permitir que el programa compile y se ejecute normalmente, pero produzca resultados incorrectos.

En esos casos, el programador debe analizar el comportamiento del programa para identificar la causa del problema.

## 3.10. Reflexión del ejercicio

Este ejercicio permitió observar cómo un error pequeño, como la ausencia de un punto y coma, puede impedir completamente la compilación de un programa.

También mostró la importancia de leer cuidadosamente los mensajes del compilador, ya que estos proporcionan información útil para identificar y corregir problemas.

La corrección fue sencilla porque el compilador indicó claramente dónde se encontraba el error.

---

# 4. Ejercicio 2: Error lógico

## 4.1. Objetivo

Identificar un error lógico en un programa que compila y ejecuta correctamente, pero produce un resultado diferente al esperado.

En este caso se analiza una función que debería calcular el promedio de varias notas.

## 4.2. Código original

Se creó el archivo:

`codigo/02_error_logico.cpp`

Con el siguiente contenido:

```cpp
#include <iostream>
#include <vector>

double calcular_promedio(const std::vector<int>& notas) {
    int suma = 0;

    for (int nota : notas) {
        suma += nota;
    }

    return suma;
}

int main() {
    std::vector<int> notas = {80, 90, 100};

    double promedio = calcular_promedio(notas);

    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

El programa utiliza un vector con tres notas y una función llamada `calcular_promedio`.

La función recorre las notas y acumula sus valores en la variable `suma`.

Sin embargo, devuelve directamente la suma en lugar de calcular el promedio.

## 4.3. Compilación del programa original

Se ejecutó:

```bash
g++ -g -o error_logico codigo/02_error_logico.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

El compilador no detectó errores porque el código cumple con las reglas de sintaxis y tipos del lenguaje C++.

## 4.4. Ejecución del programa original

Se utilizó:

```bash
./error_logico
```

### Resultado obtenido

```text
Promedio: 270
```

El programa se ejecutó sin mostrar errores, pero el resultado fue incorrecto.

## 4.5. Resultado esperado

Las notas utilizadas fueron:

| Nota | Valor |
|---|---:|
| Nota 1 | 80 |
| Nota 2 | 90 |
| Nota 3 | 100 |
| **Suma** | **270** |

Para calcular el promedio se debe sumar todas las notas y dividir el resultado entre la cantidad de elementos.

La fórmula es:

\[
\text{Promedio} = \frac{\text{Suma de las notas}}{\text{Cantidad de notas}}
\]

Sustituyendo los valores:

\[
\text{Promedio} = \frac{80 + 90 + 100}{3}
\]

\[
\text{Promedio} = \frac{270}{3} = 90
\]

Por lo tanto, el resultado esperado era:

```text
Promedio: 90
```

### Comparación de resultados

| Resultado | Valor |
|---|---:|
| Resultado original | 270 |
| Resultado esperado | 90 |
| Resultado corregido | 90 |

Esta comparación permitió confirmar que existía un error lógico en el cálculo.

## 4.6. Identificación del error

El problema se encontraba en la siguiente instrucción:

```cpp
return suma;
```

Aunque la función se llamaba `calcular_promedio`, únicamente devolvía la suma de los elementos.

El ciclo `for` acumulaba correctamente las notas:

```cpp
for (int nota : notas) {
    suma += nota;
}
```

Sin embargo, faltaba dividir el valor acumulado entre la cantidad de elementos del vector.

Por esta razón, el programa mostraba `270` en lugar de `90`.

## 4.7. Corrección realizada

Se sustituyó:

```cpp
return suma;
```

Por:

```cpp
return static_cast<double>(suma) / notas.size();
```

Esta modificación permite dividir la suma entre la cantidad de notas.

La expresión `notas.size()` devuelve el número de elementos del vector.

Por otro lado, `static_cast<double>(suma)` convierte la suma a un valor de tipo `double`.

Esto permite realizar una división de punto flotante y conservar los decimales cuando el promedio no es un número entero.

La corrección se aplicó mediante:

```bash
sed -i 's/return suma;/return static_cast<double>(suma) \/ notas.size();/' codigo/02_error_logico.cpp
```

## 4.8. Código corregido completo

El contenido final del archivo fue:

```cpp
#include <iostream>
#include <vector>

double calcular_promedio(const std::vector<int>& notas) {
    int suma = 0;

    for (int nota : notas) {
        suma += nota;
    }

    return static_cast<double>(suma) / notas.size();
}

int main() {
    std::vector<int> notas = {80, 90, 100};

    double promedio = calcular_promedio(notas);

    std::cout << "Promedio: " << promedio << std::endl;

    return 0;
}
```

## 4.9. Compilación después de la corrección

Se ejecutó:

```bash
g++ -g -o error_logico codigo/02_error_logico.cpp && echo "Compilacion exitosa"
```

### Resultado obtenido

```text
Compilacion exitosa
```

El programa volvió a compilar correctamente.

## 4.10. Ejecución del programa corregido

Se ejecutó:

```bash
./error_logico
```

### Resultado obtenido

```text
Promedio: 90
```

El resultado coincide con el promedio calculado manualmente.

Esto demuestra que la corrección solucionó el error lógico.

## 4.11. Preguntas de reflexión

### 1. ¿Por qué el compilador no detectó este error?

El compilador no detectó el error porque el programa era sintácticamente correcto.

La función devolvía un valor entero que podía convertirse automáticamente al tipo `double` declarado como retorno.

Por esta razón, la instrucción `return suma;` era válida desde el punto de vista del lenguaje.

Sin embargo, el compilador no podía determinar que la intención del programador era calcular un promedio y no devolver una suma.

### 2. ¿Por qué este error se considera lógico?

Se considera un error lógico porque el programa compila y se ejecuta correctamente, pero el procedimiento implementado no corresponde con el resultado que se desea obtener.

La función debía calcular un promedio, pero únicamente sumaba las notas.

No existía un problema de sintaxis ni un fallo de ejecución, sino un error en la lógica utilizada para realizar el cálculo.

### 3. ¿Qué estrategia usó para encontrarlo?

La estrategia consistió en ejecutar el programa y comparar el resultado obtenido con el resultado esperado.

Primero se observó que el programa mostraba `Promedio: 270`.

Después se calculó manualmente el promedio de las notas, obteniendo `90`.

Al identificar la diferencia, se revisó la función `calcular_promedio` y se encontró que devolvía la suma sin dividirla entre la cantidad de elementos.

Finalmente, se corrigió la instrucción y se ejecutó nuevamente el programa para verificar el resultado.

### 4. ¿Qué pruebas adicionales podría hacer?

Se podrían realizar varias pruebas utilizando diferentes conjuntos de notas.

Por ejemplo:

- **Notas iguales:** `{80, 80, 80}`. El promedio esperado sería `80`.
- **Notas con decimales en el resultado:** `{80, 81, 82, 84}`. El promedio esperado sería `81.75`.
- **Una sola nota:** `{95}`. El promedio esperado sería `95`.
- **Notas con valor cero:** `{0, 0, 0}`. El promedio esperado sería `0`.
- **Vector vacío:** verificar cómo se comporta la función cuando no existen notas.

En el último caso, sería necesario agregar una validación antes de realizar la división para evitar dividir entre cero.

Estas pruebas permitirían evaluar la función en diferentes situaciones y detectar posibles errores adicionales.

## 4.12. Reflexión del ejercicio

Este ejercicio permitió comprender que un programa puede compilar y ejecutarse correctamente sin necesariamente producir los resultados esperados.

También mostró la importancia de comparar los resultados del programa con cálculos conocidos.

En este caso, calcular manualmente el promedio permitió identificar rápidamente el problema.

Además, se comprendió la utilidad de convertir valores a `double` cuando se realizan operaciones que pueden producir resultados decimales.

---

# 5. Comparación entre errores de sintaxis y errores lógicos

| Característica | Error de sintaxis | Error lógico |
|---|---|---|
| Momento en que se identifica | Durante la compilación | Generalmente durante las pruebas |
| ¿Permite compilar el programa? | No | Sí |
| ¿Permite ejecutar el programa? | No, si no existe un ejecutable válido | Generalmente sí |
| Herramienta utilizada | Compilador g++ | Ejecución y comparación de resultados |
| Ejemplo encontrado | Falta de punto y coma | Devolver una suma en lugar de un promedio |
| Corrección | Agregar `;` | Dividir la suma entre la cantidad de notas |

Los dos ejercicios demuestran que existen diferentes formas en las que un programa puede presentar problemas.

Mientras que los errores de sintaxis normalmente impiden generar el ejecutable, los errores lógicos pueden pasar desapercibidos si no se realizan pruebas adecuadas.

Por este motivo, es importante tanto interpretar los mensajes del compilador como verificar el comportamiento del programa.

# 6. Evidencias generales

## 6.1. Ejercicio de sintaxis

**Compilación original:**

```text
codigo/01_error_sintaxis.cpp:4:43: error: expected ‘;’ before ‘return’
```

**Compilación corregida:**

```text
Compilacion exitosa
```

**Ejecución corregida:**

```text
Hola mundo
```

## 6.2. Ejercicio lógico

**Compilación original:**

```text
Compilacion exitosa
```

**Ejecución original:**

```text
Promedio: 270
```

**Compilación corregida:**

```text
Compilacion exitosa
```

**Ejecución corregida:**

```text
Promedio: 90
```

# 7. Conclusión

Se completaron correctamente los dos ejercicios de identificación y corrección de errores en programas C++.

En el primer ejercicio se identificó un error de sintaxis causado por la ausencia de un punto y coma. El compilador `g++` permitió localizar el problema y, después de corregirlo, el programa compiló y se ejecutó correctamente.

En el segundo ejercicio se identificó un error lógico en una función encargada de calcular el promedio de varias notas. Aunque el programa compilaba correctamente, producía un resultado incorrecto debido a que devolvía la suma en lugar del promedio.

La comparación entre los resultados esperados y los resultados obtenidos permitió encontrar el problema y comprobar que la corrección funcionaba.

Esta actividad permitió comprender que una compilación exitosa no garantiza que un programa funcione correctamente y que las pruebas son fundamentales para identificar errores lógicos.

También se reforzó la importancia de interpretar los mensajes del compilador y verificar los resultados de los programas antes de considerarlos correctos.
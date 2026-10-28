# Partes 6 y 7 — Casos borde y semillas aleatorias

## Objetivo

En estas partes se amplió el conjunto de pruebas para revisar situaciones que no siempre aparecen en los ejemplos habituales: valores límite, números negativos y cadenas vacías. También se añadió una prueba que utiliza números seudoaleatorios con una semilla fija. El objetivo fue comprobar comportamientos especiales y, al mismo tiempo, poder repetir las entradas de una prueba cuando fuera necesario investigar un fallo.

Las verificaciones descritas se realizaron con Google Test y CTest dentro del workflow **C++ testing** de GitHub Actions. Los tiempos y cantidades de pruebas que se muestran provienen de esas ejecuciones.

## Parte 6 — Casos borde

Un caso borde es una entrada ubicada en un límite del dominio válido, cerca de una transición o en una situación especial. Es importante incluirlos porque una función puede comportarse correctamente con valores comunes y fallar justo en sus extremos.

Se añadieron **13 pruebas nuevas** a los archivos de `tests/`, distribuidas de la siguiente manera:

| Módulo | Pruebas añadidas | Qué se comprobó |
|---|---:|---|
| Calculadora | 3 | División entre dos números negativos, división de positivo entre negativo y paridad de cero. |
| Cadenas | 3 | Conversión de cadena vacía a mayúsculas, cadena vacía como palíndromo y palíndromo de un solo carácter. |
| Notas | 7 | Calificaciones `0`, `100`, `-1` y transiciones `59/60`, `69/70`, `79/80`, `89/90`. |
| **Total** | **13** | |

### Calculadora

Las pruebas `DivideNegativeNumbers` y `DividePositiveByNegative` verifican el signo de los resultados:

```cpp
EXPECT_EQ(divide(-10, -2), 5);
EXPECT_EQ(divide(10, -2), -5);
```

También se comprobó que `is_even(0)` devolviera `true`. Aunque cero puede parecer un caso distinto a los números pares positivos, sí es par porque su residuo al dividirlo entre dos es cero.

### Cadenas de texto

Se probaron tres entradas especiales:

```cpp
EXPECT_EQ(to_uppercase(""), "");
EXPECT_TRUE(is_palindrome(""));
EXPECT_TRUE(is_palindrome("a"));
```

Estas comprobaciones son útiles porque una cadena vacía tiene longitud cero y puede causar errores en algoritmos que suponen que siempre existe al menos un carácter. En la implementación utilizada, tanto la cadena vacía como una cadena de un carácter se consideran palíndromos.

### Calificaciones

Para `letter_grade`, se comprobaron los dos extremos válidos: `0` debe producir `'F'` y `100` debe producir `'A'`. También se verificó que `-1` lanzara `std::invalid_argument`, en lugar de tratarse como una nota válida.

Las transiciones entre letras se revisaron a ambos lados de cada umbral:

| Valores | Resultados esperados |
|---|---|
| `59` y `60` | `'F'` y `'D'` |
| `69` y `70` | `'D'` y `'C'` |
| `79` y `80` | `'C'` y `'B'` |
| `89` y `90` | `'B'` y `'A'` |

Por ejemplo, `69` y `70` son especialmente relevantes porque `70` es el inicio del rango de aprobación en este proyecto. Verificar ambos lados ayuda a detectar errores como usar `>` cuando corresponde `>=`.

### Resultado de la Parte 6

Antes de incorporar estos casos, la suite tenía **27 pruebas**. Después de añadir las 13 pruebas de borde, el registro de GitHub Actions mostró:

```text
100% tests passed, 0 tests failed out of 40
Total Test time (real) =   0.25 sec
```

[Evidencia: ejecución con 40 pruebas](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40728756527).

Los cambios quedaron registrados en tres commits de [calculadora](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/8605f24561), [cadenas](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/f438e7dda9) y [notas](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/1cb8441b0c).

## Parte 7 — Prueba seudoaleatoria reproducible

Se añadió `CalculatorTest.RandomAdditionsWithFixedSeed` en `tests/test_calculator.cpp`. La prueba utiliza el generador `std::mt19937`, inicializado con la semilla `12345`, y selecciona valores enteros entre `-100` y `100`:

```cpp
TEST(CalculatorTest, RandomAdditionsWithFixedSeed) {
    std::mt19937 generator(12345);
    std::uniform_int_distribution<int> distribution(-100, 100);

    for (int i = 0; i < 10; i++) {
        int a = distribution(generator);
        int b = distribution(generator);
        EXPECT_EQ(add(a, b), a + b);
    }
}
```

En cada iteración se generan dos números y se comprueba que `add(a, b)` coincida con `a + b`. Aunque el ciclo realiza **10 comprobaciones**, Google Test lo registra como **una sola prueba**, por eso el total pasó de 40 a 41.

La semilla fija permite obtener la misma secuencia de entrada al repetir la prueba en el mismo entorno. Esto facilita reproducir un posible error. No significa que se hayan evaluado todas las combinaciones posibles de números.

### Experimento de cambio de semilla

Primero se ejecutó la prueba con `12345`. Después se cambió temporalmente la semilla a `54321` y, finalmente, se restauró `12345`. En los tres casos la suite terminó correctamente:

| Etapa | Semilla | Resultado de CTest | Tiempo |
|---|---:|---|---:|
| Prueba añadida | `12345` | 41/41 pruebas exitosas | 0.32 s |
| Cambio temporal | `54321` | 41/41 pruebas exitosas | 0.28 s |
| Semilla restaurada | `12345` | 41/41 pruebas exitosas | 0.12 s |

Evidencias:
- [Primera ejecución con semilla fija](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40728778476).
- [Ejecución con semilla 54321](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40729103570).
- [Ejecución con semilla 12345 restaurada](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40729116806).

Los tres resultados fueron satisfactorios. Cambiar la semilla modifica los valores generados, pero no necesariamente produce un fallo: si la función de suma funciona correctamente para esas entradas, las comprobaciones seguirán pasando. Las diferencias en el tiempo total tampoco permiten concluir que una semilla sea mejor que otra.

## Reflexión — Casos borde

1. **¿Qué es un caso borde?** Es una entrada situada en un extremo permitido, justo fuera de él o cerca de un punto donde cambia el comportamiento de la función. Por ejemplo, `69` y `70` permiten revisar el cambio de clasificación de `'D'` a `'C'`.

2. **¿Por qué probar cero y valores negativos?** Porque pueden revelar errores de signo, comparaciones incorrectas o suposiciones sobre entradas positivas. En este laboratorio se revisó que cero fuera par y que la división con números negativos produjera el signo esperado.

3. **¿Por qué probar cadenas vacías?** Porque algunas funciones no manejan correctamente una entrada sin caracteres. Las pruebas permiten comprobar que `to_uppercase("")` e `is_palindrome("")` respondan según el comportamiento definido.

4. **¿Qué valor tiene probar exactamente 69 y 70?** Son valores consecutivos a ambos lados de un umbral: `69` se clasifica como `'D'` y `70` como `'C'`. Así se puede detectar si la condición incluye correctamente el límite.

5. **¿Son suficientes solo los casos normales?** No. Los casos normales ayudan a verificar el funcionamiento básico, pero conviene complementarlos con límites, entradas especiales y valores inválidos. De esa manera se revisan comportamientos que podrían pasar inadvertidos.

## Reflexión — Semillas

1. **¿Qué es una semilla aleatoria?** Es el valor inicial utilizado por un generador seudoaleatorio para producir una secuencia de números.

2. **¿Por qué fijar una semilla?** Porque permite repetir las mismas entradas en el mismo entorno y facilita investigar un fallo sin depender de valores distintos en cada ejecución.

3. **¿Qué sucedió al cambiarla?** Se cambió de `12345` a `54321`. La secuencia de números generados fue distinta, pero las 41 pruebas continuaron pasando. Después se restauró la semilla original.

4. **¿Por qué importa la reproducibilidad?** Porque, si una prueba falla, poder repetir las entradas facilita localizar la causa y verificar una corrección. También ayuda a comparar ejecuciones sin introducir cambios innecesarios en los datos de prueba.

## Conclusión

Los casos borde ampliaron las comprobaciones más allá de los ejemplos habituales y permitieron revisar situaciones especiales de los tres módulos. La prueba con semilla fija agregó otra forma de evaluar la suma usando varias entradas sin perder la posibilidad de reproducirlas. Las ejecuciones de GitHub Actions confirmaron **40 pruebas exitosas** después de los casos borde y **41 pruebas exitosas** al añadir la prueba seudoaleatoria. Esto respalda el comportamiento observado en esos casos, aunque no garantiza que el programa esté libre de errores para cualquier entrada.

**Archivos relacionados:** [test_calculator.cpp](../tests/test_calculator.cpp), [test_string_utils.cpp](../tests/test_string_utils.cpp) y [test_grade_utils.cpp](../tests/test_grade_utils.cpp).

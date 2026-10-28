# Partes 2, 3 y 4 — Implementación y pruebas unitarias

## Objetivo

En estas actividades se implementaron funciones sencillas en C++ y se comprobaron con pruebas unitarias de Google Test. La idea fue verificar no solo que las operaciones habituales funcionaran, sino también que el programa respondiera de manera adecuada ante entradas especiales. Después se comparó el comportamiento de las aserciones `EXPECT_` y `ASSERT_` mediante un fallo provocado de forma temporal.

La compilación y las pruebas se ejecutaron en GitHub Actions. Los resultados que se mencionan a continuación corresponden a registros reales del workflow `C++ testing`, no a ejecuciones locales.

## Parte 2 — Implementación de los módulos

El proyecto organiza las declaraciones en `include/` y las implementaciones en `src/`. Se trabajó con tres módulos:

| Módulo | Funciones | Comportamiento principal |
|---|---|---|
| `calculator` | `add`, `subtract`, `multiply`, `divide`, `is_even` | Operaciones aritméticas y comprobación de números pares. |
| `string_utils` | `to_uppercase`, `is_palindrome`, `count_vowels` | Conversión a mayúsculas, detección de palíndromos y conteo de vocales. |
| `grade_utils` | `average`, `is_passing`, `letter_grade` | Promedio de notas, condición de aprobación y clasificación por letra. |

La función `divide` lanza `std::invalid_argument` cuando el divisor es cero. De manera similar, `average` rechaza un vector vacío y `letter_grade` rechaza calificaciones fuera de 0 a 100. Es importante probar estos casos porque un resultado correcto con entradas normales no garantiza que se manejen bien los errores.

Más adelante se añadió `is_valid_grade` como parte del mini reto de la Parte 12; no formaba parte del conjunto inicial de 25 pruebas.

**Archivos consultados:** [calculator.cpp](../src/calculator.cpp), [string_utils.cpp](../src/string_utils.cpp), [grade_utils.cpp](../src/grade_utils.cpp).

## Parte 3 — Primer conjunto de pruebas unitarias

Las pruebas se escribieron en `tests/` utilizando Google Test. Cada caso llama a una función con una entrada concreta y compara su resultado con lo esperado. En el primer conjunto había **25 pruebas**: ocho de calculadora, siete de cadenas y diez de calificaciones.

Algunos ejemplos representativos son:

| Prueba | Entrada o condición | Comprobación |
|---|---|---|
| `CalculatorTest.AddPositiveNumbers` | `add(2, 3)` | El resultado debe ser `5`. |
| `CalculatorTest.DivideByZeroThrowsException` | `divide(10, 0)` | Debe lanzar `std::invalid_argument`. |
| `StringUtilsTest.DetectPalindromeWithSpaces` | `"anita lava la tina"` | Debe reconocer el palíndromo. |
| `StringUtilsTest.CountVowels` | `"murcielago"` | Debe contar cinco vocales. |
| `GradeUtilsTest.CalculateAverage` | `{80, 90, 100}` | El promedio debe ser `90.0`. |
| `GradeUtilsTest.InvalidGradeThrowsException` | `letter_grade(120)` | Debe lanzar `std::invalid_argument`. |

Se utilizaron aserciones como `EXPECT_EQ`, `EXPECT_TRUE`, `EXPECT_FALSE`, `EXPECT_DOUBLE_EQ` y `EXPECT_THROW`, según el tipo de resultado que se necesitaba verificar. Esto permite que el fallo indique con mayor claridad qué condición no se cumplió.

### Cómo se ejecutan

Desde la raíz del repositorio, el procedimiento de configuración, compilación y pruebas es:

```bash
cmake -S laboratorio-testing -B laboratorio-testing/build
cmake --build laboratorio-testing/build
ctest --test-dir laboratorio-testing/build --output-on-failure
```

CTest ejecuta los casos descubiertos por Google Test y presenta un resumen. El parámetro `--output-on-failure` resulta útil porque muestra los detalles de una prueba cuando no pasa.

### Resultado del primer ciclo

La ejecución **C++ testing #3** del 28 de octubre de 2026 finalizó con éxito:

```text
100% tests passed, 0 tests failed out of 25
Total Test time (real) =   0.42 sec
```

[Evidencia: ejecución inicial con 25 pruebas](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40724257066).

Este resultado confirma que las 25 comprobaciones pasaron con esas versiones del código. No implica que se hayan probado todas las entradas posibles.

## Parte 4 — Diferencia entre EXPECT y ASSERT

Para observar cómo se comportan las aserciones, se añadieron dos pruebas al archivo `tests/test_calculator.cpp`:

- `CalculatorTest.MultipleExpectChecks` contiene tres `EXPECT_EQ` que verifican sumas distintas. Si una de estas comprobaciones falla, Google Test puede continuar evaluando las siguientes dentro de la misma prueba.
- `CalculatorTest.AssertBeforeDivision` utiliza `ASSERT_NE(divisor, 0)` antes de realizar una división. Si el divisor es cero, la aserción detiene **esa prueba** y evita ejecutar la operación posterior.

La versión corregida de la segunda prueba es:

```cpp
TEST(CalculatorTest, AssertBeforeDivision) {
    int divisor = 2;
    ASSERT_NE(divisor, 0);
    EXPECT_EQ(divide(10, divisor), 5);
}
```

### Fallo intencional y corrección

Para comprobar el efecto de `ASSERT_NE`, se cambió temporalmente el divisor de `2` a `0`. En la ejecución fallida de GitHub Actions, el registro mostró:

```text
CalculatorTest.AssertBeforeDivision ................***Failed
Expected: (divisor) != (0), actual: 0 vs 0
96% tests passed, 1 tests failed out of 27
```

El trabajo de GitHub Actions terminó con estado **Failure** en el paso `Run tests`. Las otras 26 pruebas sí pasaron. La condición de `ASSERT_NE` evitó continuar con la división dentro de `AssertBeforeDivision`, pero no detuvo toda la suite.

Después se restauró `divisor = 2` y se obtuvo:

```text
100% tests passed, 0 tests failed out of 27
Total Test time (real) =   0.16 sec
```

Evidencias verificadas:
- [Ejecución con fallo intencional de ASSERT](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40726531186).
- [Ejecución después de la corrección](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40726562515).
- [Archivo actual de pruebas de calculadora](../tests/test_calculator.cpp).

La diferencia importante es que `EXPECT_` registra una comprobación fallida sin abandonar inmediatamente la prueba, mientras que `ASSERT_` produce un fallo fatal para la prueba actual. En ambos casos, las demás pruebas pueden seguir ejecutándose.

## Reflexión — Pruebas unitarias

1. **¿Qué significa que una prueba pase?** Significa que, para la entrada y las condiciones evaluadas, el resultado coincidió con lo esperado. Por ejemplo, la prueba de suma pasó cuando `add(2, 3)` devolvió `5`. No significa que la función esté libre de errores en todos los escenarios.
2. **¿Qué significa que falle?** Que alguna condición comprobada no se cumplió o que se presentó un error durante la ejecución. El registro permite identificar la prueba afectada y comparar el resultado obtenido con el esperado.
3. **¿Por qué automatizar en lugar de probar solo manualmente?** Porque permite repetir las mismas comprobaciones después de cada cambio sin tener que ejecutar y revisar cada caso a mano. También ayuda a detectar regresiones, es decir, errores que aparecen en funcionalidades que antes funcionaban.
4. **¿Por qué conviene que las pruebas sean rápidas?** Porque se pueden ejecutar con frecuencia y obtener retroalimentación antes de seguir haciendo cambios. En este laboratorio, el conjunto inicial de 25 pruebas tardó 0.42 segundos en CTest.
5. **¿Por qué deben ser deterministas?** Porque una misma prueba, con las mismas entradas y condiciones, debería producir el mismo resultado. Así es más fácil reproducir un fallo y comprobar que una corrección realmente lo resolvió.

## Reflexión — EXPECT y ASSERT

1. **¿Cuál es la diferencia entre EXPECT y ASSERT?** `EXPECT_` permite seguir ejecutando la prueba después de una comprobación fallida; `ASSERT_` detiene la prueba actual cuando falla. Esto último es útil si continuar podría generar resultados engañosos o un error adicional.
2. **¿Cuándo utilizar EXPECT?** Cuando se quieren revisar varias condiciones independientes. Por ejemplo, en `MultipleExpectChecks` se comprueban tres sumas y tiene sentido obtener información de todas ellas.
3. **¿Cuándo utilizar ASSERT?** Cuando una condición es indispensable para que el resto de la prueba tenga sentido. Antes de dividir, comprobar que el divisor no sea cero evita ejecutar una operación inválida.
4. **¿Qué ocurrió con el divisor en cero?** La condición `ASSERT_NE(divisor, 0)` falló porque ambos valores eran cero. Google Test marcó `AssertBeforeDivision` como fallida, no ejecutó la división posterior y continuó con las otras pruebas. Al restaurar el divisor a `2`, las 27 pruebas pasaron.

## Conclusión

Estas actividades permitieron comprobar tres aspectos del testing: la organización del código en módulos, la utilidad de las pruebas unitarias para verificar comportamientos concretos y la diferencia práctica entre aserciones no fatales y fatales. El fallo provocado en `AssertBeforeDivision` fue especialmente útil para observar que un error puede quedar localizado y documentado sin impedir que el resto de la suite se ejecute. Los registros de GitHub Actions conservan tanto el fallo como su corrección.

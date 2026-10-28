# Parte 5 — Prueba fallida y corrección

## Objetivo

En esta parte se provocó un error pequeño en una función que ya tenía pruebas unitarias. La intención no era agregar una funcionalidad nueva, sino comprobar que las pruebas podían detectar un cambio incorrecto y que, después de corregirlo, el proyecto volvía a pasar todas las verificaciones.

El experimento se realizó sobre `is_even(int number)`, una función del módulo de calculadora que determina si un número es par. Los resultados se comprobaron en el workflow **C++ testing** de GitHub Actions. Se conservan las dos ejecuciones, una fallida y otra exitosa, para poder comparar lo que ocurrió.

## 1. Comportamiento esperado

La función debe devolver `true` cuando un entero es par y `false` cuando es impar. Su condición correcta es:

```cpp
bool is_even(int number) {
    return number % 2 == 0;
}
```

El operador `%` calcula el residuo de la división entera. Un número par deja residuo cero al dividirse entre dos; por eso la comparación debe hacerse con `0`.

Antes de introducir el error ya existían dos pruebas en `tests/test_calculator.cpp`:

```cpp
TEST(CalculatorTest, DetectEvenNumber) {
    EXPECT_TRUE(is_even(8));
}

TEST(CalculatorTest, DetectOddNumber) {
    EXPECT_FALSE(is_even(7));
}
```

Estas pruebas comprueban las dos respuestas posibles de la función: `8` debe reconocerse como par y `7` como impar. Son sencillas, pero suficientes para detectar el error que se introdujo en este ejercicio.

## 2. Introducción del error intencional

En `src/calculator.cpp` se cambió temporalmente la condición correcta:

```cpp
return number % 2 == 0;
```

por esta condición incorrecta:

```cpp
return number % 2 == 1;
```

Con el cambio, `is_even(8)` devuelve `false`, aunque 8 es par. A la vez, `is_even(7)` devuelve `true`, aunque 7 es impar. Es decir, el código sigue siendo válido en C++ y puede compilar, pero su comportamiento ya no coincide con el requisito.

El cambio quedó registrado en el commit [`736ff062` — Probando fallo en is_evens](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/736ff062b8ae01ab66fb73604c91cf8e22af6cf0).

## 3. Resultado de la ejecución fallida

Después de publicar el cambio, GitHub Actions configuró y compiló el proyecto correctamente. El fallo apareció en el paso **Run tests**, cuando CTest ejecutó las pruebas de Google Test.

El registro mostró el siguiente resultado para el número par:

```text
CalculatorTest.DetectEvenNumber ........***Failed
Value of: is_even(8)
  Actual: false
Expected: true
```

También falló la prueba del número impar:

```text
CalculatorTest.DetectOddNumber .........***Failed
Value of: is_even(7)
  Actual: true
Expected: false
```

Al finalizar, CTest presentó este resumen:

```text
93% tests passed, 2 tests failed out of 27
Total Test time (real) =   0.11 sec

The following tests FAILED:
  7 - CalculatorTest.DetectEvenNumber (Failed)
  8 - CalculatorTest.DetectOddNumber (Failed)

Error: Process completed with exit code 8.
```

De las **27 pruebas**, **25 pasaron y 2 fallaron**. Esto es importante porque el problema no impidió compilar el programa ni ejecutar las demás pruebas: quedó identificado en dos casos concretos. El estado del workflow fue **Failure**, tal como se esperaba para el experimento.

**Evidencia:** [GitHub Actions — ejecución fallida](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40727952047).

## 4. Corrección y nueva ejecución

Una vez observado el fallo, se restauró la condición original en `src/calculator.cpp`:

```cpp
bool is_even(int number) {
    return number % 2 == 0;
}
```

La corrección quedó registrada en el commit [`671a62b6` — Corrigiendo prueba de numeros pares](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/671a62b6b816016b621550e486999d8cbe86cdfb).

En la siguiente ejecución de GitHub Actions, las dos pruebas que antes fallaban aparecieron como `Passed`. El resumen fue:

```text
CalculatorTest.DetectEvenNumber ........ Passed
CalculatorTest.DetectOddNumber ......... Passed

100% tests passed, 0 tests failed out of 27
Total Test time (real) =   0.10 sec
```

Esta vez el workflow terminó con estado **Success**. La comparación entre ambas ejecuciones permite relacionar directamente el error introducido, los fallos detectados y la corrección aplicada.

**Evidencia:** [GitHub Actions — ejecución corregida](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40728336170).

## 5. Comparación de resultados

| Aspecto | Con el error | Después de corregirlo |
|---|---|---|
| Condición de `is_even` | `number % 2 == 1` | `number % 2 == 0` |
| `DetectEvenNumber` | Falló | Pasó |
| `DetectOddNumber` | Falló | Pasó |
| Pruebas exitosas | 25 de 27 | 27 de 27 |
| Estado de GitHub Actions | Failure | Success |
| Tiempo total de CTest | 0.11 s | 0.10 s |

Para repetir la verificación desde la raíz del repositorio se utilizan estos comandos:

```bash
cmake -S laboratorio-testing -B laboratorio-testing/build
cmake --build laboratorio-testing/build
ctest --test-dir laboratorio-testing/build --output-on-failure
```

El parámetro `--output-on-failure` hace que CTest muestre el detalle de las pruebas que no pasan, lo que facilita identificar la causa. Los resultados documentados aquí corresponden a **GitHub Actions**, no a una ejecución local.

## 6. Reflexión

1. **¿Qué aportó introducir un error intencional?** Permitió comprobar con un ejemplo real que las pruebas no solo sirven para mostrar resultados exitosos. Al cambiar una condición de `is_even`, las pruebas señalaron exactamente los dos comportamientos incorrectos. Esto ayuda a entender por qué es útil ejecutar la suite después de modificar el código.

2. **¿Por qué es útil conservar una prueba que detectó un bug?** Porque puede detectar si el mismo error aparece otra vez en el futuro. En este caso, las pruebas de números pares e impares siguen siendo útiles aunque la función ya esté corregida: si alguien modifica nuevamente la condición de forma incorrecta, ambas pueden advertirlo.

3. **¿Qué diferencia hay entre un fallo de prueba y uno de compilación?** Un fallo de compilación ocurre cuando no se puede construir el programa, por ejemplo, debido a un error de sintaxis. En este experimento la compilación sí terminó, pero las pruebas fallaron porque la función devolvía valores diferentes de los esperados. Son problemas distintos y se investigan en etapas diferentes del proceso.

4. **¿Cómo se confirmó la corrección?** Primero se restauró la comparación con residuo cero. Luego se ejecutó nuevamente la suite en GitHub Actions y se comprobó que `DetectEvenNumber` y `DetectOddNumber` pasaran. El resumen de **27 pruebas exitosas y ninguna fallida** confirmó que el error observado había quedado corregido en esos casos.

## Conclusión

Este ejercicio mostró de forma práctica cómo una modificación de una sola línea puede cambiar el comportamiento de una función sin producir errores de compilación. Las pruebas unitarias permitieron detectar el problema, localizarlo y verificar la corrección. Además, conservar las ejecuciones fallida y exitosa en GitHub Actions deja evidencia de ambas etapas y hace más fácil explicar qué ocurrió.

Este fallo de `is_even` corresponde a la **Parte 5**. Es distinto del fallo intencional de `CalculatorTest.AddPositiveNumbers` utilizado posteriormente para demostrar la integración continua en la **Parte 11**.

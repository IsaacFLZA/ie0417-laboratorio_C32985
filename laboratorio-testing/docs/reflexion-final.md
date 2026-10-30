# Partes 12 y 13 — Mini reto y reflexión final

## Mini reto de testing: `is_valid_grade(int grade)`

### Función implementada

Como parte del mini reto se incorporó la declaración de `is_valid_grade(int grade)` en [`include/grade_utils.h`](../include/grade_utils.h) y su implementación en [`src/grade_utils.cpp`](../src/grade_utils.cpp):

```cpp
bool is_valid_grade(int grade) {
    return grade >= 0 && grade <= 100;
}
```

La función devuelve `true` cuando la nota está dentro del rango **inclusivo de 0 a 100**, y `false` cuando queda fuera. A diferencia de `letter_grade()`, que lanza una excepción para una nota inválida, esta función solo indica si la entrada es válida.

### Casos de prueba diseñados

Se incorporaron seis pruebas en [`tests/test_grade_utils.cpp`](../tests/test_grade_utils.cpp), con casos normales, valores límite y entradas inmediatamente fuera del rango:

| Prueba de Google Test | Entrada | Resultado esperado | Tipo de caso |
|---|---:|---|---|
| `GradeUtilsTest.ValidGradeTypical` | `85` | `true` | Normal válido |
| `GradeUtilsTest.InvalidGradeTypical` | `150` | `false` | Normal inválido |
| `GradeUtilsTest.ValidGradeLowerBoundary` | `0` | `true` | Borde inferior válido |
| `GradeUtilsTest.ValidGradeUpperBoundary` | `100` | `true` | Borde superior válido |
| `GradeUtilsTest.InvalidGradeBelowMinimum` | `-1` | `false` | Inmediatamente debajo del mínimo |
| `GradeUtilsTest.InvalidGradeAboveMaximum` | `101` | `false` | Inmediatamente encima del máximo |

Se escogieron estos casos para comprobar tanto el comportamiento habitual como la inclusión de los extremos. Los valores `-1` y `101` ayudan a detectar errores de comparación, como utilizar `>` en lugar de `>=` o `<` en lugar de `<=`. Los valores `0` y `100` permiten verificar que ambos límites son válidos, no solo los valores intermedios.

Las comprobaciones usan `EXPECT_TRUE` y `EXPECT_FALSE` según el resultado esperado de cada entrada. Las seis forman parte del archivo de pruebas del repositorio; no son casos hipotéticos.

### Ejecución y resultados

Los cambios se incorporaron al repositorio y se verificaron mediante el workflow **C++ testing** de GitHub Actions. En la [ejecución del 28 de octubre de 2026](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031), los seis casos de `is_valid_grade()` aparecen como `Passed`, junto con las demás pruebas:

```text
100% tests passed, 0 tests failed out of 48
```

Las **48 pruebas** corresponden a la suite completa del proyecto, no únicamente al mini reto. En esta ejecución también se generó el [reporte de cobertura HTML](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031/artifacts/12835367540), con 43 de 43 líneas y 12 de 12 funciones instrumentadas ejecutadas. El reporte no presentó datos de ramas; por tanto, no se afirma ningún porcentaje de cobertura de ramas.

Estos resultados proceden de GitHub Actions. No se presenta una ejecución local del mini reto porque no se dispone de un registro que la confirme.

### Reflexión del mini reto

1. **¿Cuál fue el caso más obvio de probar?** Un valor normal dentro del rango, como `85`, porque permite comprobar de forma sencilla que la función acepta una nota válida. La prueba `ValidGradeTypical` verifica que en ese caso devuelva `true`.

2. **¿Cuál fue el caso borde más importante?** Los dos extremos, `0` y `100`, porque determinan si el rango se interpreta correctamente como inclusivo. Si tuviera que destacar uno, sería `100`, ya que una comparación incorrecta con `< 100` lo rechazaría aunque es válido. Ambos extremos están cubiertos por pruebas.

3. **¿Qué error podría aparecer si no se prueban los valores `0` y `100`?** Podría implementarse por equivocación un rango exclusivo, como `grade > 0 && grade < 100`. Esa condición aceptaría notas intermedias, pero rechazaría los dos extremos que sí deben permitirse.

4. **¿Qué diferencia hay entre probar un valor como `50` y probar valores como `-1`, `0`, `100` y `101`?** `50` permite comprobar un valor ordinario dentro del rango, mientras que los otros cuatro verifican el comportamiento exactamente en los límites y justo fuera de ellos. Estos últimos detectan errores que podrían no aparecer con una nota intermedia. La suite utiliza `85` como caso normal válido; `50` se menciona aquí para explicar la comparación solicitada.

5. **¿Qué aprendió sobre diseñar pruebas?** Este ejercicio muestra que no basta con escoger entradas que deberían funcionar. Es necesario partir del requisito, identificar los límites y comprobar también las entradas que deben rechazarse. Un conjunto pequeño, pero bien seleccionado, puede detectar errores en las condiciones del programa.

## Reflexión final

1. **¿Qué es software testing?** Es el proceso de evaluar el comportamiento de un programa mediante comprobaciones que buscan detectar errores y verificar si los resultados coinciden con lo esperado. En este laboratorio se aplicó mediante pruebas automatizadas de funciones escritas en C++.

2. **¿Por qué el testing mejora la calidad del software?** Porque permite detectar comportamientos incorrectos y regresiones antes de dar por terminados los cambios. Por ejemplo, las pruebas de paridad detectaron el error intencional introducido en `is_even()`, que posteriormente fue corregido.

3. **¿Cuál es la diferencia entre verificación y validación?** La verificación consiste en comprobar que el software cumple los requisitos y las especificaciones definidas. La validación busca comprobar que el software realmente satisface la necesidad para la cual fue creado. En otras palabras, una se enfoca en cumplir lo especificado y la otra en que lo construido sea adecuado para su propósito.

4. **¿Qué es una prueba unitaria?** Es una comprobación enfocada en una unidad pequeña de código, como una función. En el proyecto, por ejemplo, se comprueba que `add(2, 3)` devuelva `5` o que `divide(10, 0)` lance la excepción esperada.

5. **¿Qué es una prueba funcional?** Es una prueba que comprueba un comportamiento descrito por un requisito, sin centrarse necesariamente en los detalles internos de la implementación. Los casos de conversión de notas a letras son funcionales porque verifican que las entradas produzcan la categoría o el rechazo solicitado.

6. **¿Qué diferencia hay entre `EXPECT_` y `ASSERT_`?** En Google Test, una aserción `EXPECT_` registra un fallo, pero permite continuar con las siguientes comprobaciones de la prueba actual. Una `ASSERT_` es fatal para esa prueba y la interrumpe si la condición no se cumple. Esto resulta útil cuando continuar podría producir errores adicionales, como intentar dividir después de detectar un divisor cero.

7. **¿Por qué las pruebas deben ser deterministas?** Porque, con las mismas entradas y condiciones, deberían producir resultados consistentes. Esto facilita reproducir una falla, identificar su causa y comprobar que una corrección funciona.

8. **¿Por qué puede ser útil una semilla en pruebas con valores aleatorios?** Una semilla fija permite generar una secuencia seudoaleatoria reproducible en el mismo entorno. En el laboratorio se utilizaron las semillas `12345` y `54321` para probar sumas y se restauró la semilla inicial; las ejecuciones documentadas de esa etapa pasaron.

9. **¿Qué es cobertura de código?** Es una medida de cuánto código se ejecuta durante las pruebas. Puede analizarse por líneas o funciones, entre otras métricas. En la medición inicial del laboratorio se registraron **42/42 líneas y 11/11 funciones**, ambas con 100 % de cobertura.

10. **¿Por qué una cobertura alta no garantiza ausencia de errores?** Porque ejecutar una línea no significa comprobar todos sus posibles resultados o entradas. Una función puede alcanzar 100 % de cobertura de líneas y aun así tener errores en situaciones no evaluadas. Además, en este laboratorio no se obtuvo un porcentaje de cobertura de ramas.

11. **¿Qué ventaja tiene ejecutar pruebas en GitHub Actions?** Permite compilar y comprobar el proyecto automáticamente al publicar cambios relevantes, con registros que pueden consultarse después. Además, ofrece un entorno de ejecución que no depende de tener todas las herramientas instaladas localmente.

12. **¿Qué parte del laboratorio le pareció más útil?** La integración de las pruebas con GitHub Actions, porque permitió revisar los resultados de manera automática y conservar evidencias de ejecuciones exitosas. También ayudó a relacionar los cambios del código con sus comprobaciones.

13. **¿Qué parte le pareció más difícil?** Adaptar el desarrollo y la medición de cobertura para trabajar desde el navegador, sin contar con Codespaces ni con las herramientas instaladas localmente. Esto hizo necesario prestar más atención a la configuración de CMake, del workflow y a la interpretación de los registros.

14. **¿Cómo aplicaría pruebas automatizadas en un proyecto futuro?** Definiría las pruebas a partir de los requisitos desde etapas tempranas, incluyendo entradas normales, casos borde e inválidos. Después integraría su ejecución automática en cada cambio importante y usaría los resultados y la cobertura como apoyo para mejorar la calidad del proyecto.

## Estado y conclusión

El mini reto quedó incorporado al código y sus **seis pruebas pasaron** en GitHub Actions, dentro de una ejecución de **48 pruebas exitosas**. Los documentos anteriores registran las etapas de pruebas unitarias, errores intencionales, casos borde, cobertura e integración continua. Las cifras de cada etapa corresponden a ejecuciones distintas y no deben confundirse con una única medición.

Este laboratorio permitió practicar una idea central del testing: comprobar un programa requiere elegir entradas con intención, expresar resultados esperados y revisar la evidencia cuando algo falla. La automatización facilita repetir estas comprobaciones, pero sigue siendo importante interpretar los registros y reconocer que ninguna suite finita garantiza la ausencia de errores.

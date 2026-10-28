# Partes 2, 3 y 4 — Implementación y pruebas unitarias

## Módulos
- `calculator`: `add`, `subtract`, `multiply`, `divide`, `is_even`.
- `string_utils`: `to_uppercase`, `is_palindrome`, `count_vowels`.
- `grade_utils`: `average`, `is_passing`, `letter_grade`. En el reto se agregó `is_valid_grade`.

Los encabezados en `include/` declaran las funciones y los archivos `src/` contienen su implementación.

## Primer ciclo de pruebas
Se redactaron 25 pruebas iniciales repartidas entre calculadora, cadenas y notas. La ejecución **C++ testing #3** de GitHub Actions confirmó:

```text
100% tests passed, 0 tests failed out of 25
Total Test time (real) = 0.42 sec
```

Evidencia: https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40724257066

## EXPECT frente a ASSERT
Se agregaron `MultipleExpectChecks`, con tres `EXPECT_EQ`, y `AssertBeforeDivision`, que primero comprueba `ASSERT_NE(divisor, 0)`.

Al modificar temporalmente `divisor = 0`, el registro indicó:

```text
CalculatorTest.AssertBeforeDivision ***Failed
Expected: (divisor) != (0), actual: 0 vs 0
96% tests passed, 1 tests failed out of 27
```

Tras devolver el divisor a `2`, se obtuvo:

```text
100% tests passed, 0 tests failed out of 27
Total Test time (real) = 0.16 sec
```

Evidencias:
- Fallo: https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40726531186
- Corrección: https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40726562515

## Reflexión — Pruebas unitarias
1. **¿Qué significa que una prueba pase?** Que se cumplieron las condiciones verificadas para esa entrada.
2. **¿Qué significa que falle?** Que al menos una condición comprobada no se cumplió o se produjo un error de ejecución.
3. **¿Por qué automatizar en lugar de probar solo manualmente?** Para repetir comprobaciones sin intervención humana y detectar regresiones.
4. **¿Por qué conviene que las pruebas sean rápidas?** Permite ejecutarlas con frecuencia y recibir retroalimentación inmediata.
5. **¿Por qué deben ser deterministas?** Para obtener resultados consistentes ante las mismas condiciones.

## Reflexión — EXPECT y ASSERT
1. **¿Cuál es la diferencia entre EXPECT y ASSERT?** `EXPECT` registra el fallo y continúa la prueba; `ASSERT` interrumpe la prueba actual.
2. **¿Cuándo utilizar EXPECT?** Para comprobaciones independientes cuyos resultados pueden seguir evaluándose.
3. **¿Cuándo utilizar ASSERT?** Para precondiciones que deben cumplirse antes de continuar.
4. **¿Qué ocurrió con el divisor en cero?** `ASSERT_NE` falló, por lo que no se ejecutó la división posterior; las otras pruebas continuaron.

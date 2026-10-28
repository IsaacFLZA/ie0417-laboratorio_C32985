# Partes 6 y 7 — Casos borde y semillas

## Casos borde agregados
**Calculadora:** división entre negativos, división positivo/negativo, paridad de cero.

**Cadenas:** convertir cadena vacía a mayúsculas, cadena vacía como palíndromo y palíndromo de un carácter.

**Notas:** valores `0`, `100`, `-1` y transiciones `59/60`, `69/70`, `79/80`, `89/90`.

Se agregaron 13 pruebas de casos borde. La suite alcanzó 40 pruebas; al sumar la prueba aleatoria llegó a 41.

## Prueba aleatoria reproducible
Se utilizó `std::mt19937 generator(12345)`, una distribución de -100 a 100 y diez pares de números, comprobando cada suma.

En el experimento se cambió la semilla a `54321` y luego se restauró a `12345`.

**Resultados reales compartidos:**

```text
Semilla 54321:
100% tests passed, 0 tests failed out of 41
Total Test time (real) = 0.28 sec

Semilla 12345 (restaurada):
100% tests passed, 0 tests failed out of 41
Total Test time (real) = 0.12 sec
```

La semilla distinta cambia los números generados, pero no tiene por qué hacer fallar la prueba.

## Reflexión — Casos borde
1. **¿Qué es un caso borde?** Una entrada cercana a un límite, transición o condición especial.
2. **¿Por qué probar cero y valores negativos?** Porque pueden revelar errores en comparaciones, signos y divisiones.
3. **¿Por qué probar cadenas vacías?** Porque algunas funciones fallan ante una entrada de longitud cero.
4. **¿Qué valor tiene probar exactamente 69 y 70?** Permite comprobar la transición entre nota no aprobada y aprobada.
5. **¿Son suficientes solo los casos normales?** No; deben complementarse con límites y entradas inválidas.

## Reflexión — Semillas
1. **¿Qué es una semilla aleatoria?** El valor con el que se inicializa un generador seudoaleatorio.
2. **¿Por qué fijar una semilla?** Para repetir la misma secuencia de valores.
3. **¿Qué sucedió al cambiarla?** La secuencia generada cambió, pero las 41 pruebas siguieron pasando.
4. **¿Por qué importa la reproducibilidad?** Permite investigar un fallo usando las mismas entradas.

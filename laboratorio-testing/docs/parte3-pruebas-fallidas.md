# Parte 5 — Prueba fallida y corrección

## Error introducido
La función `is_even` debía devolver `true` para números pares. Se sustituyó temporalmente `return number % 2 == 0;` por `return number % 2 == 1;`.

## Ejecución con el error
Google Test detectó ambos fallos:

```text
CalculatorTest.DetectEvenNumber ***Failed
Value of: is_even(8)
  Actual: false
Expected: true

CalculatorTest.DetectOddNumber ***Failed
Value of: is_even(7)
  Actual: true
Expected: false

93% tests passed, 2 tests failed out of 27
```

## Corrección
Se restauró `return number % 2 == 0;`. La siguiente ejecución produjo:

```text
100% tests passed, 0 tests failed out of 27
Total Test time (real) = 0.10 sec
```

## Reflexión
1. **¿Qué aportó introducir un error intencional?** Permitió comprobar que la suite detecta cambios incorrectos en el comportamiento.
2. **¿Por qué es útil conservar una prueba que detectó un bug?** Evita que el mismo error reaparezca sin ser detectado.
3. **¿Qué diferencia hay entre un fallo de prueba y uno de compilación?** En el primer caso el programa compila pero no cumple una expectativa; en el segundo no se construye el ejecutable.
4. **¿Cómo se confirmó la corrección?** Se restauró la condición y se ejecutaron de nuevo las 27 pruebas, todas exitosas.

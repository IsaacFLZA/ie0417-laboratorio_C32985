# Partes 12 y 13 — Mini reto y reflexión final

## Mini reto: `is_valid_grade(int grade)`
Se añadió la declaración en `include/grade_utils.h` y la implementación en `src/grade_utils.cpp`:

```cpp
bool is_valid_grade(int grade) {
    return grade >= 0 && grade <= 100;
}
```

Se agregaron seis pruebas en `tests/test_grade_utils.cpp`:
- Nota válida típica: 85.
- Nota inválida típica: 150.
- Límite inferior válido: 0.
- Límite superior válido: 100.
- Un valor por debajo del límite: -1.
- Un valor por encima del límite: 101.

Las pruebas se incorporaron al repositorio; su ejecución final se verifica en GitHub Actions.

### Reflexión del mini reto
1. **¿Qué define una nota válida?** Estar dentro del rango inclusivo de 0 a 100.
2. **¿Por qué probar ambos extremos?** Para verificar si los límites están incluidos.
3. **¿Por qué probar -1 y 101?** Para detectar errores de una unidad alrededor de cada límite.
4. **¿Qué ventaja tienen las pruebas automatizadas del reto?** Permiten verificar repetidamente cambios en la validación.
5. **¿Cómo podría mejorarse?** Añadiendo pruebas parametrizadas y combinándolas con validaciones de otras funciones de notas.

## Reflexión final
1. **¿Qué es software testing?** Es el proceso de evaluar un sistema mediante pruebas para encontrar defectos y comprobar comportamientos esperados.
2. **¿Por qué el testing mejora la calidad del software?** Porque detecta regresiones y comportamientos incorrectos antes de entregar cambios.
3. **¿Cuál es la diferencia entre verificación y validación?** Verificación: comprobar que el producto cumple su especificación; validación: comprobar que satisface la necesidad prevista.
4. **¿Qué es una prueba unitaria?** Una prueba que comprueba de forma aislada una unidad pequeña de software, como una función.
5. **¿Qué es una prueba funcional?** Una prueba que evalúa el comportamiento esperado frente a un requisito o caso de uso.
6. **¿Qué diferencia hay entre EXPECT_ y ASSERT_?** `EXPECT_` registra fallos sin interrumpir la prueba actual; `ASSERT_` la interrumpe si la condición falla.
7. **¿Por qué las pruebas deben ser deterministas?** Para que el mismo escenario produzca resultados consistentes y los errores puedan reproducirse.
8. **¿Por qué puede ser útil una semilla en pruebas con valores aleatorios?** Permite regenerar la misma secuencia seudoaleatoria para investigar fallos.
9. **¿Qué es cobertura de código?** Una medida del código ejecutado por la suite de pruebas.
10. **¿Por qué una cobertura alta no garantiza ausencia de errores?** Una línea ejecutada no necesariamente ha sido verificada con todas las entradas o condiciones posibles.
11. **¿Qué ventaja tiene ejecutar pruebas en GitHub Actions?** Facilita ejecutar la misma verificación automáticamente al publicar cambios y sin depender del equipo local.
12. **¿Qué parte del laboratorio me pareció más útil?** La ejecución automática de pruebas y la posibilidad de comprobar fallos y correcciones mediante GitHub Actions.
13. **¿Qué parte me pareció más difícil?** Adaptar las tareas de desarrollo y cobertura para realizarlas desde el navegador sin Codespaces.
14. **¿Cómo aplicaría pruebas automatizadas en un proyecto futuro?** Diseñaría pruebas unitarias desde el inicio, agregaría casos borde y ejecutaría la suite en cada cambio mediante integración continua.

## Estado
Los módulos, casos funcionales, mini reto y seis pruebas quedaron incorporados. La ejecución posterior a esos cambios debe verificarse en Actions antes de declarar completa la validación final.

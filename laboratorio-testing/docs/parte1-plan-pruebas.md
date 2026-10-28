# Parte 1 y Parte 9 — Plan de pruebas

## Objetivo
Organizar un proyecto C++ que permita ejecutar automáticamente pruebas unitarias y funcionales mediante CMake y Google Test.

## Organización
- `include/`: declaraciones de funciones.
- `src/`: implementaciones.
- `tests/`: pruebas de Google Test.
- `docs/`: informes de las actividades.
- `CMakeLists.txt`: configuración del proyecto y descubrimiento de pruebas.

## Ejecución
```bash
cmake -S laboratorio-testing -B laboratorio-testing/build
cmake --build laboratorio-testing/build
ctest --test-dir laboratorio-testing/build --output-on-failure
```
En este laboratorio los comandos se ejecutan en GitHub Actions porque el equipo de biblioteca no permite instalar herramientas.

## Casos funcionales de calificaciones

| Caso | Entrada | Resultado esperado | Test de Google Test |
|---|---|---|---|
| TC-001 | 95 | 'A' | `LetterGradeA` |
| TC-002 | 90 | 'A' | `GradeBoundaryBetweenBAndA` |
| TC-003 | 89 | 'B' | `GradeBoundaryBetweenBAndA` |
| TC-004 | -1 | `std::invalid_argument` | `NegativeGradeThrowsException` |
| TC-005 | 101 | `std::invalid_argument` | `GradeAboveMaximumThrowsException` |

Las primeras cuatro entradas ya tenían cobertura en las pruebas existentes. Se agregó explícitamente el caso `101` para completar el plan.

## Preguntas de reflexión — Preparación
1. **¿Por qué separar las pruebas del código fuente?** Para mantener responsabilidades distintas, localizar problemas y facilitar la evolución de cada módulo.
2. **¿Qué ventaja ofrece CMake?** Permite configurar y compilar el proyecto de forma reproducible mediante comandos estándares.
3. **¿Por qué es útil ejecutar todas las pruebas con un comando?** Reduce olvidos y permite repetir la misma verificación localmente y en integración continua.
4. **¿Cuál es la diferencia entre comprobar manualmente y automatizar?** La comprobación manual requiere intervención en cada ejecución; las pruebas automatizadas validan condiciones definidas y presentan resultados repetibles.

## Preguntas de reflexión — Casos funcionales
1. **¿Qué verifica una prueba funcional?** Que una funcionalidad produzca el comportamiento previsto ante entradas específicas.
2. **¿Por qué son importantes los casos límite?** Porque los errores son frecuentes cerca de cambios de condición o de rango.
3. **¿Qué aporta probar entradas inválidas?** Comprueba que el sistema rechace datos incorrectos de manera controlada.
4. **¿Cómo se relacionan las pruebas funcionales y las unitarias?** Una prueba funcional valida un comportamiento requerido; puede implementarse mediante pruebas unitarias si la función es suficientemente aislada.

## Evidencia
Repositorio: `laboratorio-testing/`. Workflow: `.github/workflows/testing.yml` en la raíz del repositorio.

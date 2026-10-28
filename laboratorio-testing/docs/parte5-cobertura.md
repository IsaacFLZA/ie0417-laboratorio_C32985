# Parte 8 — Cobertura de código con gcov y lcov

## Objetivo
Medir qué parte del código de producción es ejecutada por las pruebas automatizadas de Google Test, utilizando `gcov`, `lcov` y `genhtml`.

## Procedimiento
La ejecución se realizó en GitHub Actions, debido a que el equipo utilizado no permite instalar herramientas locales. El workflow configuró CMake con `ENABLE_COVERAGE=ON`, compiló el proyecto, ejecutó las pruebas y generó el informe HTML.

Comandos utilizados por el workflow:

```bash
cmake -S laboratorio-testing -B laboratorio-testing/build -DENABLE_COVERAGE=ON
cmake --build laboratorio-testing/build --parallel 2
ctest --test-dir laboratorio-testing/build --output-on-failure
cd laboratorio-testing/build
lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/tests/*' --output-file coverage_filtered.info --ignore-errors unused
genhtml coverage_filtered.info --output-directory coverage_report
lcov --summary coverage_filtered.info
```

Se excluyó el código de bibliotecas externas, pruebas y archivos del sistema, para centrar la medición en `src/`.

## Resultados reales

Datos obtenidos de los registros de GitHub Actions y del artefacto HTML `coverage-report.zip`, generado el **28 de octubre de 2026**.

| Archivo | Líneas ejecutadas | Cobertura de líneas | Funciones ejecutadas | Cobertura de funciones |
|---|---:|---:|---:|---:|
| `src/calculator.cpp` | 8 / 8 | 100 % | 5 / 5 | 100 % |
| `src/string_utils.cpp` | 20 / 20 | 100 % | 3 / 3 | 100 % |
| `src/grade_utils.cpp` | 14 / 14 | 100 % | 3 / 3 | 100 % |
| **Total** | **42 / 42** | **100 %** | **11 / 11** | **100 %** |

Extracto del registro:

```text
Overall coverage rate:
  lines......: 100.0% (42 of 42 lines)
  functions......: 100.0% (11 of 11 functions)
Summary coverage rate:
  lines......: 100.0% (42 of 42 lines)
  functions..: 100.0% (11 of 11 functions)
  branches...: no data found
```

El informe HTML se descargó desde la sección **Artifacts** de GitHub Actions. Incluye `index.html` y las vistas `src/calculator.cpp.gcov.html`, `src/string_utils.cpp.gcov.html` y `src/grade_utils.cpp.gcov.html`.

## Análisis

**¿Cuál tuvo mayor o menor cobertura?** Los tres archivos empataron con 100 % de líneas y 100 % de funciones; ninguno tuvo una cobertura inferior.

**¿Qué líneas quedaron sin ejecutar?** Ninguna de las 42 líneas instrumentadas del código de producción quedó sin ejecutar. Esto no demuestra que se hayan recorrido todas las combinaciones posibles de condiciones.

**¿Se midió la cobertura de ramas?** No. El reporte especifica `branches...: no data found`; por lo tanto no corresponde asignarle un porcentaje a las ramas.

**Dos pruebas adicionales que podrían aportar calidad:**
1. Validar `letter_grade(101)` como límite superior inválido y comprobar que lanza `std::invalid_argument`.
2. Validar `is_palindrome("Anita lava la tina")` para verificar simultáneamente mayúsculas y espacios.

## Reflexión

1. **¿Qué es cobertura de código?** Es una métrica que indica cuánto código fue ejecutado durante las pruebas.
2. **¿Para qué sirve medirla?** Ayuda a localizar partes del programa que no fueron ejercitadas y a orientar nuevas pruebas.
3. **¿Qué significa alcanzar 100 % de cobertura de líneas?** Que todas las líneas instrumentadas se ejecutaron al menos una vez; no significa que todas las condiciones y entradas posibles estén verificadas.
4. **¿Por qué una cobertura alta no garantiza ausencia de errores?** Porque una línea ejecutada puede producir resultados incorrectos para entradas no incluidas en las pruebas.
5. **¿Cómo se puede mejorar el análisis de cobertura?** Activando también la medición de ramas y agregando pruebas para límites, entradas inválidas y combinaciones de condiciones.

## Evidencia
- Workflow: `/.github/workflows/testing.yml`.
- Artefacto de GitHub Actions: `coverage-report` (HTML).
- Registro del paso `Generate coverage report` con 42/42 líneas y 11/11 funciones.

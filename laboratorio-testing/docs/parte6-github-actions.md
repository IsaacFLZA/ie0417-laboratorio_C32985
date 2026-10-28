# Partes 10 y 11 — Integración continua con GitHub Actions

## Configuración
El workflow `C++ testing` se ubica en `.github/workflows/testing.yml` de la **raíz del repositorio**, la ubicación que GitHub reconoce.

Se ejecuta al recibir cambios en `main` relacionados con `laboratorio-testing/`, al crear pull requests y mediante activación manual. Instala las herramientas necesarias, configura CMake, compila, ejecuta `ctest` y genera un reporte HTML de cobertura como artefacto.

## Evidencia de funcionamiento inicial
Ejecución verificada:
https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40724257066

Resultado real:
```text
100% tests passed, 0 tests failed out of 25
```

Se registraron también ejecuciones exitosas con 27 y 41 pruebas.

## Experimento de fallo intencional en integración continua
Se preparó el cambio temporal:

```cpp
EXPECT_EQ(add(2, 3), 999);
```

en `tests/test_calculator.cpp`, con el commit `Probando fallo en GitHub Actions`. Posteriormente se restauró:

```cpp
EXPECT_EQ(add(2, 3), 5);
```

con el commit `Corrigiendo fallo en GitHub Actions`.

**Estado de la evidencia:** los commits están registrados. Los resultados de las ejecuciones asociadas deben confirmarse en la pestaña Actions antes de documentar el fallo y la recuperación como verificados.

## Reflexión — Integración continua
1. **¿Qué es integración continua?** Ejecutar validaciones automáticas frecuentes al integrar cambios en un repositorio.
2. **¿Qué ventaja tiene GitHub Actions?** Repite la compilación y las pruebas en un entorno controlado, incluso sin equipo local de desarrollo.
3. **¿Qué representa una ejecución roja?** Que algún paso del workflow terminó con error.
4. **¿Por qué conviene revisar los registros?** Para distinguir fallos de compilación, pruebas, dependencias o cobertura.
5. **¿Qué significa una ejecución verde?** Que todos los pasos obligatorios terminaron exitosamente; no implica ausencia absoluta de defectos.

## Reflexión — Fallo intencional en CI
1. **¿Qué se busca al cambiar 5 por 999?** Confirmar que el pipeline detecta una expectativa incorrecta.
2. **¿Qué debe suceder en GitHub Actions?** La prueba de suma debe fallar y el trabajo debería mostrarse en rojo.
3. **¿Cómo se recupera el pipeline?** Restaurando el valor esperado y ejecutando nuevamente el workflow.
4. **¿Por qué es importante que CI detecte errores?** Porque reduce el riesgo de integrar cambios defectuosos sin advertencia.

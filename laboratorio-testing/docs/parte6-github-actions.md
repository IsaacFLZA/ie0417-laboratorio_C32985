# Partes 10 y 11 — Integración continua con GitHub Actions

## Configuración

La integración continua (CI) permite comprobar de forma automática y frecuente que los cambios de un proyecto compilan y superan sus pruebas. En este laboratorio se configuró el workflow **C++ testing** en [`.github/workflows/testing.yml`](../../.github/workflows/testing.yml), en la raíz del repositorio, que es donde GitHub reconoce estos archivos.

El workflow utiliza un trabajo llamado `build-and-test` en `ubuntu-latest`. Se activa con cambios publicados mediante `push` a `main` o mediante `pull_request` dirigido a `main`, siempre que afecten a `laboratorio-testing/**` o al propio archivo del workflow. También admite ejecución manual mediante `workflow_dispatch`.

Los pasos definidos en la configuración son:

1. **Checkout repository:** obtiene el código del repositorio.
2. **Install dependencies:** instala herramientas de compilación, CMake y `lcov`.
3. **Configure CMake:** prepara el proyecto con `ENABLE_COVERAGE=ON`.
4. **Build:** compila los módulos y las pruebas.
5. **Run tests:** ejecuta CTest y muestra la salida de las pruebas fallidas.
6. **Generate coverage report:** recopila y filtra los datos de cobertura y genera el informe HTML.
7. **Upload coverage report:** publica el artefacto `coverage-report`.

Los comandos principales del workflow, ejecutados desde la raíz del repositorio, son:

```bash
cmake -S laboratorio-testing -B laboratorio-testing/build -DENABLE_COVERAGE=ON
cmake --build laboratorio-testing/build --parallel 2
ctest --test-dir laboratorio-testing/build --output-on-failure
```

Si una prueba falla, CTest informa el nombre del caso y su salida. El paso `Run tests` termina con error y el trabajo no se considera exitoso. Así se puede distinguir un fallo de pruebas de un problema de configuración o compilación.

## Evidencia de funcionamiento inicial

La [ejecución inicial de GitHub Actions](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40724257066) del 28 de octubre de 2026 terminó correctamente. Su registro muestra:

```text
100% tests passed, 0 tests failed out of 25
```

Posteriormente se documentaron ejecuciones exitosas con 27 y 41 pruebas. En una [ejecución posterior verificada](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031), CTest registró:

```text
100% tests passed, 0 tests failed out of 48
```

En esta última ejecución también se generó y publicó el [artefacto HTML de cobertura](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031/artifacts/12835367540). El registro reporta 43/43 líneas y 12/12 funciones instrumentadas; no aporta datos de cobertura de ramas. La medición inicial de la Parte 8, antes del mini reto, fue de 42/42 líneas y 11/11 funciones, como se explica en [el documento de cobertura](parte5-cobertura.md).

Estos resultados muestran que las pruebas pasaron en las ejecuciones indicadas, no que el proyecto esté libre de cualquier defecto.

## Fallo intencional en CI

### Cambio introducido

Para la Parte 11 se modificó temporalmente la expectativa de la prueba `CalculatorTest.AddPositiveNumbers` en [`tests/test_calculator.cpp`](../tests/test_calculator.cpp). La comprobación correcta era:

```cpp
EXPECT_EQ(add(2, 3), 5);
```

Se reemplazó por:

```cpp
EXPECT_EQ(add(2, 3), 999);
```

El cambio está registrado en el commit [`68a95674` — Probando fallo en GitHub Actions](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/68a95674ca64cc470d843ff6462e25f3674a4c20). Como `add(2, 3)` debe devolver `5`, la nueva expectativa es incorrecta y **debería** hacer fallar esa prueba al ejecutarse. No se modificó la implementación de la suma.

### Corrección

La expectativa se restauró a `5` en el commit [`397598a9` — Corrigiendo fallo en GitHub Actions](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/commit/397598a991b25dc0b276fa4dabbe1667e005da11):

```cpp
EXPECT_EQ(add(2, 3), 5);
```

### Evidencia y alcance de la comprobación

Los commits confirman tanto la introducción del error intencional como su corrección. **No se dispone de un registro recuperado que permita confirmar el estado rojo, el mensaje exacto o la cantidad de pruebas fallidas de una ejecución de GitHub Actions asociada al commit del error.** Tampoco hay evidencia de una ejecución local de este experimento; por ello no se afirma que se haya realizado.

El resultado esperado de ejecutar la versión con `999` sería una discrepancia entre `5` y `999`, seguida de un fallo en CTest. Esa explicación es una predicción basada en el código, no una cita de un log observado.

Sí se verificó una ejecución posterior con la prueba corregida y **48 de 48 pruebas exitosas**: [GitHub Actions — ejecución exitosa](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031). Esta evidencia confirma el funcionamiento de la suite corregida, pero no sustituye la captura o el registro del fallo específico solicitado en el enunciado. Si ese registro está disponible en Actions, todavía se puede incorporar su enlace.

## Reflexión — Integración continua

1. **¿Por qué es útil ejecutar pruebas automáticamente en GitHub?** Porque permite comprobar los cambios relevantes con un procedimiento repetible, sin depender de que alguien recuerde ejecutar las pruebas manualmente. Además, los resultados quedan disponibles en el historial de Actions.

2. **¿Qué problema resuelve la integración continua?** Ayuda a detectar errores y regresiones poco después de introducir cambios, evitando que se acumulen modificaciones difíciles de revisar al final del desarrollo.

3. **¿Por qué conviene ejecutar pruebas antes de integrar cambios?** Porque una prueba fallida puede advertir que una modificación todavía no cumple lo esperado. Revisarla antes de integrar reduce el riesgo de incorporar código defectuoso a la rama principal.

4. **¿Qué información proporciona GitHub Actions cuando un workflow falla?** Muestra el trabajo y el paso afectados, su estado y los registros de ejecución. En el caso de CTest, estos pueden incluir el nombre de la prueba y los resultados obtenidos, lo que facilita investigar el error.

5. **¿Cómo ayuda CI a mejorar la colaboración en equipo?** Ofrece una referencia común para revisar si los cambios compilan y superan las pruebas. Esto facilita discutir problemas concretos y mantener criterios compartidos antes de integrar código.

## Reflexión — Fallo intencional en CI

1. **¿Por qué es útil ver una prueba fallar al menos una vez?** Porque permite comprender cómo una comprobación detecta un comportamiento distinto del esperado. El cambio de `5` por `999` es un ejemplo claro de una expectativa incorrecta, aunque su ejecución fallida específica no haya podido verificarse en los registros consultados.

2. **¿Qué diferencia hay entre una prueba fallando localmente y una prueba fallando en CI?** Una prueba local se ejecuta en el entorno de desarrollo de una persona. En CI se ejecuta automáticamente en un entorno configurado para el proyecto y deja un resultado consultable por otros. No se documentó una ejecución local de este experimento.

3. **¿Por qué no se debería dejar código con pruebas fallidas en la rama principal?** Porque significa mantener un estado que no supera las comprobaciones definidas y puede dificultar detectar fallos nuevos. Lo conveniente es corregir la causa y volver a verificar.

4. **¿Qué aporta CI a la calidad del software?** Aporta verificaciones frecuentes, reproducibles y visibles. No garantiza ausencia de errores, pero permite detectar regresiones y conservar evidencia de las ejecuciones para fundamentar las decisiones.

## Conclusión

La integración continua permitió comprobar el proyecto en GitHub Actions, desde las primeras 25 pruebas exitosas hasta una ejecución posterior con 48 pruebas aprobadas. También se registró en Git el cambio intencional de una expectativa y su corrección. La principal enseñanza es interpretar correctamente la evidencia: una ejecución verde confirma que los pasos requeridos pasaron en ese momento, mientras que un fallo solo debe describirse como observado cuando se cuenta con su registro correspondiente.

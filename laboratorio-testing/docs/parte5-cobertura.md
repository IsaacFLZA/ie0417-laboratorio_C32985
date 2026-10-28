# Parte 8 — Cobertura de código con gcov y lcov

## Objetivo

En esta parte se buscó medir cuánto del código de los tres módulos de C++ se ejecuta al correr las pruebas automatizadas. Para ello se utilizaron las opciones de instrumentación de GCC, junto con `gcov`, `lcov` y `genhtml`.

La cobertura sirve para encontrar partes del programa que las pruebas todavía no recorren. Es una ayuda para decidir qué probar después, pero no sustituye la revisión de los resultados esperados: una línea puede ejecutarse y aun así contener un error.

## Procedimiento realizado

El informe se generó mediante el workflow **C++ testing** de GitHub Actions, ubicado en [`.github/workflows/testing.yml`](../../.github/workflows/testing.yml). Esta alternativa permitió utilizar las herramientas de cobertura en el entorno de GitHub Actions, sin depender de su instalación en el equipo local.

En [`CMakeLists.txt`](../CMakeLists.txt), la opción `ENABLE_COVERAGE` activa la compilación y el enlazado con `--coverage`, además de `-O0 -g`. El workflow instala `lcov`, configura el proyecto, compila, ejecuta CTest y genera el reporte HTML.

Estos son los comandos que ejecuta el workflow desde la raíz del repositorio:

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

Primero se ejecutan las pruebas para que se registren los datos de cobertura. Después, `lcov --capture` reúne la información de los archivos instrumentados; `lcov --remove` excluye bibliotecas del sistema, dependencias externas y los propios archivos de pruebas. Así, el porcentaje final se refiere al código de producción de `src/`, no a todo el repositorio. Finalmente, `genhtml` produce páginas HTML que permiten revisar cada archivo.

Los parámetros `--ignore-errors` se utilizaron para manejar determinadas advertencias de `lcov` durante la generación del reporte; no significan que las pruebas fallidas se consideren exitosas. El paso de CTest sigue siendo independiente y obligatorio.

## Resultados obtenidos

### Medición inicial de la Parte 8

En la etapa original de cobertura, antes de incorporar el mini reto `is_valid_grade()`, se registraron **42 de 42 líneas ejecutadas** y **11 de 11 funciones ejecutadas**. El desglose fue:

| Archivo de producción | Líneas ejecutadas | Funciones ejecutadas | Cobertura |
|---|---:|---:|---:|
| `src/calculator.cpp` | 8 / 8 | 5 / 5 | 100 % |
| `src/string_utils.cpp` | 20 / 20 | 3 / 3 | 100 % |
| `src/grade_utils.cpp` | 14 / 14 | 3 / 3 | 100 % |
| **Total inicial** | **42 / 42** | **11 / 11** | **100 %** |

Este resultado corresponde a la medición histórica de la actividad, no al estado final del código después de agregar la nueva función de validación de notas.

### Comprobación posterior con el mini reto incorporado

El **28 de octubre de 2026**, la ejecución corregida de GitHub Actions confirmó que las **48 pruebas pasaron** y que el reporte de cobertura se generó correctamente. Al añadirse `is_valid_grade()`, el número de líneas y funciones instrumentadas aumentó:

| Archivo de producción | Líneas ejecutadas | Funciones ejecutadas | Cobertura |
|---|---:|---:|---:|
| `src/calculator.cpp` | 8 / 8 | 5 / 5 | 100 % |
| `src/string_utils.cpp` | 20 / 20 | 3 / 3 | 100 % |
| `src/grade_utils.cpp` | 15 / 15 | 4 / 4 | 100 % |
| **Total posterior** | **43 / 43** | **12 / 12** | **100 %** |

El registro del paso **Generate coverage report** muestra:

```text
Overall coverage rate:
  lines......: 100.0% (43 of 43 lines)
  functions......: 100.0% (12 of 12 functions)
Summary coverage rate:
  lines......: 100.0% (43 of 43 lines)
  functions..: 100.0% (12 of 12 functions)
  branches...: no data found
```

No hay contradicción entre los dos totales: el primer reporte medía 11 funciones y el segundo 12, porque el proyecto creció durante el laboratorio. En ambos casos se obtuvo 100 % de cobertura de líneas y funciones para los archivos incluidos en el reporte.

**Evidencia verificable:**

- [Ejecución corregida de GitHub Actions — 48 pruebas y reporte de cobertura](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031).
- [Artefacto HTML `coverage-report` de esa ejecución](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731528031/artifacts/12835367540).
- [Configuración de la generación y publicación del reporte](../../.github/workflows/testing.yml).

El artefacto se publica como `coverage-report` e incluye el índice HTML y las páginas correspondientes a los archivos de `src/`. Se puede consultar desde la sección **Artifacts** de la ejecución, sujeto a la disponibilidad y los permisos de GitHub.

## Análisis del reporte

**Archivos con mayor y menor cobertura.** Los tres archivos empataron con 100 % tanto en líneas como en funciones. Por eso no hay uno con menor porcentaje. Sin embargo, sus tamaños son distintos: `string_utils.cpp` tiene más líneas instrumentadas que los otros dos.

**Líneas que quedaron sin ejecutar.** Ninguna de las líneas instrumentadas de `src/` quedó sin ejecutar en las mediciones indicadas. Esto no significa que se hayan comprobado todas las entradas posibles ni todos los caminos internos de cada función.

**Ramas sin cubrir.** No se obtuvo una medición de ramas: el registro indica `branches...: no data found`. Por tanto, no se puede afirmar que las ramas tengan 100 % de cobertura ni identificar con este reporte cuáles faltan. Para estudiarlas sería necesario habilitar y revisar esa métrica en una ejecución posterior.

### Dos pruebas adicionales propuestas

Aunque ya se alcanzó el 100 % de cobertura de líneas, todavía se pueden añadir casos que hagan más sólida la suite y permitan explorar combinaciones no comprobadas explícitamente:

1. **Palíndromo con mayúsculas y espacios.** Comprobar `EXPECT_TRUE(is_palindrome("Anita lava la tina"));`. Ya existe una prueba de esa frase en minúsculas, pero esta variante combina espacios con cambios de mayúsculas y minúsculas, dos operaciones que realiza la función.
2. **Vocales en mayúsculas.** Comprobar `EXPECT_EQ(count_vowels("AEIOU"), 5);`. La prueba actual utiliza `"murcielago"` en minúsculas; este nuevo caso revisaría de forma explícita la normalización de letras mayúsculas.

Estas son **propuestas**, no pruebas que se hayan agregado o ejecutado. No pueden aumentar el porcentaje de líneas por encima del 100 %; su valor estaría en ampliar los comportamientos verificados y, posiblemente, la cobertura de ramas si esta se midiera después.

## Preguntas de reflexión

1. **¿Qué significa tener 100% de cobertura?** Significa que, para la métrica que se está consultando, todas las unidades instrumentadas fueron ejecutadas por las pruebas. En este caso se alcanzó 100 % de líneas y funciones del código de producción incluido en el reporte. No se midió la cobertura de ramas.

2. **¿Tener 100% de cobertura garantiza que el programa no tiene errores?** No. Una prueba puede pasar por una línea sin comprobar todos los valores que esa línea podría recibir. Por ejemplo, una función que trabaja correctamente con una nota válida todavía podría fallar con una entrada especial no probada. La cobertura muestra ejecución, no corrección absoluta.

3. **¿Qué diferencia hay entre cobertura de líneas y cobertura de ramas?** La cobertura de líneas cuenta qué líneas ejecutables fueron recorridas. La cobertura de ramas revisa las alternativas de decisión, como los caminos verdadero y falso de un `if`. Es posible ejecutar una línea con una condición sin haber probado las dos alternativas. Por eso la cobertura de ramas complementa a la de líneas.

4. **¿Por qué una línea ejecutada no necesariamente significa que fue bien probada?** Porque ejecutarla no demuestra que su resultado se haya comparado con el esperado ni que se hayan considerado valores límite o inválidos. Una comprobación útil necesita entradas elegidas con intención y una expectativa que permita detectar un comportamiento incorrecto.

5. **¿Cómo puede ayudar la cobertura a mejorar las pruebas?** Permite ubicar funciones o líneas que no se ejecutaron y concentrar ahí los siguientes casos de prueba. En este laboratorio, el reporte confirmó que todo el código de producción instrumentado se ejecutó; el siguiente paso razonable sería revisar más combinaciones de entradas y medir también las ramas, en lugar de agregar pruebas solo para subir un porcentaje.

## Conclusión

La medición con `gcov` y `lcov` permitió comprobar que las pruebas recorrieron todas las líneas y funciones instrumentadas de los tres módulos. La cobertura inicial fue de **42/42 líneas y 11/11 funciones**; tras incorporar el mini reto, la ejecución verificada mostró **43/43 líneas y 12/12 funciones**, manteniendo el 100 % en ambas métricas. Lo más importante de este resultado no es únicamente el porcentaje, sino aprender a interpretarlo: ayuda a detectar código no ejercitado, pero debe complementarse con pruebas de límites, entradas inválidas y distintas condiciones.

# Partes 1 y 9 — Preparación del proyecto y plan de pruebas funcionales

## Objetivo

El propósito de estas actividades es organizar un proyecto en C++ para poder compilarlo y comprobar su comportamiento mediante pruebas automatizadas. Para ello se utilizan **CMake** como sistema de configuración y compilación, **Google Test** para escribir las comprobaciones y **CTest** para ejecutarlas en conjunto.

La Parte 1 se centra en preparar la estructura y el procedimiento de pruebas. En la Parte 9 se aplica ese mismo entorno a un plan de casos funcionales para la clasificación de calificaciones.

## Parte 1 — Organización del proyecto

El proyecto está dentro de la carpeta \`laboratorio-testing/\`. Su estructura principal es:

| Ruta | Función |
|---|---|
| \`include/\` | Contiene las declaraciones de las funciones disponibles para el resto del proyecto. |
| \`src/\` | Contiene las implementaciones de las funciones en C++. |
| \`tests/\` | Agrupa las pruebas escritas con Google Test. |
| \`docs/\` | Guarda la documentación de las actividades y los resultados. |
| \`CMakeLists.txt\` | Define los archivos que se compilan, incorpora Google Test y registra las pruebas con CTest. |

Separar el código de las pruebas ayuda a encontrar con mayor facilidad dónde se produce un error. Además, permite agregar nuevos casos de prueba sin mezclar las comprobaciones con la lógica de las funciones.

### Procedimiento de ejecución

Desde la **raíz del repositorio**, los comandos son:

\`\`\`bash
cmake -S laboratorio-testing -B laboratorio-testing/build
cmake --build laboratorio-testing/build
ctest --test-dir laboratorio-testing/build --output-on-failure
\`\`\`

El primer comando configura el proyecto y prepara los archivos de compilación. El segundo compila la biblioteca y el ejecutable de pruebas. El tercero ejecuta los casos registrados en CTest y muestra los detalles cuando alguno falla.

En este laboratorio, las ejecuciones se comprobaron mediante **GitHub Actions**, ya que el entorno de trabajo utilizado no permitía instalar las herramientas necesarias localmente. El workflow está en \`.github/workflows/testing.yml\`, en la raíz del repositorio, y utiliza los mismos pasos básicos de configuración, compilación y ejecución. También genera un reporte de cobertura, que se explica en otro documento.

## Parte 9 — Plan de pruebas funcionales de calificaciones

### Funcionalidad evaluada

Se revisó la función \`letter_grade(int grade)\`, implementada en \`src/grade_utils.cpp\`. Su tarea es convertir una nota numérica en una letra, de acuerdo con estos rangos:

| Rango de nota | Letra |
|---|---|
| 90 a 100 | A |
| 80 a 89 | B |
| 70 a 79 | C |
| 60 a 69 | D |
| 0 a 59 | F |

Si la nota es menor que 0 o mayor que 100, la función lanza una excepción \`std::invalid_argument\`. Este comportamiento también forma parte de los requisitos que deben probarse.

### Casos de prueba definidos

| Caso | Entrada | Resultado esperado | Prueba de Google Test |
|---|---:|---|---|
| TC-001 | 95 | Letra \`A\` | \`GradeUtilsTest.LetterGradeA\` |
| TC-002 | 90 | Letra \`A\` | \`GradeUtilsTest.GradeBoundaryBetweenBAndA\` |
| TC-003 | 89 | Letra \`B\` | \`GradeUtilsTest.GradeBoundaryBetweenBAndA\` |
| TC-004 | -1 | Excepción \`std::invalid_argument\` | \`GradeUtilsTest.NegativeGradeThrowsException\` |
| TC-005 | 101 | Excepción \`std::invalid_argument\` | \`GradeUtilsTest.GradeAboveMaximumThrowsException\` |

Los casos TC-002 y TC-003 se comprueban dentro de una misma prueba automatizada, porque ambos valores están a los lados del límite entre B y A. Por eso hay **cinco casos funcionales**, aunque la tabla haga referencia a **cuatro pruebas de Google Test distintas**.

Al revisar el archivo \`tests/test_grade_utils.cpp\`, se confirmó que los casos para 95, 90, 89 y -1 ya estaban contemplados. El caso de 101 quedó representado por la prueba \`GradeAboveMaximumThrowsException\`, que verifica que una nota superior al máximo produzca la excepción esperada.

### Resultados y evidencia

En la ejecución de GitHub Actions del **28 de octubre de 2026**, el workflow \`C++ testing\` finalizó correctamente. El registro de CTest mostró:

\`\`\`text
100% tests passed, 0 tests failed out of 48
\`\`\`

Este total corresponde a **todas las pruebas del proyecto**, no solamente a los cinco casos del plan funcional. Dentro de esas 48 pruebas, las comprobaciones de \`letter_grade\` incluidas en la tabla aparecieron con estado \`Passed\`.

- [Ejecución exitosa de GitHub Actions](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/actions/runs/40731713617)
- [Archivo de pruebas de calificaciones](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/blob/main/laboratorio-testing/tests/test_grade_utils.cpp)
- [Implementación de calificaciones](https://github.com/IsaacFLZA/ie0417-laboratorio_C32985/blob/main/laboratorio-testing/src/grade_utils.cpp)

El resultado confirma que los casos definidos se comportaron como se esperaba en esa ejecución. No significa que la función esté libre de cualquier posible defecto; para eso sería necesario considerar otros escenarios y seguir ampliando las pruebas.

## Preguntas de reflexión — Preparación

1. **¿Por qué separar las pruebas del código fuente?** Porque cumplen funciones diferentes. El código implementa el comportamiento y las pruebas comprueban que ese comportamiento sea correcto. Tenerlos separados facilita mantener ambos y localizar errores.
2. **¿Qué ventaja ofrece CMake?** Permite describir la compilación del proyecto en un archivo de configuración, en vez de depender de comandos manuales distintos para cada archivo. Esto también facilita reproducir la compilación en GitHub Actions.
3. **¿Por qué es útil ejecutar todas las pruebas con un comando?** Porque reduce la posibilidad de olvidar algún caso y permite repetir la misma revisión después de cada cambio. En este proyecto, CTest reúne las pruebas registradas.
4. **¿Cuál es la diferencia entre comprobar manualmente y automatizar?** En una comprobación manual una persona ejecuta las acciones y observa el resultado. Una prueba automatizada ya tiene definidas las entradas y las condiciones esperadas, por lo que se puede repetir sin revisar cada resultado a mano.

## Preguntas de reflexión — Casos funcionales

1. **¿Qué verifica una prueba funcional?** Comprueba si una funcionalidad responde como lo establece su requisito. En este caso, se verifica qué letra devuelve una nota y qué ocurre cuando la entrada es inválida.
2. **¿Por qué son importantes los casos límite?** Porque permiten detectar errores en los puntos donde cambia una condición. Probar 89 y 90, por ejemplo, ayuda a confirmar que la clasificación cambia exactamente donde corresponde.
3. **¿Qué aporta probar entradas inválidas?** Permite comprobar que el programa no acepta silenciosamente valores fuera del rango permitido y que responde de la forma prevista, en este caso mediante una excepción.
4. **¿Cómo se relacionan las pruebas funcionales y las unitarias?** No son categorías excluyentes. Una prueba funcional se enfoca en un comportamiento requerido, mientras que una prueba unitaria se enfoca en una unidad pequeña del código. Aquí se verifican requisitos funcionales mediante pruebas sobre una función individual.

## Conclusión

La organización del proyecto permitió ejecutar las pruebas de manera consistente mediante CMake, Google Test y CTest. En la actividad de calificaciones, el plan incluyó valores habituales, un límite entre categorías y entradas inválidas. La ejecución exitosa en GitHub Actions aportó evidencia de que estos casos pasaron junto con el resto de la suite. La principal ventaja de este procedimiento es que las mismas comprobaciones pueden repetirse cuando se modifica el código, sin tener que revisar manualmente cada resultado.

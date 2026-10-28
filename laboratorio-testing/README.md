# Laboratorio de pruebas de software — IE0417

Proyecto en C++ con CMake, Google Test, medición de cobertura y GitHub Actions.

## Estructura
- `include/`: encabezados de los módulos.
- `src/`: implementaciones C++.
- `tests/`: pruebas automatizadas con Google Test.
- `docs/`: informes del laboratorio.

## Ejecución
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Las ejecuciones automatizadas se muestran en la pestaña **Actions** del repositorio. El workflow está en `/.github/workflows/testing.yml`, porque GitHub solo detecta los workflows en la raíz del repositorio.

#include <iostream>

int obtener_mayor(int* datos, int tamano) {
    int mayor = datos[0];

    for (int i = 1; i < tamano; i++) {
        if (datos[i] > mayor) {
            mayor = datos[i];
        }
    }

    return mayor;
}

double calcular_promedio(int* datos, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += datos[i];
    }

    return static_cast<double>(suma) / tamano;
}

int main() {
    int tamano = 5;
    int* datos = new int[tamano]{-10, -20, -5, -30, -15};

    std::cout << "Mayor: " << obtener_mayor(datos, tamano) << std::endl;
    std::cout << "Promedio: " << calcular_promedio(datos, tamano) << std::endl;

    delete[] datos;

    return 0;
}

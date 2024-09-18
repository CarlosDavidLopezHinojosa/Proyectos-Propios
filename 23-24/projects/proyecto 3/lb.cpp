#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Crear un vector ordenado
    std::vector<int> v = {1, 3, 3, 5, 7, 9, 9, 11};

    // Mostrar el vector
    std::cout << "Vector: ";
    for (int n : v) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    // Valor a buscar
    int value = 3;
    
    // Encontrar el lower_bound del valor
    auto lower = std::lower_bound(v.begin(), v.end(), value);

    // Calcular el índice
    int index = lower - v.begin();

    // Mostrar el resultado
    if (lower != v.end() && *lower == value) {
        std::cout << "El valor " << value << " se encuentra en el índice " << index << "." << std::endl;
    } else {
        std::cout << "El valor " << value << " no se encuentra en el vector. Se puede insertar en el índice " << index << "." << std::endl;
    }

    // Probar con otro valor que no está en el vector
    value = 6;
    lower = std::lower_bound(v.begin(), v.end(), value);
    index = lower - v.begin();

    if (lower != v.end() && *lower == value) {
        std::cout << "El valor " << value << " se encuentra en el índice " << index << "." << std::endl;
    } else {
        std::cout << "El valor " << value << " no se encuentra en el vector. Se puede insertar en el índice " << index << "." << std::endl;
    }

    return 0;
}

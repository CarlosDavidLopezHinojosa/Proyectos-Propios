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
    int value = 12; // Un valor mayor que cualquier elemento en el vector
    
    // Encontrar el lower_bound del valor
    auto lower = std::lower_bound(v.begin(), v.end(), value);

    // Calcular el índice
    int index = lower - v.begin();

    // Mostrar el resultado
    if (lower != v.end()) {
        std::cout << "El valor " << value << " se puede insertar en el índice " << index << "." << std::endl;
    } else {
        std::cout << "El valor " << value << " no se encuentra en el vector y es mayor que todos los elementos. "
                  << "Devuelve end(), que corresponde al índice " << index << "." << std::endl;
    }

    return 0;
}

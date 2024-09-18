#include <iostream>
#include "vertex.hpp"

int main() {
    // Crear un vértice usando el método estático create
    auto vertex1 = Vertex<int>::create(1, 100);

    // Mostrar los valores iniciales
    std::cout << "Vertex 1 - Label: " << vertex1->label() 
              << ", Data: " << vertex1->data() 
              << ", Is Visited: " << std::boolalpha << vertex1->is_visited() << std::endl;

    // Modificar los valores usando los setters
    vertex1->set_label(2);
    vertex1->set_data(200);
    vertex1->set_visited(true);

    // Mostrar los valores después de modificarlos
    std::cout << "Vertex 1 - Label (updated): " << vertex1->label() 
              << ", Data (updated): " << vertex1->data() 
              << ", Is Visited (updated): " << std::boolalpha << vertex1->is_visited() << std::endl;

    // Crear otro vértice con diferente tipo de dato
    auto vertex2 = Vertex<std::string>::create(3, "Vertex 2");

    // Mostrar los valores del segundo vértice
    std::cout << "Vertex 2 - Label: " << vertex2->label() 
              << ", Data: " << vertex2->data() 
              << ", Is Visited: " << std::boolalpha << vertex2->is_visited() << std::endl;

    // Modificar los valores del segundo vértice
    vertex2->set_label(4);
    vertex2->set_data("Updated Vertex 2");
    vertex2->set_visited(true);

    // Mostrar los valores después de modificarlos
    std::cout << "Vertex 2 - Label (updated): " << vertex2->label() 
              << ", Data (updated): " << vertex2->data() 
              << ", Is Visited (updated): " << std::boolalpha << vertex2->is_visited() << std::endl;

    return 0;
}

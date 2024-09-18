#include <iostream>
#include "vertex.hpp"
#include "edge.hpp"

int main() {
    // Crear algunos vértices
    auto vertex1 = Vertex<int>::create(1, 10);
    auto vertex2 = Vertex<int>::create(2, 20);
    auto vertex3 = Vertex<int>::create(3, 30);

    // Mostrar los datos de los vértices
    std::cout << "Vertex 1 - Label: " << vertex1->label() 
              << ", Data: " << vertex1->data() << std::endl;

    std::cout << "Vertex 2 - Label: " << vertex2->label() 
              << ", Data: " << vertex2->data() << std::endl;

    std::cout << "Vertex 3 - Label: " << vertex3->label() 
              << ", Data: " << vertex3->data() << std::endl;

    // Crear una arista que conecta vertex1 y vertex2
    auto edge1 = Edge<int, double>::create(vertex1, vertex2, 5.5);

    // Mostrar la información de la arista
    std::cout << "Edge 1 - Weight: " << edge1->weight() 
              << ", Connects: Vertex " << edge1->u()->label()
              << " and Vertex " << edge1->v()->label() << std::endl;

    // Verificar si una arista tiene un vértice específico
    std::cout << "Edge 1 has Vertex 1: " << std::boolalpha << edge1->has(vertex1) << std::endl;
    std::cout << "Edge 1 has Vertex 3: " << std::boolalpha << edge1->has(vertex3) << std::endl;

    // Obtener el otro vértice de una arista
    auto otherVertex = edge1->other(vertex1);
    std::cout << "The other vertex connected to Vertex 1 by Edge 1 is Vertex " 
              << otherVertex->label() << std::endl;

    // Marcar vértices y aristas como visitados
    vertex1->set_visited(true);
    edge1->set_visited(true);

    std::cout << "Vertex 1 visited: " << std::boolalpha << vertex1->is_visited() << std::endl;
    std::cout << "Edge 1 visited: " << std::boolalpha << edge1->is_visited() << std::endl;

    return 0;
}
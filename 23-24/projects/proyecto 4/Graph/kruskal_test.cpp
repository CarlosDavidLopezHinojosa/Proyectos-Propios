#include "graph.hpp"  // Incluye la definición de la clase Graph
#include <iostream>
#include <cassert>


int main() {
    
    // Crear un grafo no dirigido
    Graph<char, int> graph(false);

    // Añadir vértices
    graph.add_vertex('A');  // Vértice 0
    graph.add_vertex('B');  // Vértice 1
    graph.add_vertex('C');  // Vértice 2
    graph.add_vertex('D');  // Vértice 3

    // Añadir aristas con pesos
    graph.add_edge(0,1,10);
    graph.add_edge(0,2,5);
    graph.add_edge(0,3,20);
    graph.add_edge(1,2,1);
    graph.add_edge(2,3,7);

    // Imprimir el grafo original
    std::cout << "Grafo original:" << std::endl;
    graph.print_graph();

    // Ejecutar el algoritmo de Kruskal para obtener el MST
    Graph<char, int> mst = graph.kruskal_algorithm();

    // Imprimir el MST resultante
    std::cout << "\nÁrbol de expansión mínima (MST) usando Kruskal:" << std::endl;
    mst.print_graph();

    // Verificar que el MST tiene el número correcto de aristas
    assert(mst.num_edges() == graph.num_vertices() - 1);

    // Verificar que el peso total del MST es correcto
    int expected_total_weight = 1 + 5 + 7; // Pesos de las aristas en el MST: (1, 4), (3, 4), (1, 3)
    int total_weight = 0;

    total_weight = mst.total_weight();

    assert(total_weight == expected_total_weight);
    std::cout << "\nEl test del algoritmo de Kruskal ha pasado correctamente." << std::endl;
    return 0;
}

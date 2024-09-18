#include <iostream>
#include "graph.hpp"

int main() {
    // Crear un grafo de prueba con 4 vértices
    Graph<char, int> graph(true);

    // Añadir vértices
    for (char vertex : {'A', 'B', 'C', 'D'}) {
        graph.add_vertex(vertex);
    }

    // Añadir aristas con pesos
    graph.add_edge(0, 1, 3); // A -> B
    graph.add_edge(1, 2, 5); // B -> C
    graph.add_edge(2, 3, 2); // C -> D
    graph.add_edge(3, 0, 7); // D -> A
    graph.add_edge(0, 2, 10); // A -> C (direct path)

    // Ejecutar el algoritmo de Floyd-Warshall
    auto I = graph.floyd_algorithm();

    // Mostrar la matriz de distancias resultante
    std::cout << "Shortest path matrix (distances):" << std::endl;
    for (size_t i = 0; i < I.size(); ++i) {std::cout <<"[";
        for (size_t j = 0; j < I[i].size(); ++j) {
            
                std::cout << int(I[i][j]) << " ";
            
        }
        std::cout << "]\n" << std::endl;
    }

    return 0;
}

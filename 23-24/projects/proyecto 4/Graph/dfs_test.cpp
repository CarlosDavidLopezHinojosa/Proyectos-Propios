#include "graph.hpp"
#include <iostream>
int main() {
    // Crear un grafo no dirigido
    Graph<char, int> graph(false);

    // Añadir vértices
    graph.add_vertex('A');
    graph.add_vertex('B');
    graph.add_vertex('C');
    graph.add_vertex('D');

    // Añadir aristas
    graph.add_edge(0, 1, 100);
    graph.add_edge(1, 2, 200);
    graph.add_edge(2, 3, 300);
    graph.add_edge(0, 3, 400);
    graph.add_edge(0, 2, 500);
    graph.add_edge(1, 3, 600);

    // Mostrar el grafo original
    std::cout << "Grafo Original:\n";
    graph.print_graph();

    // Obtener y mostrar el árbol abarcador en profundidad
    auto spanning_tree = graph.dfs_spanning_tree();
    std::cout << "\nÁrbol Abarcador en Profundidad:\n";
    spanning_tree.print_graph();

    return 0;
}

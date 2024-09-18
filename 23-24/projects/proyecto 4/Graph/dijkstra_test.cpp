#include "graph.hpp"

int main ()
{
    
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
    graph.add_edge(2, 3, 10);
    graph.add_edge(0, 3, 80);
    graph.add_edge(2, 0, 250);
    graph.add_edge(1, 3, 200);

    // Mostrar el grafo original
    std::cout << "Grafo Original:\n";
    graph.print_graph();

    std::vector<int> w;
    std::vector<size_t> p;

    std::tie(w,p) = graph.dijkstra_algorithm(3);

    std::cout << "Weight:\n [";
    for (size_t i = 0; i < w.size(); i++)
    {
        std::cout << w[i] << " ";
    }
    std::cout << "]\n";

    std::cout << "Paths:\n [";
    for (size_t i = 0; i < p.size(); i++)
    {
        std::cout << p[i] << " ";
    }
    std::cout << "]\n";
    

    return 0;
}
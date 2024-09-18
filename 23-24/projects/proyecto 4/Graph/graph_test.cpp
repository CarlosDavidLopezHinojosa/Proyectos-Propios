#include <iostream>
#include "graph.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include <cassert>

int main() {
    // Crear un grafo dirigido
    Graph<char, int> directed_graph(true);

    // Añadir vértices al grafo dirigido
    directed_graph.add_vertex('A');  // Vértice 0
    directed_graph.add_vertex('B');  // Vértice 1
    directed_graph.add_vertex('C');  // Vértice 2

    // Comprobar número de vértices
    assert(directed_graph.num_vertices() == 3);

    // Añadir aristas al grafo dirigido
    directed_graph.add_edge(0, 1, 100); // Arista 0->1 con peso 100
    directed_graph.add_edge(1, 2, 200); // Arista 1->2 con peso 200
    directed_graph.add_edge(0, 2, 300); // Arista 0->2 con peso 300

    // Comprobar número de aristas
    assert(directed_graph.num_edges() == 3);

    // Imprimir grafo dirigido
    directed_graph.print_graph();

    // Probar la obtención de vértices y aristas
    auto vertex_1 = directed_graph.vertex(1);
    assert(vertex_1->data() == 'B');
    std::cout << "Vertex 1 has label: " << vertex_1->label() << " and data: " << vertex_1->data() << std::endl;

    auto edge_01 = directed_graph.edge(0, 1);
    assert(edge_01->weight() == 100);
    std::cout << "Edge from vertex 0 to vertex 1 has weight: " << edge_01->weight() << std::endl;

    // Crear un grafo no dirigido
    Graph<char, int> undirected_graph(false);

    // Añadir vértices al grafo no dirigido
    undirected_graph.add_vertex('X');  // Vértice 0
    undirected_graph.add_vertex('Y');  // Vértice 1
    undirected_graph.add_vertex('Z');  // Vértice 2

    // Comprobar número de vértices
    assert(undirected_graph.num_vertices() == 3);

    // Añadir aristas al grafo no dirigido
    undirected_graph.add_edge(0, 1, 150); // Arista 0-1 con peso 150
    undirected_graph.add_edge(1, 2, 250); // Arista 1-2 con peso 250
    undirected_graph.add_edge(0, 2, 350); // Arista 0-2 con peso 350

    // Comprobar número de aristas
    assert(undirected_graph.num_edges() == 3);

    // Imprimir grafo no dirigido
    undirected_graph.print_graph();

    // Probar la obtención de vértices y aristas
    auto vertex_2 = undirected_graph.vertex(2);
    assert(vertex_2->data() == 'Z');
    std::cout << "Vertex 2 has label: " << vertex_2->label() << " and data: " << vertex_2->data() << std::endl;

    auto edge_02 = undirected_graph.edge(0, 2);
    assert(edge_02->weight() == 350);
    std::cout << "Edge between vertex 0 and vertex 2 has weight: " << edge_02->weight() << std::endl;

    return 0;
}

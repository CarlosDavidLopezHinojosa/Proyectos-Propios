#include "graph.hpp"
int main() {
    Graph<std::string, int> g(false);

    // Agregar vértices
    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");
    g.add_vertex("E");
    g.add_vertex("F");

    // Agregar aristas
    g.add_edge(0, 1, 10); // A - B
    g.add_edge(0, 2, 15); // A - C
    g.add_edge(1, 2, 12); // B - C
    g.add_edge(1, 3, 10); // B - D
    g.add_edge(2, 3, 10); // C - D
    g.add_edge(2, 4, 5);  // C - E
    g.add_edge(3, 4, 10); // D - E
    g.add_edge(3, 5, 10); // D - F
    g.add_edge(4, 5, 5);  // E - F
    g.add_edge(4, 1, 20); // E - B

    size_t start = 0; // Vértice 'A'
    size_t end = 5;   // Vértice 'F'

    std::cout << "Positions of vertices:\n";
    for (size_t i = 0; i < g.num_vertices(); ++i) {
        auto [x, y] = g.vertex(i)->position();
        std::cout << "Vertex " << g.vertex(i)->data() << ": (" << x << ", " << y << ")\n";
    }

    g.print_graph();

    auto [w, p] = g.a_star(start, end);

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

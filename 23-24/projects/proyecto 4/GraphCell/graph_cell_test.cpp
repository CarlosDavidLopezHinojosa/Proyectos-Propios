#include <iostream>
#include "graph_cell.hpp"
#include "vertex.hpp"
#include "edge.hpp"

int main() {
    // Crear un GraphCell
    auto graphCell = GraphCell<int, double>::create();

    // Crear un vértice y asignarlo al GraphCell
    auto vertex = Vertex<int>::create(1, 100);
    graphCell->set_vertex(vertex);

    // Crear aristas y añadirlas a la lista de aristas del GraphCell
    auto vertex2 = Vertex<int>::create(2, 200);
    auto edge1 = Edge<int, double>::create(vertex, vertex2, 5.5);
    graphCell->edge_list().push_back(edge1);

    auto vertex3 = Vertex<int>::create(3, 300);
    auto edge2 = Edge<int, double>::create(vertex, vertex3, 7.5);
    graphCell->edge_list().push_back(edge2);

    // Probar los métodos de GraphCell
    std::cout << "GraphCell Vertex Label: " << graphCell->vertex()->label() << std::endl;
    std::cout << "GraphCell Vertex Data: " << graphCell->vertex()->data() << std::endl;

    std::cout << "Edges connected to GraphCell Vertex:" << std::endl;
    for (const auto& edge : graphCell->edge_list()) {
        std::cout << "  Edge connects Vertex " << edge->u()->label() 
                  << " and Vertex " << edge->v()->label() 
                  << " with weight " << edge->weight() << std::endl;
    }

    return 0;
}
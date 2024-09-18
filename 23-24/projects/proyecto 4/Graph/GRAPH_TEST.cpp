#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
#include <limits>
#include <random>
#include <set>
#include "graph.hpp"  // Incluye tu definición de la clase Graph aquí

// Definir un alias para el tipo de datos del grafo
using GraphType = Graph<char, int>;

// Función para generar un grafo aleatorio
void generate_random_graph(GraphType& g, size_t num_vertices, size_t num_edges) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> vertex_dist(0, num_vertices - 1);
    std::uniform_int_distribution<> weight_dist(1, 20);

    std::set<std::pair<size_t, size_t>> edges;

    // Añadir vértices
    for (size_t i = 0; i < num_vertices; ++i) {
        g.add_vertex('A' + i);
    }

    // Añadir aristas
    while (edges.size() < num_edges) {
        size_t u = vertex_dist(gen);
        size_t v = vertex_dist(gen);

        // Evitar ciclos
        if (u != v && edges.find({u, v}) == edges.end() && edges.find({v, u}) == edges.end()) {
            int weight = weight_dist(gen);
            g.add_edge(u, v, weight);
            edges.insert({u, v});
        }
    }
}

int main() {
    size_t num_vertices = 20;
    size_t num_edges = 30;

    GraphType g(false);

    // Generar un grafo aleatorio con 20 vértices y 30 aristas
    generate_random_graph(g, num_vertices, num_edges);

    // Imprimir el grafo
    g.print_graph();

    // Medir el tiempo de ejecución de A*
    auto start = std::chrono::high_resolution_clock::now();
    auto path_a_star = g.a_star(0, num_vertices - 1); // Desde el primer vértice hasta el último
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_a_star = end - start;
    std::cout << "A* Algorithm Time: " << duration_a_star.count() << " seconds" << std::endl;

    // Imprimir el resultado de A*
    auto [distances_a_star, predecessors_a_star] = path_a_star;
    std::cout << "A* Path Distances: ";
    for (const auto& dist : distances_a_star) {
        std::cout << dist << " ";
    }
    std::cout << std::endl;

    std::cout << "A* Path Predecessors: ";
    for (const auto& pred : predecessors_a_star) {
        std::cout << pred << " ";
    }
    std::cout << std::endl;

    // Medir el tiempo de ejecución de Prim
    start = std::chrono::high_resolution_clock::now();
    auto mst_prim = g.prim_algorithm(0);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_prim = end - start;
    std::cout << "Prim's Algorithm Time: " << duration_prim.count() << " seconds" << std::endl;

    // Imprimir el MST resultante de Prim
    mst_prim.print_graph();

    // Medir el tiempo de ejecución de Kruskal
    start = std::chrono::high_resolution_clock::now();
    auto mst_kruskal = g.kruskal_algorithm();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_kruskal = end - start;
    std::cout << "Kruskal's Algorithm Time: " << duration_kruskal.count() << " seconds" << std::endl;

    // Imprimir el MST resultante de Kruskal
    mst_kruskal.print_graph();

    // Medir el tiempo de ejecución de Dijkstra
    start = std::chrono::high_resolution_clock::now();
    auto [distances_dijkstra, predecessors_dijkstra] = g.dijkstra_algorithm(0);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_dijkstra = end - start;
    std::cout << "Dijkstra's Algorithm Time: " << duration_dijkstra.count() << " seconds" << std::endl;

    // Imprimir el resultado de Dijkstra
    std::cout << "Dijkstra Path Distances: ";
    for (const auto& dist : distances_dijkstra) {
        std::cout << dist << " ";
    }
    std::cout << std::endl;

    std::cout << "Dijkstra Path Predecessors: ";
    for (const auto& pred : predecessors_dijkstra) {
        std::cout << pred << " ";
    }
    std::cout << std::endl;

    // Medir el tiempo de ejecución de Floyd-Warshall
    start = std::chrono::high_resolution_clock::now();
    auto shortest_paths_floyd = g.floyd_algorithm();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_floyd = end - start;
    std::cout << "Floyd-Warshall Algorithm Time: " << duration_floyd.count() << " seconds" << std::endl;

    // Imprimir la matriz de distancias más cortas de Floyd-Warshall
    std::cout << "Floyd-Warshall Shortest Paths Matrix: " << std::endl;
    for (const auto& row : shortest_paths_floyd) { std::cout << "[ ";
        for (const auto& dist : row) {
            if (dist == std::numeric_limits<int>::infinity()) {
                std::cout << "INF ";
            } else {
                std::cout << int(dist) << " ";
            }
        }
        std::cout <<" ]"<< std::endl;
    }

    return 0;
}

#pragma once
#include "vertex.hpp"
#include "edge.hpp"
#include "graph_cell.hpp"
#include "disjoint_set.hpp"

#include <stack>
#include <queue>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>


template <class T, class E>
class Graph
{
public:
    using VertexRef = typename Vertex<T>::VertexRef;
    using EdgeRef = typename Edge<T,E>::EdgeRef;
    using GraphCellRef = typename GraphCell<T,E>::GraphCellRef;
    using GraphRef = std::shared_ptr<Graph<T,E>>;
    using EdgeList = std::vector<EdgeRef>;
    using PathRegister = std::tuple<std::vector<E>,std::vector<size_t>>;
    using Heuristic = std::function<E(VertexRef,VertexRef)>;

    Graph(bool is_directed = false);
    ~Graph(){}

    //Getters
    VertexRef vertex (size_t label);
    EdgeRef edge (VertexRef u, VertexRef v);
    EdgeRef edge (size_t u, size_t v);
    bool is_directed() const;
    int num_vertices() const;
    int num_edges() const;
    E total_weight() const;

    //Adders
    void add_vertex(T data);
    void add_vertex(VertexRef new_vertex);
    void add_edge(VertexRef u, VertexRef v, E weight);
    void add_edge(size_t u, size_t v, E weight);
    void reset(bool new_state);
    
    //Print
    void print_graph();

    //Graph Trasversals
    Graph <T,E> dfs_spanning_tree();
    Graph <T,E> bfs_spanning_tree();

    //Graph Algorithm
    Graph <T,E> kruskal_algorithm();
    Graph <T,E> prim_algorithm(size_t start);
    PathRegister dijkstra_algorithm(size_t start);
    std::vector<std::vector<size_t>> floyd_algorithm();
    PathRegister a_star(size_t start, size_t begin, Heuristic H);
    PathRegister a_star(size_t start, size_t begin);


protected:
    std::vector<GraphCellRef> adjacent_list_;
    size_t next_label_;
    int num_vertices_;
    int num_edges_;
    E total_cost_;
    bool is_directed_;

private:
    void dfs(VertexRef vertex, Graph<T, E>& spanning_tree);
    
};


#include "graph_imp.hpp"

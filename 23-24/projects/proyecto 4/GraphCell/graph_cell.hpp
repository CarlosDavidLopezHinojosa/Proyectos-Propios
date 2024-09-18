#pragma once
#include "vertex.hpp"
#include "edge.hpp"
#include <vector>

template <class T,class E>
class GraphCell
{
    public:
    using VertexRef = typename Vertex<T>::VertexRef;
    using EdgeRef = typename Edge<T,E>::EdgeRef;
    using GraphCellRef = std::shared_ptr<GraphCell<T,E>>;
    using EdgeList = std::vector<EdgeRef>;

    GraphCell();
    ~GraphCell(){}

    //Getters
    VertexRef vertex() const;
    EdgeList& edge_list();

    //Setters
    void set_vertex(VertexRef new_vertex);

    //Pointers
    static GraphCellRef create ();


    protected:
    VertexRef vertex_;
    EdgeList edge_list_;
};

#include "graph_cell_imp.hpp"
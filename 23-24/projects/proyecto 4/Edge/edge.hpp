#pragma once
#include "vertex.hpp"

template <class T, class E>
class Edge
{
    public:
    using VertexRef = typename Vertex<T>::VertexRef;
    using EdgeRef = std::shared_ptr<Edge<T,E>>;

    Edge(VertexRef u, VertexRef v, E weight);
    ~Edge(){}

    //Getters
    E weight() const;
    VertexRef u() const;
    VertexRef v() const;
    bool is_visited() const;

    //Setters
    void set_weight(E new_weight);
    void set_u(VertexRef new_u);
    void set_v(VertexRef new_v);
    void set_visited(bool visited);

    //Pointers
    static EdgeRef create (VertexRef u, VertexRef v, E weight);

    //Auxiliar Functions.
    bool has(VertexRef vertex) const;
    VertexRef other(VertexRef vertex) const;

    protected:
    E weight_;
    VertexRef u_;
    VertexRef v_;
    bool is_visited_;
};

#include "edge_imp.hpp"
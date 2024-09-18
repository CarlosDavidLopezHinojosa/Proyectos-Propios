#pragma once
#include "edge.hpp"

// Constructor
template <class T, class E>
Edge<T, E>::Edge(VertexRef u, VertexRef v, E weight)
{
    set_u(u);
    set_v(v);
    set_weight(weight);
    set_visited(false);
}

// Getters
template <class T, class E>
E Edge<T, E>::weight() const 
{
    return weight_;
}

template <class T, class E>
typename Edge<T, E>::VertexRef Edge<T, E>::u() const 
{
    return u_;
}

template <class T, class E>
typename Edge<T, E>::VertexRef Edge<T, E>::v() const 
{
    return v_;
}

template <class T, class E>
bool Edge<T, E>::is_visited() const 
{
    return is_visited_;
}

// Setters
template <class T, class E>
void Edge<T, E>::set_weight(E new_weight) 
{
    weight_ = new_weight;
}

template <class T, class E>
void Edge<T, E>::set_u(VertexRef new_u) 
{
    assert(new_u != nullptr);  // Ensure the new vertex is not null
    u_ = new_u;
}

template <class T, class E>
void Edge<T, E>::set_v(VertexRef new_v) 
{
    assert(new_v != nullptr);  // Ensure the new vertex is not null
    v_ = new_v;
}

template <class T, class E>
void Edge<T, E>::set_visited(bool visited) 
{
    is_visited_ = visited;
}

// Pointers
template <class T, class E>
typename Edge<T, E>::EdgeRef Edge<T, E>::create(VertexRef u, VertexRef v, E weight) 
{
    return std::make_shared<Edge<T, E>>(u, v, weight);
}

// Auxiliary Functions
template <class T, class E>
bool Edge<T, E>::has(VertexRef vertex) const 
{
    return (vertex == u() || vertex == v());
}

template <class T, class E>
typename Edge<T, E>::VertexRef Edge<T, E>::other(VertexRef vertex) const 
{
    assert(has(vertex));  // Ensure that the vertex is part of the edge
    return (vertex == u()) ? v() : u();
}
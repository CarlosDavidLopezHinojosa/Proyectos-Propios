#pragma once
#include "vertex.hpp"

// Constructor
template <class T>
Vertex<T>::Vertex(size_t label, T data)
{
    set_label(label);
    set_data(data);
    set_visited(false);
    int h = int(std::hash<T>()(data));
    int g = int(std::hash<size_t>()(label));
    y_ = int((label*h) % (label + 100));
    x_ = (h)%(y_+1);
}

// Getters
template <class T>
size_t Vertex<T>::label() const 
{
    return label_;
}

template <class T>
T Vertex<T>::data() const 
{
    return data_;
}

template <class T>
bool Vertex<T>::is_visited() const 
{
    return is_visited_;
}

template <class T>
std::tuple<int,int> Vertex<T>::position() const
{
    return std::tuple(x_,y_);
}
// Setters
template <class T>
void Vertex<T>::set_label(size_t new_label) 
{
    assert(new_label >= 0);
    label_ = new_label;
}

template <class T>
void Vertex<T>::set_data(T new_data) 
{
    data_ = new_data;
}

template <class T>
void Vertex<T>::set_visited(bool visited) 
{
    is_visited_ = visited;
}

// Static create method
template <class T>
typename Vertex<T>::VertexRef Vertex<T>::create(size_t label, T data) 
{
    assert(label >= 0);
    return std::make_shared<Vertex<T>>(label, data);
}
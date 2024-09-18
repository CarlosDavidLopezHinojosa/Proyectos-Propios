#pragma once
#include <memory>
#include <cassert>
#include <functional>


template <class T>
class Vertex
{
    public:
    using VertexRef = std::shared_ptr<Vertex<T>>;
    Vertex(size_t label, T data);
    Vertex(size_t label,T data, int x, int y);
    ~Vertex(){}

    //Getters
    size_t label() const;
    T data() const;
    bool is_visited() const;
    std::tuple<int,int> position() const;

    //Setters
    void set_label(size_t new_label);
    void set_data(T new_data);
    void set_visited(bool visited);

    //Pointers
    static VertexRef create(size_t label, T data);

    protected:

    size_t label_;
    T data_;
    bool is_visited_;
    int x_;
    int y_;
};




#include "vertex_imp.hpp"
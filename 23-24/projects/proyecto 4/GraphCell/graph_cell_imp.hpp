#include "graph_cell.hpp"

template <class T, class E>
GraphCell<T, E>::GraphCell()
{
    vertex_ = nullptr;
    edge_list_ = {};
}

template <class T, class E>
typename GraphCell<T, E>::VertexRef 
GraphCell<T, E>::vertex() const 
{
    return vertex_;
}


template <class T, class E>
typename GraphCell<T, E>::EdgeList& 
GraphCell<T, E>::edge_list() 
{
    return edge_list_;
}

template <class T, class E>
void GraphCell<T, E>::set_vertex(VertexRef new_vertex) 
{
    vertex_ = new_vertex;
}

template <class T, class E>
typename GraphCell<T,E>::GraphCellRef 
GraphCell<T,E>::create ()
{
    return std::make_shared<GraphCell<T,E>>();
}
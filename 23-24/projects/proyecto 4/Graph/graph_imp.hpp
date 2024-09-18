#pragma once
#include "graph.hpp"


//Proper Graph Functions
template <class T, class E>
Graph<T, E>::Graph(bool is_directed) 
{
    adjacent_list_ = std::vector<GraphCellRef>(4,nullptr);
    next_label_ = 0;
    num_vertices_ = 0;
    num_edges_ = 0;
    total_cost_ = 0;
    is_directed_ = is_directed;
}

template <class T, class E>
typename Graph<T, E>::VertexRef 
Graph<T, E>::vertex(size_t label) 
{
    assert(label < adjacent_list_.size());
    return adjacent_list_[label]->vertex();
}

template <class T, class E>
typename Graph<T, E>::EdgeRef 
Graph<T, E>::edge(VertexRef u, VertexRef v) 
{
    assert(u->label() < adjacent_list_.size());

    EdgeList& l = adjacent_list_[u->label()]->edge_list();
    size_t v_label = v->label();

    auto f = [&v_label](const EdgeRef& e){return v_label == e->v()->label();};

    auto it = std::find_if(l.begin(),l.end(),f);

    return (it == l.end()) ? nullptr : *it;
}

template <class T, class E>
typename Graph<T, E>::EdgeRef 
Graph<T, E>::edge (size_t u, size_t v)
{
    assert(u < adjacent_list_.size() && v < adjacent_list_.size());
    return edge(adjacent_list_[u]->vertex(),adjacent_list_[v]->vertex());
}

template <class T, class E>
bool Graph<T,E>::is_directed() const
{
    return is_directed_;
}

template <class T, class E>
int Graph<T,E>::num_vertices() const
{
    return num_vertices_;
}

template <class T, class E>
int Graph<T,E>::num_edges() const
{
    return num_edges_;
}

template <class T, class E>
E Graph<T,E>::total_weight() const
{
    return total_cost_;
}

template <class T, class E>
void 
Graph<T, E>::add_vertex(T data) 
{
    VertexRef new_vertex = Vertex<T>::create(next_label_,data);
    GraphCellRef new_cell = GraphCell<T,E>::create();

    if (next_label_ >= adjacent_list_.size())
    {
        adjacent_list_.resize(next_label_*2,nullptr);
    }

    adjacent_list_[next_label_] = new_cell;
    adjacent_list_[next_label_++]->set_vertex(new_vertex);  
    num_vertices_++;  
}

template <class T, class E>
void 
Graph<T, E>::add_vertex(VertexRef new_vertex)
{
    GraphCellRef new_cell = GraphCell<T,E>::create();

    if (next_label_ >= adjacent_list_.size())
    {
        adjacent_list_.resize(next_label_ * 2,nullptr);
    }

    adjacent_list_[next_label_] = new_cell;
    adjacent_list_[next_label_++]->set_vertex(new_vertex);  
    num_vertices_++; 
}

template <class T, class E>
void 
Graph<T, E>::add_edge(VertexRef u, VertexRef v, E weight) 
{
    assert(u->label() < adjacent_list_.size());
    EdgeRef new_edge = Edge<T,E>::create(u, v, weight);
    EdgeList& l = adjacent_list_[u->label()]->edge_list();

    auto f = [](const EdgeRef& e1, const EdgeRef& e2) { return e1->v()->label() < e2->v()->label(); };

    auto it = std::lower_bound(l.begin(), l.end(), new_edge, f); //O(log n)

    l.insert(it, new_edge);

    if (!is_directed())
    {
        assert(v->label() < adjacent_list_.size());
        EdgeList& reverse_l = adjacent_list_[v->label()]->edge_list();
        auto reverse_edge = Edge<T,E>::create(v, u, weight);

        auto reverse_it = std::lower_bound(reverse_l.begin(), reverse_l.end(), reverse_edge,f);
        reverse_l.insert(reverse_it, reverse_edge);
    }

    num_edges_++;
    total_cost_ += weight;

}

template <class T, class E>
void 
Graph<T, E>::add_edge(size_t u, size_t v, E weight) 
{
    assert(u < adjacent_list_.size() && v < adjacent_list_.size());
    add_edge(vertex(u),vertex(v),weight);
}

template <class T, class E>
void Graph<T,E>::reset(bool new_state)
{
    for (size_t i = 0; i < new_state; i++)
    {
        vertex(i)->set_visited(new_state);
        for (auto &edge : adjacent_list_[i]->edge_list())
            edge->set_visited(new_state);
    }
    
}

template <class T, class E>
void Graph<T, E>::print_graph() {
    std::cout << "Graph (" << (is_directed_ ? "Directed" : "Undirected") << "):" << std::endl;

    for (size_t i = 0; i < next_label_; i++)
    {
        auto vertex = adjacent_list_[i]->vertex();
        auto l = adjacent_list_[i]->edge_list();

        std::cout << vertex->label() << ":" << vertex->data() << " -> [ ";
        for (auto& j : l)
        {
            std::cout << j->weight() << ":(" << j->v()->label() << ":" << j->v()->data() << ") ";
        }

        std::cout << "]\n";
    }
}



//Graph Algorithm:

//Recursive DFS
template <class T, class E>
Graph<T, E> Graph<T, E>::dfs_spanning_tree() 
{

    Graph <T,E> spanning_tree(false);

    for (size_t i = 0; i < next_label_; i++)
    {
        spanning_tree.add_vertex(vertex(i));
    }
    
    dfs(vertex(0), spanning_tree);

    return spanning_tree;
}


template <class T, class E>
void Graph<T, E>::dfs(VertexRef vertex, Graph<T, E>& spanning_tree) 
{
    vertex->set_visited(true);
    EdgeList& l = adjacent_list_[vertex->label()]->edge_list();

    for (size_t i = 0; i < l.size(); i++)
    {
        EdgeRef e = l[i];
        VertexRef v = e->v();

        if (!e->is_visited() && !v->is_visited())
        {
            e->set_visited(true);
            spanning_tree.add_edge(vertex,v,e->weight());
            dfs(v,spanning_tree);
        }   
    }
}
//

//BFS
template <class T, class E>
Graph<T, E> Graph<T, E>::bfs_spanning_tree()
{
    Graph <T,E> spanning_tree(false);
    std::queue<VertexRef> vertex_queue;

    for (size_t i = 0; i < next_label_; i++)
    {
        spanning_tree.add_vertex(vertex(i));
    }
    
    vertex_queue.push(vertex(0));
    vertex(0)->set_visited(true);

    while (!vertex_queue.empty())
    {
        VertexRef u = vertex_queue.front();
        vertex_queue.pop();
        EdgeList& l = adjacent_list_[u->label()]->edge_list();

        for (size_t i = 0; i < l.size(); i++)
        {
            EdgeRef e = l[i];
            VertexRef v = e->v();

            if (!v->is_visited())
            {   
                e->set_visited(true);
                v->set_visited(true);
                vertex_queue.push(v);
                spanning_tree.add_edge(u,v,e->weight());
            }   
        }
    }

    return spanning_tree;
}
//

template <class T, class E>
Graph<T, E> Graph<T, E>::prim_algorithm(size_t start) {
    int n = num_vertices();
    std::vector<size_t> V(n, -1);
    std::vector<bool> A(n, false);
    std::vector<E> C(n, std::numeric_limits<E>::max());
    Graph<T, E> mst(false);

    for(size_t i = 0; i < n; i++)
    {
        mst.add_vertex(vertex(i));
    }

    size_t u = start;
    A[u] = true;
    C[u] = E();

    for(size_t i = 1; i < n; i++)
    {
        EdgeList& l = adjacent_list_[u]->edge_list();
        for(EdgeRef& e : l)
        {
            size_t v = e->v()->label();
            if(!A[v] && e->weight() < C[v])
            {
                V[v] = u;
                C[v] = e->weight();
            }
        }

        E least_cost = std::numeric_limits<E>::max();
        for(size_t j = 0; j < n; j++)
        {
            if(!A[j] && C[j] < least_cost)
            {
                least_cost = C[j];
                u = j; 
            }
        }

        if(least_cost == std::numeric_limits<E>::max())
        {
            throw std::runtime_error("It's an unconnected graph.");
        }

        mst.add_edge(V[u], u, C[u]);
        A[u] = true;
    }

    return mst;
}


template <class T,class  E>
Graph <T,E> Graph <T,E>::kruskal_algorithm()
{

    std::vector<EdgeRef> edges;
    Graph<T,E> mst(false);
    DisjointSet set (num_vertices());

    for (size_t i = 0; i < num_vertices(); i++)
    {
        mst.add_vertex(vertex(i));

        EdgeList& l = adjacent_list_[i]->edge_list();
        edges.insert(edges.end(),l.begin(),l.end());
    }

    auto comp = [](const EdgeRef& a, const EdgeRef& b)
    {
        if (a->weight() == b->weight())
        {
            if (a->u()->label() == b->u()->label())
            {
                return a->v()->label() < b->v()->label();
            }

            return a->u()->label() < b->u()->label();
        }

        return a->weight() < b->weight();  
    };
    
    std::sort(edges.begin(),edges.end(),comp);

    for (size_t i = 0; mst.num_edges() < mst.num_vertices()-1; i++)
    {
        size_t u = edges[i]->u()->label();
        size_t v = edges[i]->v()->label();
        E w = edges[i]->weight();

        if (set.find(u) != set.find(v))
        {
            set.union_sets(u,v);
            mst.add_edge(u,v,w);
        }
    }

    return mst;
}

//Dijkstra's Algorithm
template <class T, class E>
typename Graph<T,E>::PathRegister
Graph<T,E>::dijkstra_algorithm(size_t start)
{
    assert(start < num_vertices());
    using Tuple = std::tuple<E,size_t,size_t>;

    std::vector<E> distances(num_vertices(),std::numeric_limits<E>::infinity());
    std::vector<size_t> predecesors(num_vertices());
    std::priority_queue<Tuple,std::vector<Tuple>,std::greater<Tuple>> pq;

    for (size_t i = 0; i < num_vertices(); i++)
    {
        predecesors[i] = i;
    }

    reset(false);

    pq.push({E(),start,start});

    E w;
    size_t u;
    size_t v;

    while (!pq.empty())
    {
        std::tie(w,u,v) = pq.top();
        pq.pop();
        
        VertexRef u_vertex = vertex(u);

        if (!u_vertex->is_visited())
        {
            predecesors[u] = v;
            distances[u] = w;

            u_vertex->set_visited(true);

            EdgeList& l = adjacent_list_[u]->edge_list();

            for (size_t i = 0; i < l.size(); i++)
            {
                VertexRef v_vertex = l[i]->v();

                if (!v_vertex->is_visited())
                {   
                    E new_weight = w + l[i]->weight();
                    if(new_weight - w < 0){std::cerr << "\nError: In Dijkstra's Algorithm all edge's weights must be positive\n"; exit(EXIT_FAILURE);}
                    distances[v_vertex->label()] = new_weight;
                    pq.push({new_weight,v_vertex->label(),u});
                }                                
            }           
        }
    }

    return std::tuple(distances,predecesors);
}
//

//Floyd Algorithm
template <class T, class E>
std::vector<std::vector<size_t>> Graph<T,E>::floyd_algorithm()
{

    int n = num_vertices();
    
    std::vector<std::vector<size_t>> I(n, std::vector<size_t>(n, -1));
    std::vector<std::vector<E>> W(n, std::vector<E>(n, std::numeric_limits<E>::infinity()));


    for (size_t i = 0; i < num_vertices(); i++)
    {
        EdgeList& l = adjacent_list_[i]->edge_list();
        for (size_t j = 0; j < l.size(); j++)
        {
            size_t v = l[j]->v()->label();
            W[i][v] = l[j]->weight();

            if (!is_directed())
            {
                W[v][i] = l[j]->weight();
            }            
        }        
    }

    for (size_t k = 0; k < n; k++)
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (W[i][k] + W[k][j] < W[i][j])
                {
                    W[i][j] = W[i][k] + W[k][j];
                    I[i][j] = k;
                }  
            }   
        }
    }

    return I;
}
//


template<class T, class E>
typename Graph<T,E>::PathRegister 
Graph<T,E>::a_star(size_t start, size_t end, Heuristic H)
{
        assert(start < num_vertices());
    using Tuple = std::tuple<E,E,size_t,size_t>;

    std::vector<E> distances(num_vertices(),std::numeric_limits<E>::infinity());
    std::vector<size_t> predecesors(num_vertices());
    std::priority_queue<Tuple,std::vector<Tuple>,std::greater<Tuple>> pq;

    for (size_t i = 0; i < num_vertices(); i++)
    {
        predecesors[i] = i;
    }

    reset(false);

    pq.push({E(),E(),start,start});

    E h;
    E w;
    size_t u;
    size_t v;

    while (!pq.empty())
    {
        std::tie(h,w,u,v) = pq.top();
        pq.pop();
        
        VertexRef u_vertex = vertex(u);

        if (!u_vertex->is_visited())
        {
            predecesors[u] = v;
            distances[u] = w;

            u_vertex->set_visited(true);

            EdgeList& l = adjacent_list_[u]->edge_list();

            for (size_t i = 0; i < l.size(); i++)
            {
                VertexRef v_vertex = l[i]->v();

                if (!v_vertex->is_visited())
                {   
                    E new_weight = w + l[i]->weight();
                    E new_heuristic = new_weight + H(vertex(i),vertex(end));
                    if(new_weight - w < 0){std::cerr << "\nError: In A* Algorithm all edge's weights must be positive\n"; exit(EXIT_FAILURE);}
                    distances[v_vertex->label()] = new_weight;
                    pq.push({new_heuristic,new_weight,v_vertex->label(),u});
                }                                
            }           
        }
    }

    return std::tuple(distances,predecesors);
}

template<class T, class E>
typename Graph<T,E>::PathRegister 
Graph<T,E>::a_star(size_t start, size_t end)
{
    Heuristic default_heuristic = [&](VertexRef u, VertexRef v) -> E
    {
        int u_x,u_y;
        int v_x,v_y;

        std::tie(u_x,u_y) = u->position();
        std::tie(v_x,v_y) = v->position();

        return E(std::abs(u_x - v_y) + std::abs(u_y - v_y));        
    };

    return a_star(start,end,default_heuristic);
}
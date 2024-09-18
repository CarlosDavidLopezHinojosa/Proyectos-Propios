#include <vector>
#include <algorithm>

class DisjointSet {
private:
    std::vector<size_t> parent, rank;

public:
    // Inicializar conjuntos disjuntos para n elementos
    DisjointSet(size_t n) : parent(n), rank(n, 0) 
    {
        for (size_t i = 0; i < n; ++i)
            parent[i] = i; // Cada elemento es su propio padre
    }

    // Encontrar la raíz de un elemento (con compresión de ruta)
    size_t find(size_t u) 
    {
        if (u != parent[u])
            parent[u] = find(parent[u]); // Compresión de ruta
        return parent[u];
    }

    // Unir dos conjuntos
    void union_sets(size_t u, size_t v) 
    {
        u = find(u);
        v = find(v);

        if (u != v) {
            // Union por rango
            if (rank[u] < rank[v])
                std::swap(u, v);
            parent[v] = u;
            if (rank[u] == rank[v])
                ++rank[u];
        }
    }
};

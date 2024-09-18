cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(GraphLibrary)

# Establecer el estándar de C++ para el proyecto
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir las carpetas como directorios de inclusión
include_directories(${CMAKE_SOURCE_DIR}/Edge)
include_directories(${CMAKE_SOURCE_DIR}/Graph)
include_directories(${CMAKE_SOURCE_DIR}/GraphCell)
include_directories(${CMAKE_SOURCE_DIR}/Vertex)
include_directories(${CMAKE_SOURCE_DIR}/DisjointSet)
include_directories(${CMAKE_SOURCE_DIR}/GraphAlgorithms)

# Archivos de código fuente
set(EDGE_SOURCES
    Edge/edge.hpp
    Edge/edge_imp.hpp
    Edge/edge_test.cpp
)

set(GRAPH_SOURCES
    Graph/graph.hpp
    Graph/graph_imp.hpp
    Graph/graph_test.cpp
)

set(GRAPHCELL_SOURCES
    GraphCell/graph_cell.hpp
    GraphCell/graph_cell_imp.hpp
    GraphCell/graph_cell_test.cpp
)

set(VERTEX_SOURCES
    Vertex/vertex.hpp
    Vertex/vertex_imp.hpp
    Vertex/vertex_test.cpp
)

# Archivo de test independiente para DFS spanning tree
set(DFS_TEST_SOURCES
    Graph/dfs_test.cpp
)

set(BFS_TEST_SOURCES
    Graph/bfs_test.cpp
)

set(DIJKSTRA_TEST_SOURCES
    Graph/dijkstra_test.cpp
)

set(FLOYD_TEST_SOURCE
    Graph/floyd_test.cpp
)

set(KRUSKAL_TEST_SOURCE
    Graph/kruskal_test.cpp
)

set(PRIM_TEST_SOURCE
    Graph/prim_test.cpp
)

set(A_STAR_TEST_SOURCE
    Graph/a_star_test.cpp
)

set(TEST
    Graph/GRAPH_TEST.cpp
)

# Añadir los ejecutables para cada conjunto de tests
add_executable(edge_test ${EDGE_SOURCES})
add_executable(graph_test ${GRAPH_SOURCES})
add_executable(graph_cell_test ${GRAPHCELL_SOURCES})
add_executable(vertex_test ${VERTEX_SOURCES})
add_executable(dfs_test ${DFS_TEST_SOURCES})
add_executable(bfs_test ${BFS_TEST_SOURCES})
add_executable(dijkstra_test ${DIJKSTRA_TEST_SOURCES})
add_executable(floyd_test ${FLOYD_TEST_SOURCE})
add_executable(kruskal_test ${KRUSKAL_TEST_SOURCE})
add_executable(prim_test ${PRIM_TEST_SOURCE})
add_executable(a_star_test ${A_STAR_TEST_SOURCE})
add_executable(GRAPH_TEST ${TEST})

# Especificar que el ejecutable requiere linkage con pthreads (si es necesario)
find_package(Threads REQUIRED)
target_link_libraries(edge_test PRIVATE Threads::Threads)
target_link_libraries(graph_test PRIVATE Threads::Threads)
target_link_libraries(graph_cell_test PRIVATE Threads::Threads)
target_link_libraries(vertex_test PRIVATE Threads::Threads)

# Opcional: Si quieres correr todos los tests juntos
add_custom_target(run_all_tests
    COMMAND edge_test
    COMMAND graph_test
    COMMAND graph_cell_test
    COMMAND vertex_test
    COMMAND dfs_test
)

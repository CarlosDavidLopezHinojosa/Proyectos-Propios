cmake_minimum_required (VERSION 3.5)
project (B-Tree LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")


add_executable(lb_test lb.cpp)
add_executable(lb2_test lb2.cpp)
add_executable(root_test root.cpp B-TreeEntry_imp.hpp B-TreeEntry.hpp B-TreeNode_imp.hpp B-TreeNode.hpp)



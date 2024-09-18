# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(FCFS_Scheduler)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir el ejecutable
add_executable(FCFS_Scheduler FCFS.cpp)

# Incluir directorios para cabeceras (si planificator.hpp está en un subdirectorio, añadir la ruta correspondiente)
include_directories(${CMAKE_SOURCE_DIR})

# Opcional: Si tienes alguna librería que quieras linkear, puedes hacerlo aquí (ejemplo con pthread)
# target_link_libraries(FCFS_Scheduler pthread)

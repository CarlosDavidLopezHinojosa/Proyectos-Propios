#include "planificator.hpp"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    // Crear una lista de procesos con sus etiquetas, tiempos de CPU y tiempos de llegada
    std::vector<process> processes = {
        process('A', 0, 3),  
        process('B', 2, 6),  
        process('C', 4, 4),
        process('D', 6, 5),
        process('E', 8, 2)   
    };

    // Crear un planificador FCFS
    FBMLPQ fcfs_scheduler(processes,[](process p){return std::pow(2,p.priority());},2);


    // Ejecutar la planificación
    std::list<char> execution_order = fcfs_scheduler.schedule();

    // Imprimir el orden de ejecución
    std::cout << "Orden de ejecución de los procesos: ";
    for (char process_label : execution_order)
    {
        std::cout << process_label << " ";
    }
    std::cout << std::endl;

    return 0;
}

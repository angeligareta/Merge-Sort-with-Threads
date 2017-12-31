#include "Sort/merge_sort.h"
 
#include <iostream>
#include <cstring>
#include <fstream>

int main (int argc, char* argv[])
{
    system("clear");
    
    if (argc==1) {
        std::cout << "Introduzca por la línea de comandos un archivo con vector\n";
        return 0;
    }
    
    Vector vector;
    std::ifstream file_entry;
    file_entry.open(argv[1]);
    
    if (!file_entry.is_open()) {
        std::cout << "Error leyendo el fichero del vector\n";
        return 0;
    }
    
    file_entry >> vector;
    
    bool verbose = false;
    
    if ( argc >= 4 && strcmp(argv[3],"0") )
        verbose = true;
    
    if ( argc >= 3 && strcmp(argv[2],"0") )
        vector.MergeSort(false, verbose);
    else
        vector.MergeSort(true, verbose);
    
    std::cout << vector;
    
}
#include "merge_sort.h"

std::ostream& operator<<(std::ostream& out, const Vector& vector)
{
    std::cout << "Su vector final es: { ";
    
    for ( auto number : vector.integer_vector_ )
        out << number << ' ';
    
    std::cout << "}\n\nGracias por utilizar el programa\n";
    std::cout << "By Ángel Igareta\n";
}

std::istream& operator>>(std::istream& in, Vector &vector)
{
    while (!in.eof()){
        int number; in >> number;
        vector.integer_vector_.push_back(number);
    }
    
    std::cout << "El vector introducido es: "; vector.PrintIntegerVector(vector.integer_vector_); std::cout << '\n';
}

Vector::Vector():
integer_vector_()
{}

Vector::~Vector()
{}

void Vector::MergeSort(const bool& option, bool verbose)
{
    if (option){
        if (verbose) std::cout << "\nUsando método Recursivo...\n";
        MergeSortRec(integer_vector_, verbose);
    }
    else{
        if (verbose) std::cout << "\nUsando método Iterativo...\n";
        MergeSortIter(integer_vector_, verbose);
    } 
}

void Vector::MergeSortIter(std::vector<int>& vector, bool verbose)
{
    std::vector< std::vector<int> > vector_split;
    
    if (verbose) {
        std::cout << "Divido el vector "; PrintIntegerVector(vector); std::cout << " en grupos de dos:\n";
    }
    // Los divido en x grupos de 2 y los ordenamos.
    for ( int i=0 ; i < vector.size()-1 ; i+=2 ) {
        if (verbose) { 
            PrintIntegerVector( std::vector<int> {vector[i], vector[i+1]} ); 
            std::cout << std::endl; 
        }
        vector_split.push_back( SimpleSort( std::vector<int> {vector[i], vector[i+1]} ) );
    }
    
    // Si n es impar fusionamos la primera división con el último.
    if ( vector.size()%2 != 0 )
        vector_split[0] = MergeVector(vector_split[0], std::vector<int> {vector[vector.size()-1]} , verbose);
    
    // Los empiezo a fusionar odenadamente hasta que se unan todos en una división.
    while (vector_split.size() != 1) {
        for ( int i=0 ; i < vector_split.size() ; i++ ) {
            if (!vector_split[i+1].empty()) {
                vector_split[i] = MergeVector(vector_split[i], vector_split[i+1], verbose);
                vector_split.erase(vector_split.begin() + i + 1);
            }
        }
    }
    
    vector = vector_split[0];
}

void Vector::MergeSortRec(std::vector<int>& vector, bool verbose)
{
    // Si el tamaño del vector es dos o menos, lo ordeno si no está ordenado
    if ( vector.size() <= 2 ) {
        vector = SimpleSort(vector);
    }
    else {
        /* Divido los vectores en dos de tamaño intencionadamente igual. Nota: No necesito
        sumar uno al segundo porque el rango de los iteradores son: [begin, end)*/
        std::vector<int> vector_1 (vector.begin(), vector.begin() + vector.size()/2);
        std::vector<int> vector_2 (vector.begin() + vector.size()/2, vector.end());
        
        //Muestro el proceso
        if (verbose) PrintSplitVector(vector, vector_1, vector_2);
        
        // Llamo a esta misma función para ordenarlos si se puede.
        std::thread thread_vector_1 (&Vector::MergeSortRec, this, std::ref(vector_1), verbose);
        std::thread thread_vector_2 (&Vector::MergeSortRec, this, std::ref(vector_2), verbose);
        
        thread_vector_1.join();
        thread_vector_2.join();
        
        // Aqui empieza la llamada de retorno. Voy uniendo los vectores resultantes.
        vector = MergeVector(vector_1, vector_2, verbose);
    }
}

std::vector<int> Vector::MergeVector (std::vector<int> vector_1, std::vector<int> vector_2, bool verbose)
{
    // Añado los centinelas
    vector_1.push_back(MAXINT); vector_2.push_back(MAXINT);
    
    // Inicializo las variables que voy a utilizar
    std::vector<int> vector_solution; int i=0,j=0;
    
    // Uno los vectores de manera ordenada
    while ( i != (vector_1.size()-1) || j != (vector_2.size()-1) ) {
        vector_solution.push_back( (vector_1[i] < vector_2[j] ) ? vector_1[i++] : vector_2[j++] );
    }
    
    if (verbose) PrintMergeVector(vector_1,vector_2,vector_solution);
    
    // Devuelvo el vector fusión ordenado.
    return vector_solution;
}

std::vector<int> Vector::SimpleSort(const std::vector<int>& vector)
{
    std::vector<int> sort_vector = vector;
    
    if ( sort_vector.size() == 2 && sort_vector[0] > sort_vector[1] )
        std::swap(sort_vector[0], sort_vector[1]);
    
    return sort_vector;
}

void Vector::PrintIntegerVector(const std::vector<int>& vector)
{
    std::cout  << "{ ";
    for ( auto number : vector )
        std::cout << number << ' ';
    std::cout  << "}";
}

void Vector::PrintSplitVector(const std::vector<int>& vector, const std::vector<int>& vector_1, const std::vector<int>& vector_2)
{
    mutex_.lock();
    std::cout  << "\nDivido el vector "; PrintIntegerVector(vector); std::cout << " en: \n";
    PrintIntegerVector(vector_1); std::cout << "\n";
    PrintIntegerVector(vector_2); std::cout << "\n";
    std::cout  << "\n";
    mutex_.unlock();
}

void Vector::PrintMergeVector(const std::vector<int>& vector_1, const std::vector<int>& vector_2, const std::vector<int>& vector)
{
    mutex_.lock();
    std::cout  << "\nFusionó el vector "; 
    PrintIntegerVector( std::vector<int> (vector_1.begin(), vector_1.end()-1) ); 
    std::cout << " y ";
    PrintIntegerVector( std::vector<int> (vector_2.begin(), vector_2.end()-1));
    std::cout << " en:\n";
    PrintIntegerVector(vector); std::cout << "\n";
    std::cout  << "\n";
    mutex_.unlock();
}
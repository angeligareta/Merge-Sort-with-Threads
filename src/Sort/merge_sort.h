#include <iostream>
#include <vector>
#include <algorithm>

#include <mutex>
#include <thread>
#include <cxxabi.h> // Para request cancellation

// Preguntar si se puede sobrecargar << con template

#define MAXINT 32767

class Vector {
    
    friend std::ostream& operator<<(std::ostream&, const Vector &);
    friend std::istream& operator>>(std::istream&, Vector &);
    
    private:
    
    std::vector<int> integer_vector_;
    std::mutex mutex_;
    
    public:
    
    Vector();
    
    ~Vector();
    
    void MergeSort(const bool&, bool);
    
    private:
    
    void MergeSortIter(std::vector<int>&, bool);
    
    void MergeSortRec(std::vector<int>&, bool);
    
    std::vector<int> MergeVector(std::vector<int>, std::vector<int> , bool);
    
    void PrintIntegerVector(const std::vector<int>&);
    
    void PrintSplitVector(const std::vector<int>&, const std::vector<int>&, const std::vector<int>&);
    
    void PrintMergeVector(const std::vector<int>&, const std::vector<int>&, const std::vector<int>&);
    
    std::vector<int> SimpleSort(const std::vector<int>&);
};
#include <iostream>
#include "Instance.h"
#include "Solver_parent.hpp"

// Syntaxe de boost qui permet de créer une matrice de float de dimension 2
typedef boost::multi_array<float, 2> array_type;
typedef array_type::index index;

class Solver_Kmeans{
    private:
    float seuil;
    int maxinter;
    array_type *DP_matrix;


    public:
    Solver_Kmeans(int n, int k, string filename);

}

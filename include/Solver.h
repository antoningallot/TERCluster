#include <iostream>
#include <vector>
#include "Instance.h"
#include "boost/multi_array.hpp"

// Syntaxe de boost qui permet de créer une matrice de float de dimension 2
typedef boost::multi_array<float, 2> array_type;
typedef array_type::index index;

// Commentaire pour débuguer le git

class Solver {
    private:
    Instance pareto;
    array_type matrix;
    std::vector<int> solution;


    public:
    Solver(Instance &p, int N, int K);
    float min_DP(int i, int k);
    void DP(int N, int K);
    void backtrack(int N, int K);
    std::vector<int> getSolution();
    void fillArray();
};
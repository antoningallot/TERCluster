#include <iostream>
#include <vector>
#include "Solver_parent.hpp"
#include "boost/multi_array.hpp"

// Syntaxe de boost qui permet de créer une matrice de float de dimension 2
typedef boost::multi_array<float, 2> array_type;
typedef array_type::index index;

// Commentaire pour débuguer le git

class Solver : public Solver_parent {
    private:
    array_type *DP_matrix;

    public:
    Solver(int n, int k, std::string filename);
    void initMatrix();
    void displayMatrix();
    float min_DP(int i, int k, int methode);
    void solve(int methode);
    void backtrack(int methode);
    
};
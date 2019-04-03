#ifndef SOLVER_PARENT_H
#define SOLVER_PARENT_H

#include <vector>
#include "Instance.h"

class Solver_parent {
    
    protected:
    Instance *pareto;
    std::vector<std::pair<int, int> > *solution;
    int N;
    int K;

    public:
    Solver_parent();
    Solver_parent(int n, int k, std::string filename);
    std::vector<std::pair<int, int> > getSolution();
    void displayPareto();
    void displaySolution();
    void solve(int methode);
};

#endif
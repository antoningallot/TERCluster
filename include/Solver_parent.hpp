#include <vector>
#include "Instance.h"

class Solver_parent {
    
    protected:
    Instance *pareto;
    std::vector<int> *solution;
    int N;
    int K;

    public:
    Solver_parent();
    Solver_parent(int n, int k, std::string filename);
    std::vector<int> getSolution();
    void displayPareto();
    void displaySolution();
    void solve();
};
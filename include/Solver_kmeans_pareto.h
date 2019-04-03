#include <iostream>
#include <vector>
#include "Solver_parent.hpp"

class Solver_kmeans_pareto : public Solver_parent{
    private:
    float seuil;
    int maxinter;

    public:
    Solver_kmeans_pareto(int n, int k, std::string filename, float s, int m);
    void write_result(std::string filename);
    Point cost_means(std::pair<int,int> pair);
    void K_means_pareto();
};

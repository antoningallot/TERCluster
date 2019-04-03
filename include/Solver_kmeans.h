#include <iostream>
#include <vector>
#include "Solver_parent.hpp"

class Solver_kmeans : public Solver_parent{
    private:
    float seuil;
    int maxinter;

    public:
    Solver_kmeans(int n, int k, std::string filename, float s, int m);
    void displayCluster(std::vector<std::vector<int> > vect);
    Point cost_means(std::vector<int> vect);
    void K_means();
};

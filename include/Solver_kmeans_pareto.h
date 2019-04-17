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
    //Point cost_means(std::pair<int,int> pair);
    Point kmeans_center(std::pair<int,int> pair);
    Point kmedoids_center(std::pair<int,int> pair);
    Point kmedian_center(std::pair<int,int> pair);
    Point dcenter(std::pair<int,int> pair);
    Point dcenterv2(std::pair<int,int> pair);
    Point ccenter(std::pair<int,int> pair);
    void solve(int methode);
    float get_result(int methode);
};

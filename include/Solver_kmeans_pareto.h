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
    Point kmeans_center(std::vector<int> vect);
    Point kmedoids_center(std::vector<int> vect);
    Point kmedian_center(std::vector<int> vect);
    Point dcenter(std::vector<int> vect);
    Point ccenter(std::vector<int> vect);
    void solve(int methode);
    float get_result(int methode);
};

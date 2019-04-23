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
    Point kmeans_center(std::pair<int,int> pair);
    Point kmedoids_center(std::pair<int,int> pair);
    Point kmedian_center(std::pair<int,int> pair);
    Point dcenter(std::pair<int,int> pair);
    Point dcenterv2(std::pair<int,int> pair);
    Point ccenter(std::pair<int,int> pair);
    /*Point kmeans_center(std::vector<int> vect);
    Point kmedoids_center(std::vector<int> vect);
    Point kmedian_center(std::vector<int> vect);
    Point dcenter(std::vector<int> vect);
    Point dcenterv2(std::vector<int> vect);
    Point ccenter(std::vector<int> vect);*/
    void solve(int methode);
    float get_result(int methode);
};

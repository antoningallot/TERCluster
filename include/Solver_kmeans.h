#ifndef SOLVER_KMEANS_H
#define SOLVER_KMEANS_H

#include <iostream>
#include <vector>
#include "Solver_parent.hpp"

class Solver_kmeans : public Solver_parent{
    private:
    float seuil;
    int maxinter;
    float result;

    public:
    Solver_kmeans(int n, int k, std::string filename, float s, int m);
    void displayCluster(std::vector<std::vector<int> > vect);
    bool belongs(Point p, std::vector<Point> v);
    Point kmeans_center(std::vector<int> vect);
    Point kmedoids_center(std::vector<int> vect);
    Point kmedian_center(std::vector<int> vect);
    Point dcenter(std::vector<int> vect);
    Point ccenter(std::vector<int> vect);
    void solve(int methode);
    float get_result(int methode);
};

#endif
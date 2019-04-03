#ifndef INSTANCE_H
#define INSTANCE_H

#include "Point.h"
#include "boost/multi_array.hpp"
#include <vector>

typedef boost::multi_array<float, 2> array_type;
typedef array_type::index idx;

class Instance {
    private:
    std::vector<Point> *pareto;
    int N;
    array_type *matrix;


    public:
    Instance();
    Instance(int n, std::string filename);
    std::vector<Point> parsing (int n, std::string filename);
    void display();
    Point getPoint(int i);
    int getSize();
    void displayMatrix();
    void initMatrix();
//Calcul avec matrice
    float cost_median_matrix(int i, int iprime);
    float cost_means_matrix(int i, int iprime);
    float cost_medoids_matrix(int i, int iprime);
    float cost_dcenter_matrix(int i, int iprime);
    float cost_dcenterv2_matrix(int i, int iprime);
    float cost_ccenter_matrix(int i, int iprime);
//Calcul sans matrice    
    float cost_median(int i, int iprime);
    float cost_means(int i, int iprime);
    float cost_medoids(int i, int iprime);
    float cost_dcenter(int i, int iprime);
    float cost_dcenterv2(int i, int iprime);
    float cost_ccenter(int i, int iprime);
};

#endif
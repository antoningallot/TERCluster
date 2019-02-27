#include "Point.h"
#include "boost/multi_array.hpp"
#include <vector>

typedef boost::multi_array<float, 2> array_type;
typedef array_type::index idx;

class Instance {
    private:
    std::vector<Point> pareto;
    int N;
    int K;
    array_type matrix;


    public:
    Instance();
    Instance(std::vector<Point> v);
    Point getPoint(int i);
    void displayMatrix();
    void initMatrix();
//Calcul avec matrice    
    float cost_median(int i, int iprime);
    float cost_means(int i, int iprime);
    float cost_medoids(int i, int iprime);
    float cost_dcenter(int i, int iprime);
    float cost_dcenterv2(int i, int iprime);
    float cost_ccenter(int i, int iprime);
//Calcul sans matrice    
    float old_cost_median(int i, int iprime);
    float old_cost_medoids(int i, int iprime);
    float old_cost_dcenter(int i, int iprime);
    float old_cost_dcenterv2(int i, int iprime);
    float old_cost_ccenter(int i, int iprime);
};
#include "Point.h"
#include <vector>

class Instance {
    private:
    std::vector<Point> pareto;
    int N;
    int K;

    public:
    Instance();
    Instance(std::vector<Point> v);
    Point getPoint(int i);
    float cost_median(int i, int iprime);
    float cost_means(int i, int iprime);
    float cost_medoids(int i, int iprime);
    float cost_dcenter(int i, int iprime);
    float cost_ccenter(int i, int iprime);
};
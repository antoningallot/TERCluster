#include "Point.h"
#include <vector>

class Instance {
    private:
    std::vector<Point> pareto;
    int N;
    int K;

    public:
    Instance();
    float cost_median(int i, int iprime);
};
#include <iostream>
#include "Instance.h"

class Solver_Kmeans{
    private:
    Instance pareto;

    public:
    Solver_Kmeans(Instance &p);
    void k_means_pareto(int N, int K);
}
#include <iostream>
#include <vector>
#include "Instance.h"
#include "boost/multi_array.hpp"

typedef boost::multi_array<float, 2> array_type;
typedef array_type::index index;

class Solver {
    private:
    Instance pareto;
    array_type matrix;


    public:
    Solver(Instance &p, int N, int K);
    float min_DP(int i, int k);
    void DP(int N, int K);
    float backtrack(int N, int K);
};
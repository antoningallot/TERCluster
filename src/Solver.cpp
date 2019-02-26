#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

Solver::Solver(Instance &p, int N, int K) : pareto(p), matrix(boost::extents[N][K]) {}

vector<int> Solver::getSolution(){
    return solution;
}

float Solver::min_DP(int i, int k){
        float min = matrix[0][k-1] + pareto.cost_median(1, i);
        for (int j = 2; j < i; j++){
            float tmp = matrix[j-1][k-1] + pareto.cost_median(j, i);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
}

void Solver::DP(int N, int K){
        //vector<vector<float> > C (N, vector<float> (N));
        for (int i = 0; i < N; i++){
            matrix[i][1] = pareto.cost_median(1, i);
            for (int k = 2; k < K; k++){
                matrix[i][k] = min_DP(i, k);
            }
        }
        //return C[N][K];
}

void Solver::backtrack(int N, int K){
    int i = N;
    for (int k = K; k > 0; k--){
        for (int j = 0; j < i; j++){
            float tmp = matrix[j-1][k-1] + pareto.cost_median(j, i);
            if(matrix[i][k] == tmp){
                solution.push_back(i);
                i = j-1;
            }
        }
    }
}
#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

Solver::Solver(Instance p, int N, int K) : pareto(p), matrix(boost::extents[N][K]) {}



float Solver::min_DP(int i, int k){
        float min = matrix[0][k-1] + pareto.cost_median(1, i);
        for (int j = 2; j < i; j++){
            float tmp = this->matrix[j-1][k-1] + pareto.cost_median(j, i);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
    }

void Solver::DP(int N, int K){
        vector<vector<float> > C (N, vector<float> (N));
        for (int i = 0; i < N; i++){
            C[i][1] = pareto.cost_median(1, i);
            for (int k = 2; k < K; k++){
                C[i][k] = min_DP(i, k);
            }
        }
        //return C[N][K];
    }

    float backtrack(vector<vector<float> > compute, vector<vector<float> > C, int N, int K){
        
    }
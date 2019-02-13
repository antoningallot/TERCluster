#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"

float min_DP(vector<vector<float> > C, int i, int k){
        float min = C[0][k-1] + cost_median(1, i);
        for (int j = 2; j < i; j++){
            float tmp = C[j-1][k-1] + cost_median(j, i);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
    }

    float DP(vector<vector<float> > compute, int N, int K){
        vector<vector<float> > C (N, vector<float> (N));
        for (int i = 0; i < N; i++){
            C[i][1] = compute[1][i];
            for (int k = 2; k < K; k++){
                C[i][k] = min_DP(C, i, k);
            }
        }
        return C[N][K];
    }

    float backtrack(vector<vector<float> > compute, vector<vector<float> > C, int N, int K){
        
    }
#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

Solver::Solver(Instance &p, int N, int K) : pareto(p), matrix(boost::extents[N][K]) {}

vector<int> Solver::getSolution(){
    return solution;
}

void Solver::fillArray(){
    int cpt = 0;
    float print = 0.0;
    for(index i = 0; i < 6; i++){
        cout << (i-1) << "\n";
        for(index j = 0; j < 2; j++){
            matrix[i][j] = (float)(cpt++);
            print = matrix[i][j];
            cout << "matrix[i][j] = " << print << "\n";
        }
    }
}

void Solver::displayMatrix(){
    for(index i = 0; i < matrix.size(); i++){
        for (index j = 0; j < matrix.shape()[1]; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

float Solver::min_DP(int i, int k){
        float min = matrix[0][k-1] + pareto.cost_means(1, i);
        for (index j = 2; j < i; j++){
            float tmp = matrix[j-1][k-1] + pareto.cost_means((int)j, i);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
}

void Solver::DP(int N, int K){
        for (index i = 0; i < N; i++){
            matrix[i][1] = pareto.cost_means(1, (int)i);
            for (index k = 1; k < K; k++){
                matrix[i][k] = min_DP((int)i, (int)k);
            }
        }
}

void Solver::backtrack(int N, int K){
    int i = N-1;
    float tmp = 0;
    for (index k = K-1; k > 0; k--){
        for (index j = 0; j < i; j++){
            if (j > 0){ 
                tmp = matrix[j-1][k-1] + pareto.cost_means((int)j, i);
            }
            cout << "Comparaison " << tmp << " == " << matrix[i][k];
            if(matrix[i][k] == tmp){
                solution.push_back(i);
                i = (int)j-1;
            }
        }
    }
}
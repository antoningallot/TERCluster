#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

Solver::Solver(Instance &p, int N, int K) : pareto(p), matrix(boost::extents[N+1][K]) {}

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

void Solver::initMatrix(){
    for(index i = 0; i < matrix.shape()[1]; i++){
        matrix[0][i] = -1;
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
        float tmp;
        float min = matrix[1][k-1] + pareto.cost_median(0, i-1);
        for (index j = 2; j <= i; j++){
            tmp = matrix[j-1][k-1] + pareto.cost_median((int)j-1, i-1);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
}

void Solver::DP(int N, int K){
        for (index i = 1; i <= N; i++){
            matrix[i][0] = pareto.cost_median(0, (int)i-1);
            for (index k = 1; k < K; k++){
                matrix[i][k] = min_DP((int)i, (int)k);
            }
        }
}

void Solver::backtrack(int N, int K){
    int i = N;
    float tmp = 0;
    for (index k = K-1; k > 0; k--){
        for (index j = 1; j <= i; j++){
            tmp = matrix[j-1][k-1] + pareto.cost_median((int)j-1, i-1);
            cout << "Comparaison " << j << " " << matrix[j-1][k-1] << " + "
            << pareto.cost_median((int)j-1, i-1) << " == " << matrix[i][k] << "\n";
            if(matrix[i][k] == tmp){
                cout << i << "\n";
                solution.push_back(j-1);
                i = (int)j-1;
            }
        }
        cout << "\n";
    }
}
#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

// Constructeur de la classe Solver
Solver::Solver(int n, int k, string filename){
    Solver_parent(n, k, filename);
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    DP_matrix = new array_type(boost::extents[N+1][K]); 
    initMatrix();
    solution = new vector<int>();
}

/*** FONCTIONS D'INITIALISATION POUR LE CONSTRUCTEUR ***/

void Solver::initMatrix(){
    for(index i = 0; i < DP_matrix->shape()[1]; i++){
        (*DP_matrix)[0][i] = -1;
    }
}

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/
void Solver::displayMatrix(){
    for(index i = 0; i < DP_matrix->size(); i++){
        for (index j = 0; j < DP_matrix->shape()[1]; j++){
            cout << (*DP_matrix)[i][j] << " ";
        }
        cout << "\n";
    }
}

/*** FONCTIONS DE LA PROGRAMMATION DYNAMIQUE ***/

float Solver::min_DP(int i, int k){
        float tmp;
        float min = (*DP_matrix)[1][k-1] + pareto->cost_median(0, i-1);
        for (index j = 2; j <= i; j++){
            tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
}

void Solver::solve(){
    for (index i = 1; i <= N; i++){
        (*DP_matrix)[i][0] = pareto->cost_median(0, (int)i-1);
        for (index k = 1; k < K; k++){
            (*DP_matrix)[i][k] = min_DP((int)i, (int)k);
        }
    }
}

void Solver::backtrack(){
    int i = N;
    float tmp = 0;
    for (index k = K-1; k > 0; k--){
        for (index j = 1; j <= i; j++){
            tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
            if((*DP_matrix)[i][k] == tmp){
                solution->push_back(j-1);
                i = (int)j-1;
            }
        }
    }
}
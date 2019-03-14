#include <iostream>
#include <vector>
#include <cmath>
#include "Solver.h"

using namespace std;

// Constructeur de la classe Solver 
Solver::Solver(int n, int k, string filename) {
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    matrix = new array_type(boost::extents[N+1][K]); 
    initMatrix();
    solution = new vector<int>();
}

/*** FONCTIONS D'INITIALISATION POUR LE CONSTRUCTEUR ***/

void Solver::initMatrix(){
    for(index i = 0; i < matrix->shape()[1]; i++){
        (*matrix)[0][i] = -1;
    }
}

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/

vector<int> Solver::getSolution(){
    return *solution;
}

void Solver::displayPareto(){
    pareto->display();
}

void Solver::displaySolution(){
    for(int i = 0; i < solution->size(); i++){
        cout << (*solution)[i] << " ";
    }
    cout << "\n";
}

void Solver::displayMatrix(){
    for(index i = 0; i < matrix->size(); i++){
        for (index j = 0; j < matrix->shape()[1]; j++){
            cout << (*matrix)[i][j] << " ";
        }
        cout << "\n";
    }
}

/*** FONCTIONS DE LA PROGRAMMATION DYNAMIQUE ***/

float Solver::min_DP(int i, int k){
        float tmp;
        float min = (*matrix)[1][k-1] + pareto->cost_median(0, i-1);
        for (index j = 2; j <= i; j++){
            tmp = (*matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
            if(tmp < min){
                min = tmp;
            }
        }
        return min;
}

void Solver::DP(){
    for (index i = 1; i <= N; i++){
        (*matrix)[i][0] = pareto->cost_median(0, (int)i-1);
        for (index k = 1; k < K; k++){
            (*matrix)[i][k] = min_DP((int)i, (int)k);
        }
    }
}

void Solver::backtrack(){
    int i = N;
    float tmp = 0;
    for (index k = K-1; k > 0; k--){
        for (index j = 1; j <= i; j++){
            tmp = (*matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
            if((*matrix)[i][k] == tmp){
                solution->push_back(j-1);
                i = (int)j-1;
            }
        }
    }
}
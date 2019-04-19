#include <iostream>
#include <fstream>
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
    // cout << "N : " << N << " K : " << K << "\n";
    DP_matrix = new array_type(boost::extents[N+1][K]);
    initMatrix();
    solution = new vector<pair<int, int> >();
}

/*** FONCTIONS D'INITIALISATION POUR LE CONSTRUCTEUR ***/

void Solver::initMatrix(){
    for(index i = 0; i < (int)DP_matrix->shape()[1]; i++){
        (*DP_matrix)[0][i] = -1;
    }
}

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/
void Solver::displayMatrix(){
    for(index i = 0; i < (int)DP_matrix->size(); i++){
        for (index j = 0; j < (int)DP_matrix->shape()[1]; j++){
            cout << (*DP_matrix)[i][j] << " ";
        }
        cout << "\n";
    }
}

void Solver::write_result(string filename){
    ofstream file(filename.c_str());
    if(file.is_open()){
        for(int i = (int)solution->size()-1; i >= 0; i--){
            file << (*solution)[i].second << " " << (*solution)[i].first << "\n";
        }
        file.close();
    }
}

float Solver::get_result(){
    return (*DP_matrix)[N][K-1];
}

/*** FONCTIONS DE LA PROGRAMMATION DYNAMIQUE ***/

float Solver::min_DP(int i, int k, int methode){
        float tmp;
        float min = 0;
        switch (methode) 
        {
            case 1:
            min = (*DP_matrix)[1][k-1] + pareto->cost_median(0, i-1);
            for (index j = 2; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            break;
            // return min_median;

            case 2:
            min = (*DP_matrix)[1][k-1] + pareto->cost_means(0, i-1);
            for (index j = 2; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_means((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            break;
            // return min_means;

            case 3:
            min = (*DP_matrix)[1][k-1] + pareto->cost_medoids(0, i-1);
            for (index j = 2; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_medoids((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            break;
            // return min_medoids;

            case 4:
            min = (*DP_matrix)[1][k-1] + pareto->cost_dcenter(0, i-1);
            for (index j = 2; j <= i; j++){
                // cout << "Cost : " << j << " " << i << " " << pareto->cost_dcenter((int)j-1, i-1) << endl;
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_dcenter((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            //cout << endl;
            break;
            // return min_dcenter;

            case 5:
            min = (*DP_matrix)[1][k-1] + pareto->cost_dcenterv2(0, i-1);
            for (index j = 2; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_dcenterv2((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            break;
            // return min_dcenterv2;

            case 6:
            min = (*DP_matrix)[1][k-1] + pareto->cost_ccenter(0, i-1);
            for (index j = 2; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_ccenter((int)j-1, i-1);
                if(tmp < min){
                    min = tmp;
                }
            }
            break;
            // return min_ccenter;
        }
        return min;
}

void Solver::solve(int methode){
    switch(methode)
    {
        case 1:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_median(0, (int)i-1);
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;

        case 2:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_means(0, (int)i-1);
            //cout << (*DP_matrix)[i][0] << endl;
            //cout << endl;
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;
        case 3:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_medoids(0, (int)i-1);
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;

        case 4:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_dcenter(0, (int)i-1);
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;

        case 5:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_dcenterv2(0, (int)i-1);
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;
        case 6:
        for (index i = 1; i <= N; i++){
            (*DP_matrix)[i][0] = pareto->cost_ccenter(0, (int)i-1);
            for (index k = 1; k < K; k++){
                (*DP_matrix)[i][k] = min_DP((int)i, (int)k, methode);
            }
        }
        break;
    }
}

void Solver::backtrack(int methode){
    int i = N;
    float tmp = 0;
    pair<int, int> pair;
    switch (methode)
    {
        case 1:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_median((int)j-1, i-1);
                if((*DP_matrix)[i][k] == tmp){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

        case 2:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_means((int)j-1, i-1);
                if((*DP_matrix)[i][k] == tmp){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

        case 3:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_medoids((int)j-1, i-1);
                if((*DP_matrix)[i][k] == tmp){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

        case 4:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                // tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_dcenter((int)j-1, i-1);
                if((*DP_matrix)[i][k] == (*DP_matrix)[j-1][k-1] + pareto->cost_dcenter((int)j-1, i-1)){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

        case 5:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_dcenterv2((int)j-1, i-1);
                if((*DP_matrix)[i][k] == tmp){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

        case 6:
        for (index k = K-1; k > 0; k--){
            for (index j = 1; j <= i; j++){
                tmp = (*DP_matrix)[j-1][k-1] + pareto->cost_ccenter((int)j-1, i-1);
                if((*DP_matrix)[i][k] == tmp){
                    pair = make_pair(i-1, j-1);
                    solution->push_back(pair);
                    i = (int)j-1;
                }
            }
        }
        pair = make_pair(i-1, 0);
        solution->push_back(pair);
        break;

    }
}
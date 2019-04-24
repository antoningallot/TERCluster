#include <iostream>
#include <vector>
#include <fstream>
#include "Solver_parent.hpp"

using namespace std;

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/

Solver_parent::Solver_parent(){}

Solver_parent::Solver_parent(int n, int k, string filename) {
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    solution = new vector<pair<int, int> >();
}

vector<pair<int, int> > Solver_parent::getSolution(){
    return *solution;
}

void Solver_parent::displayPareto(){
    pareto->display();
}

void Solver_parent::displaySolution(){
    for(int i = 0; i < (int)solution->size(); i++){
        cout << (*solution)[i].first << " " << (*solution)[i].second << "\n";
    }
    // cout << "\n";
}

int Solver_parent::getSize(){
    return pareto->getSize();
}

void Solver_parent::solve(int methode){ };

void Solver_parent::write_result(string filename){
    ofstream file(filename.c_str());
    if(file.is_open()){
        for(int i = solution->size()-1; i >= 0; i--){
            file << (*solution)[i].first << " " << (*solution)[i].second << "\n";
        }
        file.close();
    }
}
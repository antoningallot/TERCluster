#include <iostream>
#include <vector>
#include "Solver_parent.hpp"

using namespace std;

/*** FONCTIONS AUXILIAIRES POUR LA MANIPULATION ***/

Solver_parent::Solver_parent(){}

Solver_parent::Solver_parent(int n, int k, string filename) {
    pareto = new Instance(n, filename);
    N = pareto->getSize();
    K = k;
    solution = new vector<int>();
}

vector<int> Solver_parent::getSolution(){
    return *solution;
}

void Solver_parent::displayPareto(){
    pareto->display();
}

void Solver_parent::displaySolution(){
    for(int i = 0; i < solution->size(); i++){
        cout << (*solution)[i] << " ";
    }
    cout << "\n";
}

void Solver_parent::solve(){ };
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Solver.h"

using namespace std;

vector<Point> parsing (int n, string filename) {
    cout << "Test fonc\n";
    vector<Point> res (0);
    float x, y;
    int taille, dimension, cpt = 0;
    ifstream file (filename);
    if (file.is_open()){
        file >> taille;
        file >> dimension;
    }
    cout << "Taille = " << taille << " Dimension = " << dimension << "\n";
    if (taille != 0) {
        taille = min(n, taille);
    }
    while (cpt < taille){
        if(file.is_open()){
            file >> x;
            file >> y;
            Point p(x, y);
            res.push_back(p);
            cpt++;
        }
        
    }
    file.close();
    return res;
}

void display(vector<int> tab) {
    unsigned int i;
    for(i = 0; i < tab.size()-1; i++){
        cout << tab[i] << "\n";
    }
}

int main (int argc, char *argv[]) {
    
    vector<Point> v = parsing(6, "data.txt");
    Instance p(v);
    Solver s(p, 6, 2);
    s.DP(6, 2);
    s.backtrack(6, 2);
    display(s.getSolution());

    return 0;
}

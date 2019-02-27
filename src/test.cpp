#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Solver.h"

using namespace std;

vector<Point> parsing (int n, string filename) {
    vector<Point> res (0);
    float x, y;
    int taille, dimension, cpt = 0;
    ifstream file (filename);
    if (file.is_open()){
        file >> taille;
        file >> dimension;
    }
    //cout << "Taille = " << taille << " Dimension = " << dimension << "\n";
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
    cout << "Partition de la solution : \n";
    for(i = 0; i < tab.size(); i++){
        cout << tab[i] << "\n";
    }
}

int main (int argc, char *argv[]) {
    //blabla
    vector<Point> v = parsing(7, "data.txt");
    Instance p(v);
    p.initMatrix();
    p.displayMatrix();
    Solver s(p, 7, 3);
    //s.fillArray();
    s.DP(7, 3);
    s.backtrack(7, 3);
    s.displayMatrix();
    display(s.getSolution());

    return 0;
}

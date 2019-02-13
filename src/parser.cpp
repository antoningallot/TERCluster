#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Point.h"
using namespace std;

// Créer une instance dans laquelle tout stocker
// vector<point> + taille vector + taille données en attributs privés de cette instance
// matrices et données utilisées dans calculs intermédiaires en attributs privés aussi
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

void display(vector<Point> tab) {
    unsigned int i;
    for(i = 0; i < tab.size()-1; i++){
        tab[i].display();
    }
}

int main (int argc, char *argv[]) {
    vector<Point> tab (20);
    cout << "Test main\n";
    tab = parsing(20, "data.txt");
    cout << "vector construit\n";
    //vector<Point> tab (10, Point());
    display(tab);
    cout << tab.size();
    
    return 0;
}
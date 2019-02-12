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
    cout << "Test fonc";
    vector<Point> res (n);
    float x, y;
    int taille, dimension, cpt = 0;
    //int cpt = 0;
    ifstream file (filename);
    if (file.is_open()){
        file >> taille;
        file >> dimension;
    }
    cout << "Taille = " << taille << " Dimension = " << dimension;
    if (taille != 0) {
        taille = min(n, taille);
    }
    while (cpt <= taille){
        if(file.is_open()){
            file >> x;
            file >> y;
            Point p(x, y);
            res.push_back(p);
            taille++;
            cpt++;
        }
        
    }
    file.close();
    return res;
}

void display(vector<Point> tab) {
    unsigned int i;
    for(i = 0; i < tab.size(); i++){
        tab[i].display();
    }
}

int main (int argc, char *argv[]) {
    vector<Point> tab (20);
    cout << "Test main\n";
    tab = parsing(20, "data.txt");
    //vector<Point> tab (10, Point());
    display(tab);
    
    return 0;
}
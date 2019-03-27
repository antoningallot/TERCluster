#include <iostream>
#include <cmath>
#include <fstream>
#include <math.h>
#include <bits/stdc++.h>
#include "Instance.h"

using namespace std;

Instance::Instance(){}

//Constructeur de la classe Instance
Instance::Instance(int n, string filename) { 
    pareto = new vector<Point>(parsing(n, filename));
    N = pareto->size();
    // cout << "N : " << N << "\n";
    matrix = new array_type(boost::extents[N][N]);
    initMatrix();
}

/*** FONCTIONS D'INITIALISATION POUR LE CONSTRUCTEUR D'INSTANCE ***/
vector<Point> Instance::parsing (int n, string filename) {
    vector<Point> res (0);
    float x, y;
    int taille, dimension, cpt = 0;
    ifstream file (filename.c_str());
    if (file.is_open()){
        file >> taille;
        file >> dimension;
    }
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

void Instance::initMatrix(){
    for(idx i=0; i<N-1; i++){
        (*matrix)[i][i+1] = getPoint(i).distance(getPoint(i+1));
    }
    for(idx i=0; i<N-1; i++){
        for (idx j=i+2; j<N; j++){
            (*matrix)[i][j]= (*matrix)[i][j-1]+(*matrix)[j-1][j];
        }
    }
}


/*** FONCTIONS POUR LA MANIPULATION EXTERIEURE (PAR D'AUTRES CLASSES)***/

void Instance::display() {
    for(int i = 0; i < N; i++){
        (*pareto)[i].display();
    }
}

Point Instance::getPoint(int i){ return (*pareto)[i];}

int Instance::getSize(){ return pareto->size(); }

/*** FONCTIONS DE CALCUL DES COUTS EN UTILISANT LA MATRICE INITIALISE ***/ 

float Instance::cost_means_matrix(int i, int iprime){
    float sum = 0;
    int cpt = 0;
    Point p(0,0);
    for(int j= i; j <= iprime; j++){
        p.addPoint(getPoint(j));
    }
    p.multInt(1/(iprime-i+1));
    for(int I = i; I <= iprime; I++){
        sum+= getPoint(I).distance(p);
    }
    return sum;
}

float Instance::cost_medoids_matrix(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            if(I<j){sum += (*matrix)[I][j];}
            if(j<I){sum += (*matrix)[j][I];}
        }
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::cost_median_matrix(int i, int iprime){
    if (i == iprime) { return 0; }
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            if(I<j){sum += (*matrix)[I][j];}
            if(j<I){sum += (*matrix)[j][I];}
        }
        //sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::cost_dcenter_matrix(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int j=i; j <= iprime; j++){
        float sum = 0;
        if((*matrix)[i][j]>(*matrix)[j][iprime]){
            sum += (*matrix)[i][j];
        }
        else {
            sum += (*matrix)[j][iprime];
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::cost_dcenterv2_matrix(int i, int iprime){
    float min = FLT_MAX;
    int j = i;
    while(j< iprime){
        float sum = 0;
        if((*matrix)[i][j]>(*matrix)[j][iprime]){
            sum += (*matrix)[i][j];
        }
        else {
            sum += (*matrix)[j][iprime];
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
            i += 1;
        }
        else{
            return min;
        }
    }
    return min;
}

float Instance::cost_ccenter_matrix(int i, int iprime){
    float sum = (*matrix)[i][iprime];
    return 0.5*sqrt(sum);
}

/*** FONCTIONS DE CALCUL DES COUTS EN RECALCULANT A CHAQUE APPEL ***/

float Instance::cost_medoids(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            sum += getPoint(I).distance(getPoint(j));
        }
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::cost_median(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            sum += getPoint(I).distance(getPoint(j));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}
    
float Instance::cost_dcenter(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int j=i; j <= iprime; j++){
        float sum = 0;
        if(getPoint(j).distance(getPoint(i))>getPoint(j).distance(getPoint(iprime))){
            sum = getPoint(j).distance(getPoint(i));
        }
        else {
            sum = getPoint(j).distance(getPoint(iprime));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::cost_dcenterv2(int i, int iprime){
    float min = FLT_MAX;
    int j = i;
    while(j< iprime){
        float sum = 0;
        if(getPoint(j).distance(getPoint(i))>getPoint(j).distance(getPoint(iprime))){
            sum = getPoint(j).distance(getPoint(i));
        }
        else {
            sum = getPoint(j).distance(getPoint(iprime));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
            i += 1;
        }
        else{
            return min;
        }
    }
    return min;
}

float Instance::cost_ccenter(int i, int iprime){
    float sum = getPoint(i).distance(getPoint(iprime));
    return 0.5*sqrt(sum);
}
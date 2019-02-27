#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include "Instance.h"

using namespace std;

Instance::Instance(){}

Instance::Instance(std::vector<Point> v): pareto(v), N(v.size){ 
    for(int i=0; i<N; i++){
        matrix[i][i+1] = this->getPoint(i).distance(this->getPoint(i+1));
    }
    for(int i=0; i<N; i++){
        for (int j=i+2; j<N; j++){
            matrix[i][j]= matrix[i][j-1]+matrix[j-1][j];
        }
    }
}

Point Instance::getPoint(int i){ return pareto[i];}

//Calcul avec matrice (à faire)

float Instance::cost_means(int i, int iprime){
    float sum = 0;
    int cpt = 0;
    Point p(0,0);
    for(int j= i; j <= iprime; j++){
        p.addPoint(getPoint(j));
    }
    p.multInt(1/(iprime-i+1));
    for(int I = i; I <= iprime; I++){
        sum+= this->getPoint(I).distance(p);
    }
    return sum;
}

float Instance::cost_medoids(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            if(I<j){sum += matrix[I][j];}
            if(j<I){sum += matrix[j][I];}
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
            if(I<j){sum += matrix[I][j];}
            if(j<I){sum += matrix[j][I];}
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
        if(matrix[i][j]>matrix[j][iprime]){
            sum += matrix[i][j];
        }
        else {
            sum += matrix[j][iprime];
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
        if(matrix[i][j]>matrix[j][iprime]){
            sum += matrix[i][j];
        }
        else {
            sum += matrix[j][iprime];
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
    float sum = matrix[i][iprime];
    return 0.5*sqrt(sum);
}

//Calcul sans distance

float Instance::old_cost_medoids(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            sum += this->getPoint(I).distance(this->getPoint(j));
        }
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::old_cost_median(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int I = i; I <= iprime; I++){
        float sum = 0;
        for (int j = i; j <= iprime; j++){
            sum += this->getPoint(I).distance(this->getPoint(j));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}
    
float Instance::old_cost_dcenter(int i, int iprime){
    float min = FLT_MAX;
    if(i == iprime) {min = 0;}
    for(int j=i; j <= iprime; j++){
        float sum = 0;
        if(this->getPoint(j).distance(this->getPoint(i))>this->getPoint(j).distance(this->getPoint(iprime))){
            sum = this->getPoint(j).distance(this->getPoint(i));
        }
        else {
            sum = this->getPoint(j).distance(this->getPoint(iprime));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
    return min;
}

float Instance::old_cost_dcenterv2(int i, int iprime){
    float min = FLT_MAX;
    int j = i;
    while(j< iprime){
        float sum = 0;
        if(this->getPoint(j).distance(this->getPoint(i))>this->getPoint(j).distance(this->getPoint(iprime))){
            sum = this->getPoint(j).distance(this->getPoint(i));
        }
        else {
            sum = this->getPoint(j).distance(this->getPoint(iprime));
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

float Instance::old_cost_ccenter(int i, int iprime){
    float sum = this->getPoint(i).distance(this->getPoint(iprime));
    return 0.5*sqrt(sum);
}
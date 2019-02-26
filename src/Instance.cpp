#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include "Instance.h"

using namespace std;

Instance::Instance(){}

Instance::Instance(std::vector<Point> v): pareto(v){ }

Point Instance::getPoint(int i){ return pareto[i];}

float Instance::cost_medoids(int i, int iprime){
    float min = FLT_MAX;
    for(int I = i; I < iprime; I++){
        float sum = 0;
        for (int j = i; j < iprime; j++){
            sum += this->getPoint(I).distance(this->getPoint(j));
        }
        if (sum < min){
            min = sum;
        }
    }
    min = (1/(iprime-i+1))* min * min;
    return min;
}

float Instance::cost_means(int i, int iprime){
    float sum = 0;
    int cpt = 0;
    Point p;
    for(int j= i; j < iprime; j++){
        p.addPoint(getPoint(j));
    }
    p.multInt(1/(iprime-i+1));
    for(int I = i; I < iprime; I++){
        sum+= this->getPoint(I).distance(p);
    }
    sum = (1/(iprime-i+1))* sum * sum;
    return sum;
}

float Instance::cost_median(int i, int iprime){
    float min = FLT_MAX;
    for(int I = i; I < iprime; I++){
        float sum = 0;
        for (int j = i; j < iprime; j++){
            sum += this->getPoint(I).distance(this->getPoint(j));
        }
        sum = sqrt(sum);
        if (sum < min){
            min = sum;
        }
    }
}
    
float Instance::cost_dcenter(int i, int iprime){
    float min = FLT_MAX;
    for(int j=i; j < iprime; j++){
        float sum = 0;
        if(this->getPoint(j).distance(this->getPoint(i))>this->getPoint(j).distance(this->getPoint(iprime))){
            sum = this->getPoint(j).distance(this->getPoint(i));
        }
        else {
            sum = this->getPoint(j).distance(this->getPoint(iprime));
        }
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
        if(this->getPoint(j).distance(this->getPoint(i))>this->getPoint(j).distance(this->getPoint(iprime))){
            sum = this->getPoint(j).distance(this->getPoint(i));
        }
        else {
            sum = this->getPoint(j).distance(this->getPoint(iprime));
        }
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
    return 0.5*this->getPoint(i).distance(this->getPoint(iprime));
}
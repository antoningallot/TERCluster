#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"
#include "Instance.h"

using namespace std;

Instance::Instance(){}

    Instance::Instance(std::vector<Point> v): pareto(v){ }

    Point Instance::getPoint(int i){ return this->pareto[i]}

    float cost_medoids(int i, int iprime){
        float min = FLOAT_MAX;
        for(int I = i; I < iprime; I++){
            float sum = 0;
            for (int j = i; j < iprime; j++){
                sum += this->getPoint(I).distance(this->getPoint(j));
            }
            if (sum < min){
                min = sum;
            }
        }
        return min;
    }

    float cost_means(int i, int iprime){
        float sum = 0;
        int cpt = 0;
        float x = 0 ;
        float y = 0;
        for(int j= i; j < iprime; I++){
                x += this->getPoint(j).getX();
                y += this->getPoint(j).getY();
                cpt += 1;
        }
        Point p(1/(iprime-i+1)*(x/cpt),1/(iprime-i+1)*(y/cpt));
        for(int I = i; I < iprime; I++){
            sum+= this->getPoint(I).distance(p);
        }
        return sum;
    }

    float cost_median(int i, int iprime){
        float min = FLOAT_MAX;
        for(int I = i; I < iprime; I++){
            float sum = 0;
            for (int j = i; j < iprime; j++){
                float sum += this->getPoint(I).distance(this->getPoint(j));
            }
            sum = sqrt(sum);
            if (sum < min){
                min = sum;
            }
        }
    }
    
    float cost_dcenter(int i, int iprime){
        
    }

    float cost_ccenter(int i, int iprime){
        return 0.5*this->getPoint(i).distance(this->getPoint(iprime));
    }
};

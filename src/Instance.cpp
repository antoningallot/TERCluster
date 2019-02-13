#include <iostream>
#include <vector>
#include <cmath>
#include "Point.h"

using namespace std;

class Instance {

    Instance::Instance(){
        
    }

    float cost_median(int i, int iprime){
        float min = 0;
        for(int I = i; I < iprime; I++){
            float sum = 0;
            for (int j = i; j < iprime; j++){
                float sum += dist(this.get(j), this.get(I));
            }
            if (sum < min){
                min = sum;
            }
        }
        return min;
    }

    
};
#include "Point.h"
#include <iostream>
#include <cmath>
using namespace std;
   
Point::Point() : x(0), y(0) { }
Point::Point(float abs, float ord) : x(abs), y(ord) { }

void Point::display(){
    cout << "x:" << x << ", y:" << y << "\n";
}

float Point::distance(Point i){
    return sqrt(pow((x-i.x),2.0)+pow((y-i.y),2.0));
}

void Point::addPoint(Point i){
    x = x + i.x;
    y = y + i.y;
}

void Point::multInt(int val){
    x = x * val;
    y = y * val;
}

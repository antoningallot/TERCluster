#include "Point.h"
#include <iostream>
#include <cmath>
using namespace std;
   
Point::Point() : x(0), y(0) { }
Point::Point(float abs, float ord) : x(abs), y(ord) { }

void Point::display(){
    cout << "x:" << x << ", y:" << y << "\n";
}

float Point::getX(){
    return this.x;
}

float Point::getY(){
    return this.y;
}
float Point::distance(Point i){
    return pow((this.x-i.getX()),2.0)+pow((this.y-i.getY()),2.0)
}
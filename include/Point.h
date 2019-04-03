#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
    private:
    float x;
    float y;

    public:
    Point();
    Point(float abs, float ord);
    void display();
    float distance(Point i);
    void addPoint(Point i);
    void multInt(float val);
};

#endif
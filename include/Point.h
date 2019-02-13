#include <iostream>

class Point {
    
    private:

    float x;
    float y;

    public:
    
    Point();
    Point(float abs, float ord);
    void display();
    float getX();
    float getY();
    float distance(Point i);
};
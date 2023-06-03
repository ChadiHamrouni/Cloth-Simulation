#pragma once
#include "point.h"

class Stick {

public:
    float Length;
    Point& P0;
    Point& P1;

    Stick(Point* p0, Point* p1, float length);
   
    void Update(float dt);

    void Render(sf::RenderWindow& window);

};
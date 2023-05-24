#pragma once
#include "point.h"

class Stick {

public:
    float Length;
    Point& P0;
    Point& P1;
    Stick(Point* p0, Point* p1, float length);
   

    void update(float dt);

    void render(sf::RenderWindow& window);

  //  float distance(Point* p0, Point* p1);
  
   
};
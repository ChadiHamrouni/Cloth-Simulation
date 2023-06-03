#pragma once
#include <SFML/Graphics.hpp>

class Point {

public:
    float x = 0, y = 0, vel_x = 0, vel_y = 0, mass = 0, old_x = 0, old_y = 0;
    bool pinned = false;
    sf::CircleShape shape;

    Point(float x, float y, float mass, bool pinned);
    Point();

    void Update_Verlet(float dt);

    void Render(sf::RenderWindow& window);

};
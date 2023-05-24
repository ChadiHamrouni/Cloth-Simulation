#pragma once
#include <SFML/Graphics.hpp>

class Point {

public:
    float x = 0, y = 0, vel_x = 0, vel_y = 0, mass = 0, old_x = 0, old_y = 0;
    bool pinned = false;
    sf::CircleShape shape;


    Point(float x, float y, float mass, bool pinned);
    Point();

    void update_verlet(float dt);

    void update(float dt);

    void render(sf::RenderWindow& window);

    void constraint(int Width, int Height);
};
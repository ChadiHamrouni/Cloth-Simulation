#pragma once
#include <SFML/Graphics.hpp>

class Point {

public:
    float x = 0, y = 0;
    float vel_x = 0, vel_y = 0;
    float old_x = 0, old_y = 0;
    float mass = 0;
    bool pinned = false;

    sf::CircleShape shape;

    Point(float x, float y, float mass, bool pinned);

    Point();

    void UpdateVerlet(float dt);

    void Render(sf::RenderWindow& window);

    static void SetInitialPosition(const int num_objects, std::vector<Point>& points);

    static void SetAnchorPoints(std::vector<Point>& points);

};

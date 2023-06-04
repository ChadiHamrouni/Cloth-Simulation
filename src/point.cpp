#include "../header/point.h"

float force_x = 150;
float force_y = 100;

Point::Point(float x, float y, float mass, bool pinned) {

    this->x = x;
    this->y = y;
    this->mass = mass;
    this->pinned = pinned;
    this->old_x = x;
    this->old_y = y;

    shape.setFillColor(sf::Color::White);
    shape.setRadius(5.f);
    shape.setPosition(x, y);
}

Point::Point() {}

void Point::UpdateVerlet(float dt) {

    if (!this->pinned) {

        vel_x = this->x - this->old_x;
        vel_y = this->y - this->old_y;

        this->old_x = this->x;
        this->old_y = this->y;

        float acc_x = force_x / this->mass;
        float acc_y = force_y / this->mass;

        this->x += vel_x + acc_x * dt * dt;
        this->y += vel_y + acc_y * dt * dt;

        shape.setPosition(x, y);
    }
}

void Point::Render(sf::RenderWindow& window) { window.draw(shape);}

void Point::SetInitialPosition(const int num_objects, std::vector<Point>& points) {

    float xini = 450;
    for (int i = 0; i < num_objects; i++) {
        float yini = 200;
        for (int j = 0; j < num_objects; j++) {
            Point p = Point(xini, yini, 1, false);
            points.push_back(p);
            yini = yini + 10;
        }
        xini = xini + 10;
    }
}

void Point::SetAnchorPoints(std::vector<Point>& points) {
    
    float initialx = 450;
    float initialy = 200;

    for (int i = 0; i <= 35; i = i + 5) {
        points[i] = Point(initialx, initialy, 1.0, true);
        initialx = initialx + 50;

    }
}

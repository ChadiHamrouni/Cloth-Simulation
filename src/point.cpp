#include "../header/point.h"

float force_x = 0;
float force_y = 30;

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

void Point::Update_Verlet(float dt) {

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

void Point::Render(sf::RenderWindow& window) {
    window.draw(shape);
}


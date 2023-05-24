#include "../header/point.h"

float force_x = 300;
float force_y = 300;

Point::Point(float x, float y, float mass, bool pinned) {

    this->x = x;
    this->y = y;
    this->mass = mass;
    this->pinned = pinned;
    this->old_x = x;
    this->old_y = y;

    shape.setFillColor(sf::Color::White);
    shape.setRadius(15.f);
    shape.setPosition(x, y);
}

Point::Point() {}

void Point::update_verlet(float dt) {

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

void Point::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void Point::constraint(int Width, int Height) {

    vel_x = this->x - this->old_x;
    vel_y = this->y - this->old_y;

    if (this->x < 0) {
        this->x = 0;
        this->old_x = this->x + vel_x;
    }
    else if (this->x > Width - 31) {
        this->x = Width - 31;
        this->old_x = this->x + vel_x;
    }
    
    //if (this->y < 0) {
    //    this->y = 0;
    //    this->old_y = this->y + vel_y;
    //}

    else if (this->y > Height - 50) {
        this->y = Height - 50;
        this->old_y = this->y + vel_y;
    }
}

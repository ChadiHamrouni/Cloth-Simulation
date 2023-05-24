#include "../header/stick.h"
#include "../header/point.h"

Stick::Stick(Point* p0, Point* p1, float length) : P0(*p0), P1(*p1), Length(length) {}


void Stick::update(float dt) {

    float dx = this->P1.x - this->P0.x;
    float dy = this->P1.y - this->P0.y;

    float dist = std::sqrt(dx * dx + dy * dy);
    float diff = this->Length - dist;
    float percent = (diff / dist) / 2;

    float offset_x = dx * percent;
    float offset_y = dy * percent;

    if (!this->P0.pinned) {
        this->P0.x -= offset_x;
        this->P0.y -= offset_y;
    }

    if (!this->P1.pinned) {
        this->P1.x += offset_x;
        this->P1.y += offset_y;
    }
}

void Stick::render(sf::RenderWindow& window) {

    sf::VertexArray stick(sf::LineStrip, 2);
    stick[0].position = P0.shape.getPosition() + sf::Vector2f(15.f, 15.f);
    stick[1].position = P1.shape.getPosition() + sf::Vector2f(15.f, 15.f);

    window.draw(stick);
}

//float Stick::distance(Point* p0, Point* p1) {
//
//    float dx = p1.x - p0.x;
//    float dy = p1.y - p0.y;
//    return std::sqrt(dx * dx + dy * dy);
//}
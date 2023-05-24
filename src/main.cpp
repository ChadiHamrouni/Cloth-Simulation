#include <SFML/Graphics.hpp>
#include "../header/point.h"
#include "../header/stick.h"

int Width = 1280;
int Height = 720;

const int NumRows = 14;
const int NumColumns = 25;
const float CellSize = 51.1f;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Verlet Integration", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Clock clock;

    sf::Color red(235, 69, 95);
    sf::Color blue(0, 255, 202);
   
    sf::RectangleShape floor;
    sf::RectangleShape right;
    sf::RectangleShape left;

    sf::Color Red(235, 69, 95);
    sf::Color wh(0, 0, 0);
    sf::Color wa(0, 255, 202);
    sf::Color green(13, 84, 93);

    sf::VertexArray grid(sf::Lines);  // VertexArray to store the grid lines

    // Create the vertical lines of the grid
    for (int col = 0; col <= NumColumns; ++col) {
        float x = col * CellSize;
        grid.append(sf::Vertex(sf::Vector2f(x, 0.f), green));
        grid.append(sf::Vertex(sf::Vector2f(x, NumRows * CellSize), green));
    }

    // Create the horizontal lines of the grid
    for (int row = 0; row <= NumRows; ++row) {
        float y = row * CellSize;
        grid.append(sf::Vertex(sf::Vector2f(0.f, y), green));
        grid.append(sf::Vertex(sf::Vector2f(NumColumns * CellSize, y), green));
    }

    // Setting up the borders
    floor.setSize(sf::Vector2f(1280, 20.f));
    floor.setFillColor(sf::Color::Black);
    floor.setPosition(0, 720);
    floor.setOutlineThickness(3);
    floor.setOutlineColor(blue);

    right.setSize(sf::Vector2f(1280, 600.f)); // Set size of the line
    right.setFillColor(sf::Color::Black);
    right.setPosition(1880, 0);
    right.setRotation(90);
    right.setOutlineThickness(3);
    right.setOutlineColor(blue);

    left.setSize(sf::Vector2f(0, 720.f)); // Set size of the line
    left.setFillColor(sf::Color::Black);
    left.setPosition(0, 0);
    left.setOutlineThickness(3);
    left.setOutlineColor(blue);

    // Creating the points & Sticks (This solution isn't scalable, in the future structure creation will be dynamic)
    const int NUM_OBJECTS = 13;
    Point* points[NUM_OBJECTS];
    Point* p2[NUM_OBJECTS];
    Point* p3[NUM_OBJECTS];
    Point* p4[NUM_OBJECTS];
    Point* p5[NUM_OBJECTS];
    Point* p6[NUM_OBJECTS];
    Point* p7[NUM_OBJECTS];
    Point* p8[NUM_OBJECTS];
    Point* p9[NUM_OBJECTS];

    float yy = 100.0f; 
    float xx = 100.0f;
    float yIncrement = 30.0f;
  
    for (int i = 0; i < NUM_OBJECTS; i++) {

        points[0] = new Point(500, 10, 1.0, true);
        p2[0] = new Point(540, 10, 1.0, true);
        p3[0] = new Point(580, 10, 1.0, true);
        p4[0] = new Point(620, 10, 1.0, true);
        p5[0] = new Point(660, 10, 1.0, true);
        p6[0] = new Point(700, 10, 1.0, true);
        p7[0] = new Point(740, 10, 1.0, true);
        p8[0] = new Point(780, 10, 1.0, true);
        p9[0] = new Point(820, 10, 1.0, true);
            
            points[i] = new Point(xx, yy, 1.0, false);
            p2[i] = new Point(xx, yy, 1.0, false);
            p3[i] = new Point(xx, yy, 1.0, false);
            p4[i] = new Point(xx, yy, 1.0, false);
            p5[i] = new Point(xx, yy, 1.0, false);
            p6[i] = new Point(xx, yy, 1.0, false);
            p7[i] = new Point(xx, yy, 1.0, false);
            p8[i] = new Point(xx, yy, 1.0, false);
            p9[i] = new Point(xx, yy, 1.0, false);

            yy += yIncrement;
        }

    for (int i = 0; i < NUM_OBJECTS; i++) {
        
        points[i]->shape.setFillColor(red);
        p3[i]->shape.setFillColor(red);
        p5[i]->shape.setFillColor(red);
        p7[i]->shape.setFillColor(red);
        p9[i]->shape.setFillColor(red);
    
    }
    const int NUM_STICKS = NUM_OBJECTS -1;

    Stick* sticks[NUM_STICKS];
    Stick* sticks1[NUM_STICKS];
    Stick* sticks2[NUM_STICKS];
    Stick* sticks6[NUM_STICKS];
    Stick* sticks7[NUM_STICKS];
    Stick* sticks9[NUM_STICKS];
    Stick* sticks11[NUM_STICKS];
    Stick* sticks12[NUM_STICKS];
    Stick* sticks15[NUM_STICKS];

    for (int i = 0; i < NUM_STICKS; i++) {
        sticks[i] = new Stick(points[i], points[i + 1], 40);
        sticks1[i] = new Stick(p2[i], p2[i + 1], 40);
        sticks2[i] = new Stick(p3[i], p3[i + 1], 40);
        sticks6[i] = new Stick(p4[i], p4[i + 1], 40);
        sticks7[i] = new Stick(p5[i], p5[i + 1], 40);
        sticks9[i] = new Stick(p6[i], p6[i + 1], 40);
        sticks11[i] = new Stick(p7[i], p7[i + 1], 40);
        sticks12[i] = new Stick(p8[i], p8[i + 1], 40);
        sticks15[i] = new Stick(p9[i], p9[i + 1], 40);
  
    }

    Stick* sticks4[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks4[i] = new Stick(points[i], p2[i], 40);
    }

    Stick* sticks3[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks3[i] = new Stick(p2[i], p3[i], 40);
    }

    Stick* sticks5[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks5[i] = new Stick(p3[i], p4[i], 40);
    }

    Stick* sticks8[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks8[i] = new Stick(p4[i], p5[i], 40);
    }

    Stick* sticks10[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks10[i] = new Stick(p5[i], p6[i], 40);
    }

    Stick* sticks13[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks13[i] = new Stick(p6[i], p7[i], 40);
    }

    Stick* sticks14[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks14[i] = new Stick(p7[i], p8[i], 40);
    }

    Stick* sticks16[NUM_STICKS];
    for (int i = 0; i < NUM_STICKS; i++) {
        sticks16[i] = new Stick(p8[i], p9[i], 40);
    }

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart(); // get the time elapsed since the last restart and restart the clock
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update all points
        for (int i = 0; i < NUM_OBJECTS; i++) {
            points[i]->update_verlet(dt);
            p2[i]->update_verlet(dt);
            p3[i]->update_verlet(dt);
            p4[i]->update_verlet(dt);
            p5[i]->update_verlet(dt);
            p6[i]->update_verlet(dt);
            p7[i]->update_verlet(dt);
            p8[i]->update_verlet(dt);
            p9[i]->update_verlet(dt);
        }

        // Update all sticks
        for (int i = 0; i < NUM_STICKS; i++) {
            sticks[i]->update(dt);
            sticks1[i]->update(dt);
            sticks2[i]->update(dt);
            sticks3[i]->update(dt);
            sticks4[i]->update(dt);
            sticks5[i]->update(dt);
            sticks6[i]->update(dt);
            sticks7[i]->update(dt);
            sticks8[i]->update(dt);
            sticks9[i]->update(dt);
            sticks10[i]->update(dt);
            sticks11[i]->update(dt);
            sticks12[i]->update(dt);
            sticks13[i]->update(dt);
            sticks14[i]->update(dt);
            sticks15[i]->update(dt);
            sticks16[i]->update(dt);
        }
        // Apply Constraints
        for (int i = 0; i < NUM_OBJECTS; i++) {
            points[i]->constraint(Width, Height);
            p2[i]->constraint(Width, Height);
            p3[i]->constraint(Width, Height);
            p4[i]->constraint(Width, Height);
            p5[i]->constraint(Width, Height);
            p6[i]->constraint(Width, Height);
            p7[i]->constraint(Width, Height);
            p8[i]->constraint(Width, Height);
            p9[i]->constraint(Width, Height);
        }

        window.clear(sf::Color::Black);

        window.draw(grid);
        window.draw(floor);
        window.draw(right);
        window.draw(left);
        // Render all Points & Sticks
        for (int i = 0; i < NUM_STICKS; i++) {
            sticks[i]->render(window);
            sticks1[i]->render(window);
            sticks2[i]->render(window);
            sticks3[i]->render(window);
            sticks4[i]->render(window);
            sticks5[i]->render(window);
            sticks6[i]->render(window);
            sticks7[i]->render(window);
            sticks8[i]->render(window);
            sticks9[i]->render(window);
            sticks10[i]->render(window);
            sticks11[i]->render(window);
            sticks12[i]->render(window);
            sticks13[i]->render(window);
            sticks14[i]->render(window);
            sticks15[i]->render(window);
            sticks16[i]->render(window);
        }

        for (int i = 0; i < NUM_OBJECTS; i++) {
            points[i]->render(window);
            p2[i]->render(window);
            p3[i]->render(window);
            p4[i]->render(window);
            p5[i]->render(window);
            p6[i]->render(window);
            p7[i]->render(window);
            p8[i]->render(window);
            p9[i]->render(window);
            
        }
        window.display();
    }

    return 0;
}
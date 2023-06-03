#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

#include <vector>
#include "../header/point.h"
#include "../header/stick.h"
#include "../header/guioverlay.h"

int Width = 1280;
int Height = 720;

const int NumRows = 14;
const int NumColumns = 25;
const float CellSize = 51.1f;

const int NUM_OBJECTS = 45;
int numIterations = 50;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Verlet Integration", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::Clock clock;

    ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    bool show = true;

    sf::Color red(235, 69, 95);
    sf::Color green(13, 84, 93);

    sf::VertexArray grid(sf::Lines);

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

    std::vector<Point> points;
    float xini = 450;
    for (int i = 0; i < NUM_OBJECTS; i++) {
        float yini = 200;
        for (int j = 0; j < NUM_OBJECTS; j++) {
            Point p = Point(xini, yini, 1, false);
            points.push_back(p);
            yini = yini + 10;
        }
        xini = xini + 10;
    }

    float initialx = 450;
    float initialy = 200;
    for (int i = 0; i <= 35; i = i + 5) {
        points[i] = Point(initialx, initialy, 1.0, true);
        initialx = initialx + 50;

    }

    std::vector<Stick> sticks;
    //   Point d[NUM_OBJECTS][NUM_OBJECTS];
    Point*** d = new Point * *[NUM_OBJECTS];

    for (int i = 0; i < NUM_OBJECTS; i++) {
        d[i] = new Point * [NUM_OBJECTS];
        for (int j = 0; j < NUM_OBJECTS; j++) {
            d[i][j] = &points[static_cast<std::vector<Point, std::allocator<Point>>::size_type>(i) * NUM_OBJECTS + j];
        }
    }

    for (int i = 0; i < NUM_OBJECTS - 1; i++) {
        for (int j = 0; j < NUM_OBJECTS - 1; j++) {

            Point* a = d[i][j];
            Point* b1 = d[i + 1][j];
            Point* b2 = d[i][j + 1];
            Stick stick1(a, b1, 10);
            sticks.push_back(stick1);
            Stick stick2(a, b2, 10);
            sticks.push_back(stick2);
        }
    }

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart(); // get the time elapsed since the last restart and restart the clock
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Updating the points positions
        for (int i = 0; i < NUM_OBJECTS; i++) {
            for (int j = 0; j < NUM_OBJECTS; j++) {
                d[i][j]->Update_Verlet(dt);
            }
        }

        // Updating the sticks positions (through increasing iterations to increase performance)
        for (int i = 0; i < numIterations; i++) {
            for (Stick& stick : sticks) {
                stick.Update(dt / numIterations);
            }
        }

        ImGui::SFML::Update(window, clock.restart());
        Overlay::ShowSideBar();

        Overlay::ShowOverlay(&show);
        window.clear();

        // Drawing the background grid
        window.draw(grid);

        // Rendering the sticks
        for (Stick& stick : sticks) {
            stick.Render(window);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    // Memory Deallocation
    for (int i = 0; i < NUM_OBJECTS; i++) {
        delete[] d[i];
    }
    delete[] d;

    ImGui::SFML::Shutdown();
    return 0;
}

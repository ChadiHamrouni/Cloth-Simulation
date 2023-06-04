#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <vector>

#include "../header/point.h"
#include "../header/stick.h"
#include "../header/guioverlay.h"

int Width = 1280;
int Height = 720;

const int NUM_OBJECTS = 40;
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

    Overlay::SetupGrid();

    std::vector<Point> points;
    Point::SetInitialPosition(NUM_OBJECTS, points);
    Point::SetAnchorPoints(points);

    // Store the points in a 2D array to ease connecting the points
    Point*** d = new Point * *[NUM_OBJECTS];
    for (int i = 0; i < NUM_OBJECTS; i++) {
        d[i] = new Point * [NUM_OBJECTS];
        for (int j = 0; j < NUM_OBJECTS; j++) {
            d[i][j] = &points[static_cast<std::vector<Point, std::allocator<Point>>::size_type>(i) * NUM_OBJECTS + j];
        }
    }
    
    // Connecting every point with its right and below neighbor
    std::vector<Stick> sticks;
    for (int i = 0; i < NUM_OBJECTS - 1; i++) {
        for (int j = 0; j < NUM_OBJECTS - 1; j++) {
            Point* a = d[i][j]; 
            Point* b1 = d[i + 1][j]; // Connect the Point with its right neighbor
            Point* b2 = d[i][j + 1]; // Connect Point with it's below  

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
                d[i][j]->UpdateVerlet(dt);
            }
        }

        // Updating the sticks positions through iterations to increase performance
        for (int i = 0; i < numIterations; i++) {
            for (Stick& stick : sticks) {
                stick.Update(dt / numIterations);
            }
        }

        ImGui::SFML::Update(window, clock.restart());

        // Rendering the GUI components
        Overlay::ShowSideBar();
        Overlay::ShowOverlay(&show);

        window.clear();

        // Drawing the background grid
        Overlay::RenderGrid(window);

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

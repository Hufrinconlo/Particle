// main.cpp
#include <SFML/Graphics.hpp>
#include "simulation.hpp"
#include "color_utils.hpp"

#include <thread> // For sleep
#include <chrono> // For time

// Function prototype for graphics rendering
void renderGraphics(sf::RenderWindow& window, const std::vector<Circle>& circles);

int main() {
    int width = 300;
    int height = 200;
    int flag = 0;

    double gravity = 9.8;   // Gravity constant (adjust as needed)
    double timeStep = 0.05;  // Time step for each update

    const int maxBalls = 20;
    const double radius = 20;

    sf::RenderWindow window(sf::VideoMode(width, height), "2D Particle Simulation");

    std::vector<Circle> circles;

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<double> dampingDist(0.4, 0.6);  // Damping factor range
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateLogic(circles, width, height, gravity, timeStep);  // Update the logic
        renderGraphics(window, circles);   // Render the graphics

        if (circles.size() < maxBalls && flag%50 == 0) {
            int x = radius + (rand() % int(width - 2*radius));
            double dampingFactor = dampingDist(rng);
            circles.push_back(Circle(x, 0, radius, getRandomColor(), dampingFactor));

        }
        flag++;

        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Wait a bit

    }

    return 0;
}

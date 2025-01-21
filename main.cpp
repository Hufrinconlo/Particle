// main.cpp
#include <SFML/Graphics.hpp>
#include "simulation.hpp"
#include "color_utils.hpp"
#include "Variables.hpp"

#include <thread> // For sleep
#include <chrono> // For time

// Function prototype for graphics rendering
void renderGraphics(sf::RenderWindow& window, const std::vector<Circle>& circles);

int main() {
    int flag = 0; // sirve para que no agrege bolas en cada iteracion
    int id_counter = 0; // Para asignar ids a los circulos

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    // Se le resta para que no se salgan de la pantalla
    desktop.width = desktop.width-100;
    desktop.height = desktop.height-100;

    int width = desktop.width;
    int height = desktop.height;

    std::cout<<width<<" "<<height<<std::endl;

    sf::RenderWindow window(desktop, "2D Particle Simulation");

    std::vector<Circle> circles;

    CollisionGrid grid(width, height, conf::cellSize); // Grid with a specified cell size

    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<double> dampingDist(0.4, 0.6);  // Damping factor range
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key press event
            if (event.type == sf::Event::KeyPressed) {
                // Close the window if Escape is pressed
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                /*
                if ( event.key.code == sf::Keyboard::Space) {
                    int newX = radius + (rand() % int(width - 2*radius));
                    int newY = 0;

                    // Use the function from logic.cpp via logic.hpp
                    if (!isOverlapping(circles, newX, newY, radius)) {
                        double dampingFactor = dampingDist(rng);
                        circles.push_back(Circle(newX, 0, radius, getRandomColor(), dampingFactor));
                    }
                }*/
            }
        }

        if (circles.size() < conf::maxBalls && flag%20 == 0) {
            int x = conf::radius + (rand() % int(width - 2*conf::radius));
            double dampingFactor = dampingDist(rng);
            circles.emplace_back(x, conf::radius, conf::radius, getRandomColor(), dampingFactor, id_counter);
            id_counter++;
        }
        flag++;
        std::cout<<"Inserta una bola"<<std::endl;
        updateLogicSubStep(circles, width, height, grid);  // Update the logic
        renderGraphics(window, circles);   // Render the graphics

    }

    return 0;
}

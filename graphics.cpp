// graphics.cpp
#include <SFML/Graphics.hpp>
#include "simulation.hpp"
#include "color_utils.hpp"

void renderGraphics(sf::RenderWindow& window, const std::vector<Circle>& circles) {
    window.clear(sf::Color::Black);

    for (const auto& circle : circles) {
        sf::CircleShape shape(10); // Radius of 10 pixels
        shape.setFillColor(circle.color); // Use the color mapping function
        shape.setPosition(circle.x, circle.y); // Scale positions by 20 for better visibility
        window.draw(shape);
    }

    window.display();
}

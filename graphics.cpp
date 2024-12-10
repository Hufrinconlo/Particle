// graphics.cpp
#include <SFML/Graphics.hpp>
#include "simulation.hpp"
#include "color_utils.hpp"
#include "Variables.hpp"

void renderGraphics(sf::RenderWindow& window, const std::vector<Circle>& circles) {
    window.clear(sf::Color::Black);

    for (const auto& circle : circles) {
        sf::CircleShape shape(circle.radius);
        shape.setFillColor(circle.color); // Use the color mapping function
        shape.setOrigin(circle.radius, circle.radius); // Set the origin to the center of the circle
        shape.setPosition(circle.x, circle.y); 
        window.draw(shape);
    }
    
    sf::Vector2u windowSize = window.getSize();

    // Extract the width and height
    unsigned int width = windowSize.x-20;
    unsigned int height = windowSize.y-20;
    
    
    sf::RectangleShape wall (sf::Vector2f(width, height));
    wall.setPosition(10,10);
    wall.setFillColor(sf::Color::Transparent);
    wall.setOutlineColor(sf::Color::White);
    wall.setOutlineThickness(10);
    window.draw(wall);

    window.display();
}

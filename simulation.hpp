// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <string>
#include "color_utils.hpp"

struct Circle {
    double x;
    double y;
    double vel;
    sf::Color color;
    double dampingFactor;

    Circle(double startX, double startY, sf::Color colorName, double DampingFactor) : 
            x(startX), y(startY), vel(0.0), color(colorName), dampingFactor(DampingFactor){}
};

// Function prototypes
void updateLogic(std::vector<Circle>& circles, int width, int height, double gravity, double timeStep);

#endif // SIMULATION_HPP

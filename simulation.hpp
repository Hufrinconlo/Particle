// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <string>
#include "color_utils.hpp"

#include <iostream>

struct Circle {
    double x;
    double y;
    double velX;
    double velY;
    double radius;
    sf::Color color;
    double dampingFactor;

    Circle(double startX, double startY, double startRadius ,sf::Color colorName, double DampingFactor) : 
    x(startX), y(startY), velX(0.0), velY(0.0), radius(startRadius), color(colorName), dampingFactor(DampingFactor){}
};

// Function prototypes
void updateLogicSubStep(std::vector<Circle>& circles, int width, int height);

void updateLogic(std::vector<Circle>& circles, int width, int height, double timeStep);

double calculateDistance(double x1, double y1, double x2, double y2);

void handleCollision(Circle& circle1, Circle& circle2, int width, int height);

bool isCollision(const Circle& circle1, const Circle& circle2);

bool isOverlapping(const std::vector<Circle>& circles, float newX, float newY, float radius);

#endif // SIMULATION_HPP

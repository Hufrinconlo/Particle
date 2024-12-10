// logic.cpp
#include "simulation.hpp"
#include "Variables.hpp"

void updateLogicSubStep(std::vector<Circle>& circles, int width, int height){
    double timeStep = double(conf::timeStep/conf::subSteps);

    for (int i = 0; i < conf::subSteps; i++){
        updateLogic(circles, width, height, timeStep);
    }
}

void updateLogic(std::vector<Circle>& circles, int width, int height, double timeStep){
    const int val = 10; // esta variable está para poner un bordillo
    // Check and handle collisions between circles
    for (size_t i = 0; i < circles.size(); ++i) {
        for (size_t j = i + 1; j < circles.size(); ++j) {
            if (isCollision(circles[i], circles[j])) {
                handleCollision(circles[i], circles[j], width, height);
            }
        }
    }
    for (auto& circle : circles) {

        // Example logic: move down until the bottom or collision

        // x(t) = x + v*t + a * t

        circle.velY += conf::gravity * timeStep;

        // Update position with velocity
        circle.x += circle.velX * timeStep;
        circle.y += circle.velY * timeStep;

        if (circle.y > height - circle.radius- val) {
            
            circle.y = height - circle.radius - val;
            circle.velY = -circle.velY * circle.dampingFactor;
        }
        if (circle.x > width - circle.radius - val){
            circle.x = width - circle.radius - val;
            circle.velX = -circle.velX * circle.dampingFactor;
        }
        if (circle.x - circle.radius - val < 0){
            circle.x = circle.radius + val;
            circle.velX = -circle.velX * circle.dampingFactor;
        }
    }
}

bool isCollision(const Circle& circle1, const Circle& circle2) {
    double distance = calculateDistance(circle1.x, circle1.y, circle2.x, circle2.y);
    return distance < (circle1.radius + circle2.radius);
}

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void handleCollision(Circle& circle1, Circle& circle2, int width, int height) {
    // Normal vector
    double nx = circle2.x - circle1.x;
    double ny = circle2.y - circle1.y;
    double distance = std::sqrt(nx * nx + ny * ny);

    // Avoid division by zero
    if (distance == 0.0) return;

    // Normalize the normal vector
    nx /= distance;
    ny /= distance;

    double overlap = (-circle1.radius - circle2.radius) + distance;
    double separation = overlap / 2.0;

    if (circle1.y == height - circle1.radius || circle2.y == height - circle2.radius) {
    // Adjust based on which circle is constrained
        if (circle1.y == height - circle1.radius) {
            circle2.x -= nx * overlap;
            circle2.y -= ny * overlap;
        } else {
            circle1.x += nx * overlap;
            circle1.y += ny * overlap;
        }
    } else {
        // Equal separation for unconstrained circles
        circle1.x += nx * separation;
        circle1.y += ny * separation;
        circle2.x -= nx * separation;
        circle2.y -= ny * separation;
    }

    // Calculate relative velocity
    double dvx = circle1.velX - circle2.velX;
    double dvy = circle1.velY - circle2.velY;

    // Velocity along the normal direction
    double dotProduct = dvx * nx + dvy * ny;

    // Skip if the circles are moving away from each other
    if (dotProduct < 0) return;

    // Calculate the impulse
    double impulse = 19 * dotProduct / (circle1.radius + circle2.radius);

    // Apply impulse to the velocities
    circle1.velX -= impulse * nx;
    circle1.velY -= impulse * ny;
    circle2.velX += impulse * nx;
    circle2.velY += impulse * ny;
}

bool isOverlapping(const std::vector<Circle>& circles, float newX, float newY, float radius) {
    for (const auto& circle : circles) {
        float existingX = circle.x + circle.radius;
        float existingY = circle.y + circle.radius;
        float existingRadius = circle.radius;

        if (calculateDistance(newX, newY, existingX, existingY) < (radius + existingRadius)) {
            return true;
        }
    }
    return false;
}
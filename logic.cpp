// logic.cpp
#include "simulation.hpp"
#include "Variables.hpp"

void updateLogicSubStep(std::vector<Circle>& circles, int width, int height, CollisionGrid grid){
    double timeStep = double(conf::timeStep/conf::subSteps);

    for (int i = 0; i < conf::subSteps; i++){
        grid.update(circles);
        updateLogic(circles, width, height, timeStep);
        if (circles.size() > 1) {
        checkCollisions(grid, circles, width, height);
        std::cout<<"Sale de checkCollisions"<<std::endl;}
    }
}

void checkCollisions(CollisionGrid& grid, std::vector<Circle>& circles, int width, int height) {
    std::cout<<"Entra a checkCollisions"<<std::endl;
    // Neighboring cell offsets
    const int neighborOffsets[9][2] = {
        {0, 0},   // Current cell
        {-1, 0},  // Left
        {1, 0},   // Right
        {0, -1},  // Top
        {0, 1},   // Bottom
        {-1, -1}, // Top-left
        {-1, 1},  // Bottom-left
        {1, -1},  // Top-right
        {1, 1}    // Bottom-right
    };

    // Loop through all cells in the grid
    for (int x = 0; x < grid.width; ++x) {
        for (int y = 0; y < grid.height; ++y) {
            const auto& cell = grid.getCell(x, y);

            // Intra-cell collision
            for (size_t i = 0; i < cell.objects_count; ++i) {
                uint32_t circleIdx1 = cell.objects[i];
                Circle& c1 = circles[circleIdx1];

                // Check collisions with other objects in the same cell
                for (size_t j = i + 1; j < cell.objects_count; ++j) {
                    uint32_t circleIdx2 = cell.objects[j];
                    Circle& c2 = circles[circleIdx2];
                    std::cout<<"intra in"<<std::endl;
                    handleCollision(c1, c2, width, height);
                    std::cout<<"intra out"<<std::endl;
                }
            }

            // Inter-cell collision with neighbors
            for (const auto& offset : neighborOffsets) {
                int nx = x + offset[0];
                int ny = y + offset[1];

                // Skip invalid neighbors (out of bounds)
                if (!grid.isValidCell(nx, ny)) continue;

                const auto& neighborCell = grid.getCell(nx, ny);

                for (size_t i = 0; i < cell.objects_count; ++i) {
                    uint32_t circleIdx1 = cell.objects[i];
                    Circle& c1 = circles[circleIdx1];

                    for (size_t j = 0; j < neighborCell.objects_count; ++j) {
                        uint32_t circleIdx2 = neighborCell.objects[j];
                        Circle& c2 = circles[circleIdx2];

                        // Avoid duplicate checks
                        if (circleIdx1 >= circleIdx2) continue;
                        std::cout<<"inter in"<<std::endl;
                        handleCollision(c1, c2, width, height);
                        std::cout<<"inter out"<<std::endl;
                    }
                }
            }
        }
    }
}

void updateLogic(std::vector<Circle>& circles, int width, int height, double timeStep){
    std::cout<<"Entra a updateLogic"<<std::endl;
    const int val = 10; // esta variable está para poner un bordillo
    
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

double calculateDistance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void handleCollision(Circle& circle1, Circle& circle2, int width, int height) {
    std::cout<<"Entra a handleCollision"<<std::endl;
    // Normal vector
    double nx = circle2.x - circle1.x;
    double ny = circle2.y - circle1.y;
    double distance = calculateDistance(circle1.x, circle1.y, circle2.x, circle2.y);
    std::cout<<"porno"<<std::endl;
    // Avoid division by zero
    if (distance == 0.0 || distance > circle1.radius + circle2.radius) return;
    std::cout<<"por2"<<std::endl;
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
    std::cout<<"por3"<<std::endl;

    // Calculate relative velocity
    double dvx = circle1.velX - circle2.velX;
    std::cout<<"por4"<<std::endl;
    double dvy = circle1.velY - circle2.velY;
    std::cout<<"por5"<<std::endl;

    // Velocity along the normal direction
    double dotProduct = dvx * nx + dvy * ny;
    std::cout<<"por6"<<std::endl;
    // Skip if the circles are moving away from each other
    if (dotProduct < 0) return;
    std::cout<<"por7"<<std::endl;
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
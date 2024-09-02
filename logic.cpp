// logic.cpp
#include "simulation.hpp"

void updateLogic(std::vector<Circle>& circles, int width, int height, double gravity, double timeStep){
    
    
    for (auto& circle : circles) {
        // Example logic: move down until the bottom or collision

        // x(t) = x + v*t + a * t

            circle.vel += gravity * timeStep;
            circle.y += circle.vel * timeStep;

        if (circle.y > height - 30) {
            
            circle.y = height - 30;
            circle.vel = -circle.vel * circle.dampingFactor;
        }
    }
}

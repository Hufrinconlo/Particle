// simulation.hpp
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <string>
#include "color_utils.hpp"

#include <unordered_map>
#include <utility> // for std::pair
#include <cmath>   // for std::floor

#include <iostream>

struct Circle {
    double x;
    double y;
    double velX;
    double velY;
    double radius;
    sf::Color color;
    double dampingFactor;
    int id;

    Circle(double startX, double startY, double startRadius ,sf::Color colorName, double DampingFactor, int id) : 
    x(startX), y(startY), velX(0.0), velY(0.0), radius(startRadius), color(colorName), dampingFactor(DampingFactor), id(id){}
};

// Simplified Grid and CollisionGrid without inheritance

struct CollisionCell {
    static constexpr uint8_t cell_capacity = 4;
    static constexpr uint8_t max_cell_idx  = cell_capacity - 1;
    uint32_t objects_count = 0;
    uint32_t objects[cell_capacity] = {};

    void addCircle(uint32_t id) {
        if (objects_count < cell_capacity) {
            objects[objects_count++] = id;
        }
    }

    void clear() {
        objects_count = 0;
    }

    void remove(uint32_t id) {
        for (uint32_t i = 0; i < objects_count; ++i) {
            if (objects[i] == id) {
                objects[i] = objects[objects_count - 1];
                --objects_count;
                return;
            }
        }
    }
};

struct CollisionGrid {
    int32_t width;
    int32_t height;
    int32_t cellSize;
    std::vector<std::vector<CollisionCell>> cells;

    CollisionGrid(int32_t width, int32_t height, int32_t cellSize)
        : width(width), height(height), cellSize(cellSize) {
        int numCellsX = width / cellSize+1;
        int numCellsY = height / cellSize+1;
        cells.resize(numCellsX, std::vector<CollisionCell>(numCellsY));
    }

    auto& getCell (int x, int y){
        return cells[x][y];
    }

    // Helper to calculate the grid cell index for a given position
    int getCellIndex(int32_t x, int32_t y) {
        int cellX = x / cellSize;
        int cellY = y / cellSize;
        return cellY * (width / cellSize) + cellX;
    }

    void addCircle(int32_t x, int32_t y, uint32_t circleId) {
        int gridX = x / cellSize;
        int gridY = y / cellSize;
        if (isValidCell(gridX, gridY)) {
            cells[gridX][gridY].addCircle(circleId);
        }
    }

    void clear() {
        for (auto& column : cells) {
            for (auto& cell : column) {
                cell.clear();
            }
        }
    }

    bool isValidCell(int gridX, int gridY) const {
        return gridX >= 0 && gridX < cells.size() &&
               gridY >= 0 && gridY < cells[0].size();
    }

    // Actualiza la grilla para reflejar los cambios de los circulos
    void update(const std::vector<Circle>& circles) {
        clear();  // Clear the grid first
        for (size_t i = 0; i < circles.size(); ++i) {
            const Circle& c = circles[i];
            int gridX = static_cast<int>(c.x) / cellSize;
            int gridY = static_cast<int>(c.y) / cellSize;
            cells[gridX][gridY].addCircle(c.id);
        }
    }

};


// Function prototypes
void resolveCollision(Circle& c1, Circle& c2, int width, int height);

void checkCollisions(CollisionGrid& grid, std::vector<Circle>& circles, int width, int height);

void updateLogicSubStep(std::vector<Circle>& circles, int width, int height, CollisionGrid grid);

void updateLogic(std::vector<Circle>& circles, int width, int height, double timeStep);

double calculateDistance(double x1, double y1, double x2, double y2);

void handleCollision(Circle& circle1, Circle& circle2, int width, int height);

bool isCollision(const Circle& circle1, const Circle& circle2);

bool isOverlapping(const std::vector<Circle>& circles, float newX, float newY, float radius);

#endif // SIMULATION_HPP

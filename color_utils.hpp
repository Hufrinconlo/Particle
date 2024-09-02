// color_utils.hpp
#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>

// Function to get color from name
sf::Color getColorFromName(const std::string& colorName);

// Function to get a random color
sf::Color getRandomColor();

#endif // COLOR_UTILS_HPP
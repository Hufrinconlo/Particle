// color_utils.hpp

#include "color_utils.hpp"

sf::Color getColorFromName(const std::string& colorName) {
    static const std::unordered_map<std::string, sf::Color> colorMap = {
        {"red", sf::Color::Red},
        {"blue", sf::Color::Blue},
        {"green", sf::Color::Green},
        {"yellow", sf::Color::Yellow},
        {"white", sf::Color::White},
        {"black", sf::Color::Black},
        {"magenta", sf::Color::Magenta},
        {"cyan", sf::Color::Cyan}
    };

    auto it = colorMap.find(colorName);
    if (it != colorMap.end()) {
        return it->second;
    } else {
        return sf::Color::White; // Default color if not found
    }
}

sf::Color getRandomColor(){
    static const std::vector<std::string> colorNames = {
        "red", "blue", "green", "yellow", "white", "black", "magenta", "cyan"
    };

    static std::random_device rd;
    static std::mt19937 rng(rd()); // Initialize random number generator
    std::uniform_int_distribution<size_t> dist(0, colorNames.size() - 1); // Distribution

    int index = dist(rng); // Generate random index
    return getColorFromName(colorNames.at(index)); // Return the color name
}

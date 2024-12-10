# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(Simulation)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable target
add_executable(simulation main.cpp logic.cpp graphics.cpp color_utils.cpp)

# Link SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(simulation sfml-graphics sfml-window sfml-system)


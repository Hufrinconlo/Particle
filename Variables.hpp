#pragma once

namespace conf
{
    double const gravity = 9.8;   // Gravity constant (adjust as needed)
    double const timeStep = 0.016;  // Time step for each update

    const int maxBalls = 500;
    const double radius = 10;

    const double cellSize = radius*1.5;

    const int subSteps = 4;
}

// Por ahora los indices y los ids serán iguales, cuando empiece a eliminar circulos la 
// cosa va a cambiar y tocará corregir eso
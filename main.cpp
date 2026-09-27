#include <iostream>
#include "Vector2D.h"

int main()
{
    Vector2D position(200, 150);
    Vector2D velocity(5, -2);

    Vector2D newPosition = position.add(velocity);

    std::cout << "New position: "
              << newPosition.x << ", "
              << newPosition.y << std::endl;

    std::cout << "Velocity magnitude: "
              << velocity.magnitude() << std::endl;

    return 0;
}
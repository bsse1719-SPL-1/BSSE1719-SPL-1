#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::add(Vector2D v)
{
    return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::subtract(Vector2D v)
{
    return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::multiply(double value)
{
    return Vector2D(x * value, y * value);
}

double Vector2D::magnitude()
{
    return sqrt(x * x + y * y);
}
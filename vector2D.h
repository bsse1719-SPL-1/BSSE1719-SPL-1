#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    double x;
    double y;

    Vector2D();
    Vector2D(double x, double y);

    Vector2D add(Vector2D v);
    Vector2D subtract(Vector2D v);
    Vector2D multiply(double value);

    double magnitude();
};

#endif
#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdexcept>

using namespace std;

class Vector2
{
public:
    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    void Normalize()
    {
        float length = sqrt(x * x + y * y);
        if (length == 0)
            throw std::runtime_error("Cannot normalize a zero-length vector.");
        
        x /= length;
        y /= length;
    }
       
public:
    float x;
    float y;
};


#endif // ! VECTOR2_H
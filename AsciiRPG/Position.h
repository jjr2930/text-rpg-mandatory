#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"
#include "IConstructionParameter.h"
#include "Vector2Int.h"

#include <iostream>
#include <cstdlib>

/*
* TODO: x,y -> vector2int로 변경, Transform으로 바꾸는게 나을지도?
*/
class Position : public Component
{
public: class ConstructParameter : public Component::ConstructionParamterBase
{
public:
    ConstructParameter(int x, int y, shared_ptr<Entity> entity)
        : Component::ConstructionParamterBase(entity)
    {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
    shared_ptr<Entity> entity;
};
public:
    Position(int64_t id, const std::string& name, std::shared_ptr<IConstructionParameter> params);
    void TryMoveXOnly(int deltaX);
    void TryMoveYOnly(int deltaY);
    bool CanMoveTo(shared_ptr<Position> position, int newX, int newY);

    //getter
    int GetX() const { return x; }
    int GetY() const { return y; }
    Vector2Int GetPosition() const { return Vector2Int(x, y); }

    //setter
    void SetX(int newX) { x = newX; }
    void SetY(int newY) { y = newY; }
    void SetPosition(int newX, int newY) { x = newX; y = newY; }

    //add
    void AddX(int deltaX) { x += deltaX; }
    void AddY(int deltaY) { y += deltaY; }
    void AddPosition(int deltaX, int deltaY) { x += deltaX; y += deltaY; }

    //multiply
    void MultiplyX(int factor) { x *= factor; }
    void MultiplyY(int factor) { y *= factor; }
    void MultiplyPosition(int factorX, int factorY) { x *= factorX; y *= factorY; }

    //divide
    void DivideX(int divisor)
    {
        if (divisor == 0)
        {
            std::cerr << "Error: Division by zero in DivideX" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        x /= divisor;
    }

    void DivideY(int divisor)
    {
        if (divisor == 0)
        {
            std::cerr << "Error: Division by zero in DivideY" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        y /= divisor;
    }

    void DividePosition(int divisorX, int divisorY)
    {
        if (divisorX == 0 || divisorY == 0)
        {
            std::cerr << "Error: Division by zero in DividePosition (x="
                << divisorX << ", y=" << divisorY << ")" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        x /= divisorX;
        y /= divisorY;
    }

private:
    int x;
    int y;
};

#endif // !POSITION_COMPONENT_H

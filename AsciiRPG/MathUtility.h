#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include "Vector2Int.h"

#include <cmath>

class MathUtility
{
    public :
        static bool IsOverlap(const Vector2Int& pos1, const Vector2Int& pos2, const int allowGap);
};

#endif // !MATH_UTILITY_H

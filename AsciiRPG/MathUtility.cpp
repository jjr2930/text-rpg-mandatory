#include "MathUtility.h"

bool MathUtility::IsOverlap(const Vector2Int& pos1, const Vector2Int& pos2, const int allowGap)
{
    int xGap = abs(pos1.x - pos2.x);
    int yGap = abs(pos1.y - pos2.y);

    if (yGap == 0 && xGap <= allowGap)
    {
        return true;
    }

    else if (xGap == 0 && yGap <= allowGap)
    {
        return true;
    }

    return false;
}

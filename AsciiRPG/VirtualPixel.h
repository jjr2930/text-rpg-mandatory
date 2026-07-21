#ifndef VIRTUAL_PIXEL_H
#define VIRTUAL_PIXEL_H

#include "Vector2Int.h"

class VirtualPixel
{
public:
    Vector2Int position;
    char character;
    int color;
};

#endif // !VIRTUAL_PIXEL_H
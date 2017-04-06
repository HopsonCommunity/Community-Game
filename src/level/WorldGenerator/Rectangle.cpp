#include "Rectangle.h"

namespace WGenerator
{


    Rectangle::Rectangle()
    {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

    Rectangle::Rectangle(uint x, uint y, uint width, uint height) : x(x), y(y), width(width), height(height)
    {
    }
}
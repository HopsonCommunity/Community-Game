#pragma once

#include "../../util/Types.h"

namespace WGenerator
{
    class Rectangle
    {
        public:
            Rectangle();
            Rectangle(uint x, uint y, uint width, uint height);
            uint x;
            uint y;
            uint width;
            uint height;
    };
}
#pragma once

#include "../Item.h"

struct Timestep;

namespace Item
{
    class System
    {
    public:
        virtual void update(const Timestep& ts, Item* item) = 0;
    };
}
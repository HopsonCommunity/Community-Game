#pragma once

#include "System.h"

namespace Item
{
    class SpriteDrawingSystem : public System
    {
    public:
        void update(const Timestep& ts, Item* item) override;
    };
}
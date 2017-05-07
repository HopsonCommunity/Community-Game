#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Item
{
    struct ComponentType
    {
        std::string name;
    };

    class Component
    {
    public:
        Component() {};

        virtual ComponentType* getType() const { return nullptr; }
    };
}
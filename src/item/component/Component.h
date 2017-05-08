#pragma once

namespace Item
{
    class Component
    {
    public:
        Component() {};
        virtual ~Component() {};

        virtual std::unique_ptr<Component> clone() { return std::make_unique<Component>(*this); };
    };
}

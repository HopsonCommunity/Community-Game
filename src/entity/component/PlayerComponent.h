#pragma once

#include "Component.h"

namespace Entity
{
    class PlayerComponent : public Component
    {
    public:
        PlayerComponent();
        PlayerComponent(nlohmann::json json);

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;;
    };
}

#pragma once

#include "Component.h"
#include "../../util/json.hpp"

namespace Framework
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

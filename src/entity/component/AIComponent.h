#pragma once

#include "Component.h"

#include "../../util/AStar.h"
#include "../../util/json.hpp"

namespace Entity
{
    class AIComponent : public Component
    {
    public:
        Entity* trackingEntity;
        double trackingDistance;

        std::function<std::vector<Util::Node*>(Vec2i, Vec2i, Level::Level*)> findPath;

        AIComponent(double trackingDistance);
        AIComponent(nlohmann::json json);

        static const int ID = 1;
    };
}

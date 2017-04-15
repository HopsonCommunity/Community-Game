#pragma once

#include "Component.h"

#include "../../util/AStar.h"

namespace Framework
{
    class AIComponent : public Component
    {
    public:
        AIComponent(double trackingDistance);
        AIComponent(nlohmann::json json);

        std::function<std::vector<Util::Node*>(Vec2i, Vec2i, Level::Level*)> findPath;
        Entity* trackingEntity;
        double trackingDistance;

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;
    };
}

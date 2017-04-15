#include "Component.h"

#include <SFML/Graphics.hpp>

#include "../../util/AStar.h"
#include "../../util/json.hpp"

namespace Framework
{
    class AIComponent : public Component
    {
    public:
        AIComponent(double trackingDistance);
        AIComponent(nlohmann::json json);

        std::function<std::vector<Util::Node*>(Util::Vec2i, Util::Vec2i, Level::Level*)> findPath;
        Entity* trackingEntity;
        double trackingDistance;

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;
    };
}

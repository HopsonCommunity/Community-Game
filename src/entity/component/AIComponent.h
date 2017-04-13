#include "Component.h"

#include <SFML/Graphics.hpp>

#include "../ai/pathfind/AStar.h"

#include "../../util/json.hpp"

namespace Framework
{
    class AIComponent : public Component
    {
    public:
        AIComponent();
        AIComponent(nlohmann::json json);

        std::vector<Node*> findPath(Vec2i start, Vec2i end, Level::Level* level);

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;
    };
}

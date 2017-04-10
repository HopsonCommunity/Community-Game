#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "../../util/json.hpp"

namespace Framework
{
	class CollisionComponent : public Component
	 {
	public:
		sf::FloatRect aabb;
	public:
		CollisionComponent(const sf::FloatRect& position);
		CollisionComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

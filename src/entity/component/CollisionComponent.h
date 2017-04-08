#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace Framework
{
	class CollisionComponent : public Component
	 {
	public:
		sf::FloatRect aabb;
	public:
		CollisionComponent(const sf::FloatRect& position);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
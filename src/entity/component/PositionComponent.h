#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"

namespace Framework
{
	class PositionComponent : public Component
	{
	public:
		sf::Vector2f position;
	public:
		PositionComponent(const sf::Vector2f& position);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
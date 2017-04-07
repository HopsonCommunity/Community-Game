#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace Framework
{
	class VelocityComponent : public Component
	{
	public:
		// double speed, angle; // WIP WIP
		sf::Vector2f velocity;
	public:
		VelocityComponent(const sf::Vector2f& velocity = {});

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
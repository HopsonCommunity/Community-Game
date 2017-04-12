#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

namespace Framework
{
	class VelocityComponent : public Component
	{
	public:
		float speed;
		sf::Vector2f velocity;
		bool moving;
	public:
		VelocityComponent(const sf::Vector2f& velocity = {});

		// Move at an angle
		void move(float angle);

		// Move x/y dir
		void move(int xa, int ya);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
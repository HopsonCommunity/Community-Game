#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

#include "../../util/json.hpp"
#include "../../util/Types.h"

namespace Framework
{
	class VelocityComponent : public Component
	{
	public:
		float acceleration; // eg. 5 pixels/sec^2
		sf::Vector2f velocity; // used for direction of movement
		bool moving;
	public:
		VelocityComponent(const sf::Vector2f& velocity = {});
		VelocityComponent(nlohmann::json json);
    
		// Move at an angle
		void move(float angle);

		// Move x/y dir
		void move(int xa, int ya);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"
#include "../../util/json.hpp"

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
		VelocityComponent(nlohmann::json json);
		void move(float angle);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

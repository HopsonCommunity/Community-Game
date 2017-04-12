#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "../../util/json.hpp"

namespace Framework
{
	class PositionComponent : public Component
	{
	public:
		sf::Vector2f position;
	public:
		PositionComponent(const sf::Vector2f& position = {0, 0});
		PositionComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

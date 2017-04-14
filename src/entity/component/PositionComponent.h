#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "../../util/json.hpp"
#include "../../maths/Maths.h"

namespace Framework
{
	class PositionComponent : public Component
	{
	public:
		vec2 position;
	public:
		PositionComponent(const vec2& position = {0, 0});
		PositionComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

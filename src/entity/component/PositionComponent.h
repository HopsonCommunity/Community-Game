#pragma once

#include "Component.h"

#include "../../util/json.hpp"

namespace Entity
{
	class PositionComponent : public Component
	{
	public:
		Vec2 position;

		PositionComponent(const Vec2& position = {0, 0});
		PositionComponent(nlohmann::json json);

        static const int ID = 6;
	};
}

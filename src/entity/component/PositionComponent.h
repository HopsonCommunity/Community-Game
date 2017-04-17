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

        std::unique_ptr<Component> clone() override
        {
            return std::make_unique<PositionComponent>(*this);
        }

        static const int ID = 6;
	};
}

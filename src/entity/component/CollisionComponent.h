#pragma once

#include "Component.h"

#include "../../maths/Hitbox.h"
#include "../../util/json.hpp"

namespace Entity
{
	class CollisionComponent : public Component
	{
	public:
		Hitbox aabb;

		CollisionComponent(const Hitbox& hitbox);
		CollisionComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<CollisionComponent>(*this);
		}

		static const int ID = 3;
	};
}

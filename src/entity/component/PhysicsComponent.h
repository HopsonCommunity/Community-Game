#pragma once

#include "Component.h"

#include "../../maths/Collision.h"
#include "../../util/json.hpp"

namespace Entity
{
	class PhysicsComponent : public Component
	{
	public:
		Object object;

		PhysicsComponent(const Object& hitbox);
		PhysicsComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<PhysicsComponent>(*this);
		}

		static const int ID = 3;
	};
}

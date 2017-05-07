#pragma once

#include "Component.h"

#include "../../maths/AABB.h"
#include "../../util/json.hpp"

namespace Entity
{
	class PhysicsComponent : public Component
	{
	public:
		AABB aabb;
		Vec2 pos, velocity;
		bool moving;
		float movespeed;

		void setVelocity(float xa, float ya);

		PhysicsComponent(const AABB& hitbox);
		PhysicsComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<PhysicsComponent>(*this);
		}

		static const int ID = 3;
	};
}

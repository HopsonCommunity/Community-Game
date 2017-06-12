#pragma once

#include "Component.h"

#include "../maths/Rectangle.h"

namespace Components
{
	class PhysicsComponent : public Component
	{
	public:
		FloatRectangle bounds;
		Vec2 pos, velocity;
		bool moving;
		float movespeed;
		float sortOffset;

	public:
		PhysicsComponent(const FloatRectangle& hitbox);
		PhysicsComponent(nlohmann::json json);

		void setVelocity(float xa, float ya);

		std::unique_ptr<Component> clone() override { return std::make_unique<PhysicsComponent>(*this); }

		static const uint ID = ComponentID::Physics;
	};
}

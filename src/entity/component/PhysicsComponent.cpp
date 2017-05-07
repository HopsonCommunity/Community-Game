#include "PhysicsComponent.h"

namespace Entity
{
	void PhysicsComponent::setVelocity(float xa, float ya)
	{
		if (xa == 0 && ya == 0)
			return;
		velocity = { xa, ya };
		
		normalize(velocity);
		velocity *= movespeed;

		moving = true;
	}

	PhysicsComponent::PhysicsComponent(const AABB& obj)
		: aabb(obj)
	{}

	PhysicsComponent::PhysicsComponent(nlohmann::json json)
	{
		aabb = { { json["aabb"]["xMin"], json["aabb"]["yMin"] },{ json["aabb"]["xMax"], json["aabb"]["yMax"] } };
		movespeed = json["movespeed"];
	}
}
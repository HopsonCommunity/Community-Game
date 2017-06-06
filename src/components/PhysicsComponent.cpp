#include "PhysicsComponent.h"

#include "../util/Log.h"

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
		: aabb(obj), moving(false), movespeed(0), sortOffset(0)
	{
	}

	PhysicsComponent::PhysicsComponent(nlohmann::json json)
		: moving(false), movespeed(0)
	{
		aabb = { {0, 0}, {0, 0} };
		if (json.find("aabb") == json.end())
			LOG_WARN("[JSON] Entity with PhysicsComponent but without aabb! Setting to ", aabb, " as default.");
		else
			aabb = { { json["aabb"]["xMin"], json["aabb"]["yMin"] },{ json["aabb"]["xMax"], json["aabb"]["yMax"] } };

		if (json.find("movespeed") == json.end())
			LOG_WARN("[JSON] Entity with PhysicsComponent but without movespeed! Setting to \"", 0, "\" as default.");
		else
			movespeed = json["movespeed"];

		if (json.find("sortOffset") != json.end())
			sortOffset = json["sortOffset"];
	}
}

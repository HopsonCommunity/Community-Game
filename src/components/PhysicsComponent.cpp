#include "PhysicsComponent.h"

#include "../util/Log.h"

namespace Components
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

	PhysicsComponent::PhysicsComponent(const FloatRectangle& obj)
		: bounds(obj), moving(false), movespeed(0), sortOffset(0)
	{
	}

	PhysicsComponent::PhysicsComponent(nlohmann::json json)
		: moving(false), movespeed(0)
	{
		bounds = { {0, 0}, {0, 0} };
		if (json.find("collisionBox") == json.end())
			LOG_WARN("[JSON] Entity with PhysicsComponent but without FloatRectangle! Setting to ", bounds, " as default.");
		else
			bounds = { { json["collisionBox"]["x"], json["collisionBox"]["y"] },{ json["collisionBox"]["width"], json["collisionBox"]["height"] } };

		if (json.find("movespeed") == json.end())
			LOG_WARN("[JSON] Entity with PhysicsComponent but without movespeed! Setting to \"", movespeed, "\" as default.");
		else
			movespeed = json["movespeed"];

		if (json.find("sortOffset") != json.end())
			sortOffset = json["sortOffset"];
	}
}

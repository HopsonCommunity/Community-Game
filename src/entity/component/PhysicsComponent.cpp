#include "PhysicsComponent.h"

namespace Entity
{
	PhysicsComponent::PhysicsComponent(const Object& obj)
		: object(obj)
	{}

	PhysicsComponent::PhysicsComponent(nlohmann::json json)
		: object()
	{
		object.aabb = { { json["aabb"]["xMin"], json["aabb"]["yMin"] },{ json["aabb"]["xMax"], json["aabb"]["yMax"] } };

		object.density = json["density"];
		object.restitution = json["restitution"];

		object.initMass();
	}
}
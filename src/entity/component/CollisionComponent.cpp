#include "CollisionComponent.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(const Hitbox& aabb)
		: aabb(aabb)
	{}

	CollisionComponent::CollisionComponent(nlohmann::json json) 
		: aabb({ json["aabb"]["xMin"], json["aabb"]["yMin"], json["aabb"]["xMax"], json["aabb"]["yMax"] })
	{}

	ComponentType* CollisionComponent::getStaticType()
	{
		static ComponentType type({ "Collision" });
		return &type;
	}

	ComponentType* CollisionComponent::getType() const
	{
		return getStaticType();
	}


}

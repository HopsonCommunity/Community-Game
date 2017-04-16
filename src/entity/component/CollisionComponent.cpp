#include "CollisionComponent.h"

namespace Entity
{
	CollisionComponent::CollisionComponent(const Hitbox& aabb)
		: aabb(aabb)
	{}

	CollisionComponent::CollisionComponent(nlohmann::json json) 
		: aabb({ json["aabb"]["xMin"], json["aabb"]["yMin"], json["aabb"]["xMax"], json["aabb"]["yMax"] })
	{}
}

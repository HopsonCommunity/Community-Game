#include "CollisionComponent.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(const sf::FloatRect& aabb)
		: aabb(aabb)
	{}

	CollisionComponent::CollisionComponent(nlohmann::json json) 
	{
		//aabb = sf::FloatRect(json["width"], json["height"]);
	}

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

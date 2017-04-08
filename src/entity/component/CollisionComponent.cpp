#include "CollisionComponent.h"

namespace Framework
{
	CollisionComponent::CollisionComponent(const sf::FloatRect& aabb)
		: aabb(aabb)
	{
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
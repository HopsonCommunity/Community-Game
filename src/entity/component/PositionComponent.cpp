#include "PositionComponent.h"

namespace Framework
{
	PositionComponent::PositionComponent(const sf::Vector2f& position)
		: position(position)
	{
	}

	ComponentType* PositionComponent::getStaticType()
	{
		static ComponentType type({ "Position" });
		return &type;
	}

	ComponentType* PositionComponent::getType() const
	{
		return getStaticType(); 
	}
}
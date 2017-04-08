#include "VelocityComponent.h"

namespace Framework
{
	VelocityComponent::VelocityComponent(const sf::Vector2f& velocity)
		: velocity(velocity)
	{
	}

	ComponentType* VelocityComponent::getStaticType()
	{
		static ComponentType type({ "Velocity" });
		return &type;
	}
	
	ComponentType* VelocityComponent::getType() const 
	{
		return getStaticType(); 
	}
}
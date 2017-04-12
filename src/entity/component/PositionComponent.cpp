#include "PositionComponent.h"

namespace Framework
{
	PositionComponent::PositionComponent(const sf::Vector2f& position)
		: position(position)
	{
	}

	PositionComponent::PositionComponent(nlohmann::json json) 
	{
		position = sf::Vector2f(json["x"], json["y"]);
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

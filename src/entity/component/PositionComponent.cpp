#include "PositionComponent.h"

namespace Entity
{
	PositionComponent::PositionComponent(const Vec2& position)
		: position(position)
	{
	}

	PositionComponent::PositionComponent(nlohmann::json json)
		: position(Vec2(json["position"]["x"], json["position"]["y"]))
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

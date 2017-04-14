#include "PositionComponent.h"

namespace Framework
{
	PositionComponent::PositionComponent(const vec2& position)
		: position(position)
	{
	}

	PositionComponent::PositionComponent(nlohmann::json json)
		: position(vec2(json["position"]["x"], json["position"]["y"]))
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

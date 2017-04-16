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

}

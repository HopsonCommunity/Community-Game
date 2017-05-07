#include "LifeComponent.h"

namespace Entity
{
	LifeComponent::LifeComponent(float life)
		: life(life)
	{}

	LifeComponent::LifeComponent(nlohmann::json json)
		: life(json["duration"])
	{}
}
#include "LifeComponent.h"

#include "../util/Log.h"

namespace Entity
{
	LifeComponent::LifeComponent(float life)
		: life(life)
	{}

	LifeComponent::LifeComponent(nlohmann::json json)
		: life(20)
	{
		if (json.find("duration") == json.end())
			LOG_WARN("[JSON] Entity with LifeComponent no duration! Set to default (", life, ")");
		else
			life = json["duration"].get<float>();
	}
}

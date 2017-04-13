#include "PlayerComponent.h"

namespace Framework
{
	PlayerComponent::PlayerComponent()
	{

	}

	PlayerComponent::PlayerComponent(nlohmann::json json)
	{
	}

	ComponentType* PlayerComponent::getStaticType()
	{
		static ComponentType type({ "Player" });
		return &type;
	}

	ComponentType* PlayerComponent::getType() const
	{
		return getStaticType();
	}
}

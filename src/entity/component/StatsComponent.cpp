#include "StatsComponent.h"

namespace Framework
{
	StatsComponent::StatsComponent()
	{
	}

	StatsComponent::StatsComponent(nlohmann::json json) 
	{
		///@TODO: json parsing
	};

	void StatsComponent::addEffect(std::shared_ptr<StatusEffect> effect)
	{
		active_effects.push_back(effect);
	}

	ComponentType* StatsComponent::getStaticType()
	{
		static ComponentType type({ "Stats" });
		return &type;
	}

	ComponentType* StatsComponent::getType() const
	{
		return getStaticType();
	}
}

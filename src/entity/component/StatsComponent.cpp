#include "StatsComponent.h"

namespace Framework
{
	StatsComponent::StatsComponent()
	{
	}

	StatsComponent::StatsComponent(nlohmann::json json)
	{
		base_health_boost = std::make_shared<HealthBoost>(DURATION_INFINITE, json["base"]["max_health"], json["base"]["health_regen"]);
		base_defense = std::make_shared<Defense>(DURATION_INFINITE, json["base"]["armor"], json["base"]["magic_resist"]);
		
		addEffect(base_health_boost);
		addEffect(base_defense);

		stats.health = json["base"]["max_health"];
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

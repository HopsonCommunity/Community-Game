#include "StatsComponent.h"

namespace Entity
{
	StatsComponent::StatsComponent()
	{
	}

	StatsComponent::StatsComponent(nlohmann::json json)
	{
		if (json.find("base") != json.end())
		{
			active_effects.push_back(std::make_shared<HealthBoost>(-1, json["base"]["max_health"], json["base"]["health_regen"]));
			active_effects.push_back(std::make_shared<Defense>(-1, json["base"]["armor"], json["base"]["magic_resist"]));
			
			stats.health = json["base"]["max_health"];
		}
	};

#pragma region STATUS_EFFECT

	StatusEffect::StatusEffect(int32 duration)
		: m_duration(duration)
	{}

	// Effects with m_duration = -1 are infinite.
	void StatusEffect::manageDuration()
	{
		if (m_duration == 0)
			active = 0;

		if (m_duration > 0)
			m_duration--;
	}

	HealthBoost::HealthBoost(int32 duration, int32 maxHealth, int32 healthregen)
		: StatusEffect(duration)
		, max_health(maxHealth)
		, health_regen(healthregen)
	{}

	void HealthBoost::effect(Stats& stats)
	{
		stats.max_health += max_health;
		stats.health_regen += health_regen;
	}

	Defense::Defense(int32 duration, int32 armor, int32 mr)
		: StatusEffect(duration)
		, armor(armor)
		, magic_resist(mr)
	{}

	void Defense::effect(Stats& stats)
	{
		stats.armor += armor;
		stats.magic_resist += magic_resist;
	}

#pragma endregion
}
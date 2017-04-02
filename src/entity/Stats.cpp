#include "Stats.h"

namespace Framework
{
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
		, m_maxHealth(maxHealth)
		, m_healthRegen(healthregen)
	{}
	
	void HealthBoost::effect(Stats & stats)
	{
		stats.max_health += m_maxHealth;
		stats.health_regen += m_healthRegen;
	}
	
	Defense::Defense(int32 duration, int32 armor, int32 mr)
		: StatusEffect(duration)
		, m_armor(armor)
		, m_magicResist(mr)
	{}
	
	void Defense::effect(Stats & stats)
	{
		stats.armor += m_armor;
		stats.magic_resist += m_magicResist;
	}
}
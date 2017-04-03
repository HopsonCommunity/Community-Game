#pragma once

#include "../util/Types.h"

namespace Framework
{
	// Do not change entities' stats directly. Use StatusEffects. Example in Player constructor.
	struct Stats
	{
		int32 max_health, health_regen, armor, magic_resist;

		void reset() { max_health = 0, health_regen = 0, armor = 0, magic_resist = 0; }
	};

	// Similar status effects are grouped. Each status effect has its own
	// effect function which determines its effect on the stats of an
	// entity.

#define DURATION_INFINITE -1

	class StatusEffect
	{
	private:
		int32 m_duration; // Set to -1 for infinite duration
	public:
		bool active = 1;
	public:
		StatusEffect(int32 duration)
		: m_duration(duration) 
		{}
		
		virtual void effect(Stats& stats) = 0;

		// Effects with m_duration = -1 are infinite.
		void manageDuration()
		{
			if (m_duration == 0)
				active = 0;

			if (m_duration > 0)
				m_duration--;
		}
	};

	// All stats related to health
	class HealthBoost : public StatusEffect
	{
	public:
		int32 max_health;
		int32 health_regen;
	public:
		HealthBoost(int32 duration, int32 maxHealth, int32 healthregen = 0)
		: StatusEffect(duration)
		, m_maxHealth(maxHealth)
		, m_healthRegen(healthregen)
		{}
		
		void effect(Stats& stats) override
		{
			stats.max_health += m_maxHealth;
			stats.health_regen += m_healthRegen;
		}
	};

	// All stats related to defense
	class Defense : public StatusEffect
	{
	public:
		int32 armor;
		int32 magic_resist;
	public:
		Defense(int32 duration, int32 armor, int32 mr)
			: StatusEffect(duration)
			, m_armor(armor)
			, m_magicResist(mr)
		{}

		void effect(Stats& stats) override
		{
			stats.armor += m_armor;
			stats.magic_resist += m_magicResist;
		}
	};
}
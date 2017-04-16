#pragma once

#include "../util/Types.h"

namespace Entity
{
	// Do not change entities' stats directly. Use StatusEffects.
	struct Stats
	{
		// Only change health directly
		int32 health, max_health, health_regen, armor, magic_resist;

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
		StatusEffect(int32 duration);

		virtual void effect(Stats& stats) = 0;

		// Effects with m_duration = -1 are infinite.
		void manageDuration();
	};

	class HealthBoost : public StatusEffect
	{
	public:
		int32 max_health;
		int32 health_regen;
	public:
		HealthBoost(int32 duration, int32 maxHealth, int32 healthregen = 0);

		void effect(Stats& stats) override;
	};

	class Defense : public StatusEffect
	{
	public:
		int32 armor;
		int32 magic_resist;
	public:
		Defense(int32 duration, int32 armor, int32 mr);

		void effect(Stats& stats) override;
	};
}

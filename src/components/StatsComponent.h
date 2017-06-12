#pragma once

#include "Component.h"

namespace Components
{
#pragma region STATS
	struct Stats
	{
		int32 health, max_health, health_regen, armor, magic_resist;
	};
#pragma endregion

#pragma region STATUS_EFFECT

	// A status effect changes values in the stats component over time
	class Buff
	{
	public:
		Buff(int32 duration);
		virtual ~Buff() = default;

		bool active = 1;

		void manageDuration();
		virtual void effect(Stats& stats) = 0;

	private:
		int32 m_duration;
	};

	class HealthBoost : public Buff
	{
	public:
		int32 max_health;
		int32 health_regen;

		HealthBoost(int32 duration, int32 maxHealth, int32 healthregen = 0);

		void effect(Stats& stats) override;
	};

	class Defense : public Buff
	{
	public:
		int32 armor;
		int32 magic_resist;

		Defense(int32 duration, int32 armor, int32 mr);

		void effect(Stats& stats) override;
	};

#pragma endregion

	class StatsComponent : public Component
	{
	public:
		Stats stats;
		std::vector<std::shared_ptr<Buff>> active_buffs;

	public:
		StatsComponent();
		StatsComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override { return std::make_unique<StatsComponent>(*this); }

		static const uint ID = ComponentID::Stats;
	};
}

#pragma once

#include "Component.h"

#include "../../util/json.hpp"

#include <vector>
#include <memory>

namespace Entity
{
#pragma region STATS
    struct Stats
    {
        int32 health, max_health, health_regen, armor, magic_resist;
    };
#pragma endregion

#pragma region STATUS_EFFECT

    // A status effect changes values in the stats component over time
    class StatusEffect
    {
    public:
        StatusEffect(int32 duration);

        bool active = 1;

        void manageDuration();
        virtual void effect(Stats& stats) = 0;

    private:
        int32 m_duration;
    };

    class HealthBoost : public StatusEffect
    {
    public:
        int32 max_health;
        int32 health_regen;

        HealthBoost(int32 duration, int32 maxHealth, int32 healthregen = 0);

        void effect(Stats& stats) override;
    };

    class Defense : public StatusEffect
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
        std::vector<std::shared_ptr<StatusEffect>> active_effects;

        StatsComponent();
        StatsComponent(nlohmann::json json);

        static const int ID = 8;
    };

}

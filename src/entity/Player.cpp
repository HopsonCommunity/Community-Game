#include "Player.h"

namespace Framework
{
	Player::Player()
	: Entity(100, 100)
	{
		constexpr static auto MAX_HEALTH = 800;

		addEffect(std::make_unique<HealthBoost>(DURATION_INFINITE, MAX_HEALTH, 0));
		m_health = MAX_HEALTH;

		addEffect(std::make_unique<Defense>(20 * 5, 20, 30));
	}

	void Player::applyDamage(const Damage& dmg)
	{
	}
}
#include "Player.h"

namespace Framework
{
	Player::Player()
	: Entity(100, 100)
	, m_moveState(IDLE)
	{
		constexpr static auto MAX_HEALTH = 800;

		addEffect(std::make_unique<HealthBoost>(DURATION_INFINITE, MAX_HEALTH, 0));
		m_health = MAX_HEALTH;

		addEffect(std::make_unique<Defense>(20 * 5, 20, 30));
	}

	void Player::input()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			velocity.x += 0.1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			velocity.x -= 0.1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			velocity.y -= 0.1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			velocity.y += 0.1;
	}

	void Player::update()
	{
		Entity::update();


	}

	void Player::applyDamage(const Damage& dmg)
	{
		int32 real_dmg = dmg.amount;

		///@TODO Better algorithm to calculate defenses
		if (dmg.source == DamageSource::Physical)
			real_dmg = m_stats.armor / 100 * dmg.amount;

		if (dmg.source == DamageSource::Magic)
			real_dmg = m_stats.magic_resist / 100 * dmg.amount;

		m_health -= real_dmg;
	}
}
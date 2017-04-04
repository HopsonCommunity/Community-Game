#include "Player.h"

#include "../Application.h"

namespace Framework
{
	Player::Player()
	{
		auto hb = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);
		addEffect(hb);
		m_health = 800;

		hb->max_health = 7200;

		addEffect(std::make_shared<Defense>(20 * 5, 20, 30));
	}

	void Player::update(float dt)
	{
		int xdir = 0;
		int ydir = 0;

		if (Application::instance->inputPressed(MOVE_UP))
			ydir--;
		if (Application::instance->inputPressed(MOVE_DOWN))
			ydir++;
		if (Application::instance->inputPressed(MOVE_LEFT))
			xdir--;
		if (Application::instance->inputPressed(MOVE_RIGHT))
			xdir++;

		if (xdir > 0)
		{
			if (ydir > 0)
				walk(DOWN_RIGHT);
			else if (ydir < 0)
				walk(UP_RIGHT);
			else
				walk(RIGHT);
		}
		else if (xdir < 0)
		{
			if (ydir > 0)
				walk(DOWN_LEFT);
			else if (ydir < 0)
				walk(UP_LEFT);
			else
				walk(LEFT);
		}
		else
		{
			if (ydir > 0)
				walk(DOWN);
			else if (ydir < 0)
				walk(UP);
		}
		std::cout << m_stats.max_health << std::endl;

		velocity *= 0.5f;
	}

	void Player::applyDamage(const Damage& dmg)
	{
		float damage_thing;

		if (dmg.source == DamageSource::Physical)
			damage_thing = dmg.amount / (dmg.amount - m_stats.armor);

		if (dmg.source == DamageSource::Magic)
			damage_thing = dmg.amount / (dmg.amount - m_stats.magic_resist);

		m_health -= dmg.amount * damage_thing;
	}
}
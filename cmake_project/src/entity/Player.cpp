#include "Player.h"

#include "../Application.h"

namespace Framework
{

	constexpr static auto MAX_HEALTH = 800;

	Player::Player()
	{
		addEffect(std::make_unique<HealthBoost>(DURATION_INFINITE, MAX_HEALTH, 0));
		m_health = MAX_HEALTH;

		addEffect(std::make_unique<Defense>(20 * 5, 20, 30));
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

		applyVelocity(dt);
	}

	void Player::applyDamage(const Damage& dmg)
	{
	}
}
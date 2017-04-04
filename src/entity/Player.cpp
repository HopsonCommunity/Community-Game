#include "Player.h"

#include "../Application.h"

namespace Framework
{
	Player::Player()
	{
		sprite = sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64));

		m_animator.addAnim("idle", 0, 0, 32, 8, 7);
		m_animator.addAnim("run", 0, 64, 32, 8, 14);
		m_animator.setAnim("idle");
		m_speedWalk = 150;

		auto hb = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);
		addEffect(hb);
		m_health = 800;

		hb->max_health = 7200;

		addEffect(std::make_shared<Defense>(20 * 5, 20, 30));

		sf::Image* m_animationAtlas = new sf::Image();
		m_animationAtlas->loadFromFile("res/textures/player_modelDefault.png");
		m_animation = new Graphics::AnimatedSprite(m_animationAtlas, 32, 7, 5);
	}

	Player::~Player()
	{
		delete m_animation;
	}

	void Player::update(float dt)
	{
		Creature::update(dt);

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

		m_animator.setAnim(m_walking ? "run" : "idle");
		applyVelocity(dt);
	}

	void Player::applyDamage(const Damage& dmg)
	{
		float damage_thing = 1; // Never code late at night

		if (dmg.source == DamageSource::Physical)
			damage_thing = dmg.amount / (dmg.amount - m_stats.armor);

		if (dmg.source == DamageSource::Magic)
			damage_thing = dmg.amount / (dmg.amount - m_stats.magic_resist);

		m_health -= dmg.amount * damage_thing;
	}
}
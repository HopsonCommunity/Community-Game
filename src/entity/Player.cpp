#include "Player.h"

#include "../Application.h"

#include "component/Components.h"

namespace Framework
{
	Player::Player()
	: Entity()
	{
		addComponent(new Framework::SpriteComponent(sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64))));
		addComponent(new Framework::PositionComponent({ -20, -20 }));
		addComponent(new Framework::VelocityComponent());

		m_animator.addAnimation("idle", 0, 0, 32, 8, 7);
		m_animator.addAnimation("run", 0, 64, 32, 8, 14);
		m_animator.setAnimation("idle");
		m_speedWalk = 150;
		
		auto hb = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);
	
		addComponent(new StatsComponent());
		StatsComponent* c_stats = getComponent<StatsComponent>();
		
		c_stats->addEffect(hb);
		c_stats->stats.health = 800;

		hb->max_health = 7200;

		c_stats->addEffect(std::make_shared<Defense>(20 * 5, 20, 30));
	}

	void Player::update(const Timestep& ts)
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

		m_direction = Application::instance->mousePosition().x > Application::instance->getWindow().getSize().x / 2;
		
		m_animator.setAnimation(m_walking ? "run" : "idle");

		SpriteComponent* c_sprite = getComponent<SpriteComponent>();
		m_animator.update(ts, c_sprite->sprite);
	
		c_sprite->sprite.setScale(static_cast<float>(m_direction ? 1 : -1), static_cast<float>(1));
		
		m_walking = false;
	}

	void Player::walk(Direction dir)
	{
		VelocityComponent* c_vel = getComponent<VelocityComponent>();
		if (!c_vel)
			return;

		switch (dir)
		{
		case UP:
			c_vel->velocity.y -= m_speedWalk;
			break;
		case UP_RIGHT:
			c_vel->velocity.x += m_speedWalk * 0.7071067f;
			c_vel->velocity.y -= m_speedWalk * 0.7071067f;
			break;
		case RIGHT:
			c_vel->velocity.x += m_speedWalk;
			break;
		case DOWN_RIGHT:
			c_vel->velocity.x += m_speedWalk * 0.7071067f;
			c_vel->velocity.y += m_speedWalk * 0.7071067f;
			break;
		case DOWN:
			c_vel->velocity.y += m_speedWalk;
			break;
		case DOWN_LEFT:
			c_vel->velocity.x -= m_speedWalk * 0.7071067f;
			c_vel->velocity.y += m_speedWalk * 0.7071067f;
			break;
		case LEFT:
			c_vel->velocity.x -= m_speedWalk;
			break;
		case UP_LEFT:
			c_vel->velocity.x -= m_speedWalk * 0.7071067f;
			c_vel->velocity.y -= m_speedWalk * 0.7071067f;
			break;
		}
		m_walking = true;
	}
}
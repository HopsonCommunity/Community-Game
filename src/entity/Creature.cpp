#include "Creature.h"

#include "../Application.h"
#include "physics/TileCollision.h"

namespace Framework
{

	Creature::Creature()
		: m_animator(&sprite),
		m_hitBox(sf::FloatRect(-8, -8, 16, 16))
	{}

	void Creature::update(const Timestep& ts)
	{
		m_animator.update(ts);
		m_direction = Application::instance->mousePosition().x > Application::instance->getWindow().getSize().x / 2;
		sprite.setScale(static_cast<float>(m_direction ? 1 : -1), static_cast<float>(1));
		m_walking = false;
	}

	void Creature::applyVelocity(float dt)
	{
		auto colliding = Physics::tileCollision(position, velocity, m_hitBox, *level, dt);

		if (!colliding.first)
			position.x += velocity.x * dt;
		if (!colliding.second)
			position.y += velocity.y * dt;

		velocity.x = 0;
		velocity.y = 0;
	}

	void Creature::walk(Direction dir)
	{
		switch (dir)
		{
		case UP:
			velocity.y -= m_speedWalk;
			break;
		case UP_RIGHT:
			velocity.x += m_speedWalk * 0.7071067f;
			velocity.y -= m_speedWalk * 0.7071067f;
			break;
		case RIGHT:
			velocity.x += m_speedWalk;
			break;
		case DOWN_RIGHT:
			velocity.x += m_speedWalk * 0.7071067f;
			velocity.y += m_speedWalk * 0.7071067f;
			break;
		case DOWN:
			velocity.y += m_speedWalk;
			break;
		case DOWN_LEFT:
			velocity.x -= m_speedWalk * 0.7071067f;
			velocity.y += m_speedWalk * 0.7071067f;
			break;
		case LEFT:
			velocity.x -= m_speedWalk;
			break;
		case UP_LEFT:
			velocity.x -= m_speedWalk * 0.7071067f;
			velocity.y -= m_speedWalk * 0.7071067f;
				//0.7071067811865475f//
			break;
		}
		m_walking = true;
	}

}

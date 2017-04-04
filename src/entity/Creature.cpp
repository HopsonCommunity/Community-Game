#include "Creature.h"

#include "../Application.h"
#include "physics/TileCollision.h"

namespace Framework
{

	Creature::Creature()
		: m_animator(&sprite),
		m_hitBox(sf::FloatRect(-8, -8, 16, 16))
	{}

	void Creature::update(float dt)
	{
		m_animator.update(dt);
		m_direction = Application::instance->mousePosition().x > Application::instance->getWindow().getSize().x / 2;
		sprite.setScale(m_direction ? 1 : -1, 1);
		m_walking = false;
	}

	void Creature::applyVelocity(float dt)
	{
		bool* colliding = Physics::tileCollision(position, velocity, m_hitBox, *level, dt);

		if (!colliding[0])
			position.x += velocity.x * dt;
		if (!colliding[1])
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
			velocity.x += m_speedWalk * 0.7071067811865475;
			velocity.y -= m_speedWalk * 0.7071067811865475;
			break;
		case RIGHT:
			velocity.x += m_speedWalk;
			break;
		case DOWN_RIGHT:
			velocity.x += m_speedWalk * 0.7071067811865475;
			velocity.y += m_speedWalk * 0.7071067811865475;
			break;
		case DOWN:
			velocity.y += m_speedWalk;
			break;
		case DOWN_LEFT:
			velocity.x -= m_speedWalk * 0.7071067811865475;
			velocity.y += m_speedWalk * 0.7071067811865475;
			break;
		case LEFT:
			velocity.x -= m_speedWalk;
			break;
		case UP_LEFT:
			velocity.x -= m_speedWalk * 0.7071067811865475;
			velocity.y -= m_speedWalk * 0.7071067811865475;
			break;
		}
		m_walking = true;
	}

}
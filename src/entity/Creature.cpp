#include "Creature.h"

namespace Framework
{

	Creature::Creature()
	{}

	void Creature::walk(Direction dir)
	{
		m_direction = dir;

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
	}

}
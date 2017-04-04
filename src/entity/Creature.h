#pragma once

#include "Entity.h"
#include "animation/Animator.h"

namespace Framework
{

	enum Direction
	{
		UP = 0,
		UP_RIGHT = 1,
		RIGHT = 2,
		DOWN_RIGHT = 3,
		DOWN = 4,
		DOWN_LEFT = 5,
		LEFT = 6,
		UP_LEFT = 7
	};

	class Creature : public Entity
	{
	protected:
		float m_speedWalk = 80;
		bool m_direction;
		bool m_walking;
		Animator m_animator;

	public:
		Creature();

	protected:
		void update(float dt) override;

		void walk(Direction dir);
	};

}

#pragma once

#include "Entity.h"
#include "animation/Animator.h"

namespace Framework
{
	class Player : public Entity
	{
	public:
		Player();

		void update(const Timestep& ts) override;
	};
}
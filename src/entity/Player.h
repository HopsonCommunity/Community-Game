#pragma once

#include "Entity.h"

namespace Framework
{
	class Player : public Entity
	{
	public:
		Player();

		void update(const Timestep& ts) override;
	};
}
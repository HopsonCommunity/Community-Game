#pragma once

#include "../Creature.h"

namespace Framework
{
	class Zombie : public Creature
	{
	public:
		Zombie();

		void update(const Timestep& ts) override;
	};
}
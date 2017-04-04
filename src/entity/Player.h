#pragma once

#include "Creature.h"
#include "../ui/Label.h"

namespace Framework
{
	class Player : public Creature
	{
	private:
	public:
		Player();

		void update(const Timestep& ts) override;
		void applyDamage(const Damage& dmg) override;
	};
}
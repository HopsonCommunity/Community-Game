#pragma once

#include "Creature.h"

namespace Framework
{
	class Player : public Creature
	{
	public:
		Player();

		void update(float dt) override;
		void applyDamage(const Damage& dmg) override;
	};
}
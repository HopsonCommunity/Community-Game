#pragma once

#include "Entity.h"

namespace Framework
{
	class Player : public Entity 
	{
	public:
		Player();

		void applyDamage(const Damage& dmg) override;
	};
}
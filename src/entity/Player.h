#pragma once

#include "Entity.h"

namespace Framework
{
	class Player : public Entity 
	{
		void applyDamage(const Damage& dmg) override;
	};
}
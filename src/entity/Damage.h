#pragma once

#include "../util/Types.h"

namespace Framework
{
	// Knowing the damage source is useful!
	enum class DamageSource : byte
	{
		Physical = 0,
		Magic = 1,
		True = 2 // ignores defenses
	};

	// Damage struct holding some data about damage instances.
	struct Damage
	{
		DamageSource source;
		int32 amount;
	};

	class IDamageable
	{
	public:
		virtual void applyDamage(const Damage& dmg) = 0;
	};
}
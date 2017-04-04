#pragma once

#include "../util/Types.h"

namespace Framework
{
	// Knowing the damage source WILL be useful later if there are stats, buffs
	// or potions reducing specific types of dmg. (eg. Fire Resist or Magic Resist)
	//
	// (True damage ignores defences.)
	enum class DamageSource : byte
	{
		Physical = 0,
		Magic = 1,
		True = 2
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
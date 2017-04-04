#pragma once

#include "Creature.h"
#include "../graphics/AnimatedSprite.h"

namespace Framework
{
	class Player : public Creature
	{
	private:
		Graphics::AnimatedSprite* m_animation;
	public:
		Player();
		~Player();

		void update(float dt) override;
		void applyDamage(const Damage& dmg) override;
	};
}
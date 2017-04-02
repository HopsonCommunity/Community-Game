#pragma once

#include "Entity.h"

namespace Framework
{
	class Player : public Entity 
	{
	public:
		enum MoveState : byte
		{
			IDLE, WALK
		};
	private:
		MoveState m_moveState;
	public:
		Player();
		
		void applyDamage(const Damage& dmg) override;
	
		void input();
		virtual void update();
	};
}
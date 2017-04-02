#pragma once

#include "Entity.h"

class Application;

namespace Framework
{
	class Player : public Entity 
	{
	public:
		enum FaceDirection : byte
		{
			RIGHT, LEFT
		};

		enum MoveState : byte
		{
			IDLE, WALK
		};
	private:
		sf::Image m_textureAtlas;
		sf::Texture* m_currentFrame;

		MoveState m_moveState;
		FaceDirection m_faceDir;

		int m_frameCounter = 0;
		int m_frame = 0;
	public:
		Player();
		~Player();

		void applyDamage(const Damage& dmg) override;
	
		void input(Application* app);
		void update(float dt);
	};
}
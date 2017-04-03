#pragma once

#include "Entity.h"

class Application;

namespace Framework
{
	class Player : public Entity
	{
        public:
            enum class FaceDirection : byte
            {
                Right,
                Left,
            };

            enum class MoveState : byte
            {
                Idle,
                Walk
            };

            Player();
            ~Player();

            void applyDamage(const Damage& dmg) override;

            void input(Application* app);
            void update(float dt);

        private:
            sf::Image m_textureAtlas;
            sf::Texture* m_currentFrame;

            MoveState m_moveState    = MoveState::Idle;
            FaceDirection m_faceDir;

            int m_frameCounter = 0;
            int m_frame = 0;
	};
}

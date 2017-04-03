#pragma once

#include "../util/Types.h"

#include <SFML/Graphics.hpp>

#include "Damage.h"
#include "Stats.h"

#include <memory>

namespace Framework
{
	class Entity : public IDamageable
	{
        public:
            Entity();

			// Default entity doesn't care about damage source.
			virtual void applyDamage(const Damage& dmg) override;

            int32 getHealth();
			const Stats& getStats();

			virtual void update(float dt); 
            virtual void render(sf::RenderWindow& window);

			void addEffect(std::unique_ptr<StatusEffect> effect);

        protected:
			int32 m_health;
			Stats m_stats;

			void applyVelocity(float dt);
		private:
			std::vector<std::unique_ptr<StatusEffect>> m_activeEffects;

        public:
            ///@TODO Public for now. Change later
			sf::Vector2f position;
            sf::Vector2f velocity;
			sf::Sprite sprite;
	};
}

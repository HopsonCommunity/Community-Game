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

			void addEffect(std::shared_ptr<StatusEffect> effect);
        protected:
			int32 m_health;
			Stats m_stats;
		private:
			std::vector<std::shared_ptr<StatusEffect>> m_activeEffects;
        public:
			sf::Vector2f position;
            sf::Vector2f velocity;
			sf::RectangleShape shape;
	};
}

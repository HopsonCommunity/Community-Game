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
            Entity(float width, float height);

			// Default entity doesn't care about damage source.
			virtual void applyDamage(const Damage& dmg) override;

            int32 getHealth();
			const Stats& getStats();

			virtual void update(); 
            virtual void render(sf::RenderWindow& window);

			void addEffect(std::unique_ptr<StatusEffect> effect);

            // Returns entity's shape. Use to apply transormations.
            sf::RectangleShape& getShape();
        protected:
			int32 m_health;
			Stats m_stats;
		private:
			std::vector<std::unique_ptr<StatusEffect>> m_activeEffects;

            sf::RectangleShape m_shape;
        public:
            ///@TODO Public for now. Change later
            sf::Vector2f velocity;
	};
}

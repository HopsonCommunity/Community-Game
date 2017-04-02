#pragma once

#include "../util/Types.h"

#include <SFML/Graphics.hpp>

#include "Damage.h"

namespace Framework
{
	class Entity : public IDamageable
	{
        public:
            Entity(float width, float height);

            /*
                Default entity doesn't care about damage sources. (He just takes it)
                Later other entites (eg: Player) will care tho. Since they will have stats and buffs
            */
			virtual void applyDamage(const Damage& dmg) override;

            int32 getHealth();

            void render(sf::RenderWindow& window);

            // Returns entity's shape. Use to apply transormations.
            sf::RectangleShape& getShape();
        private:
            int32 m_health;

            sf::RectangleShape m_shape;
        public:
            ///@TODO Public for now. Change later
            sf::Vector2f velocity;
	};
}

#pragma once

#include "../util/Types.h"

#include <SFML/Graphics.hpp>
#include <memory>

#include "Damage.h"
#include "Stats.h"

#include "../level/Level.h"

namespace Framework
{

	class Entity : public IDamageable
	{
	private:
		std::vector<std::shared_ptr<StatusEffect>> m_activeEffects;

	protected:
		int32 m_health;
		Stats m_stats;

	public:
		///@TODO Public for now. Change later
		Level::Level* level;
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Sprite sprite;

    public:
        Entity();

		virtual void update(const Timestep& ts);
		virtual void render(sf::RenderWindow& window);

		virtual void applyVelocity(float dt);
		// Default entity doesn't care about damage source.
		virtual void applyDamage(const Damage& dmg) override;
		void addEffect(std::shared_ptr<StatusEffect> effect);    

        int32 getHealth();
		const Stats& getStats();
	};
}

#include "Entity.h"

#include <iostream>

namespace Framework
{
	Entity::Entity(float width, float height)
    : m_shape({ width, height })
	{
	}

	void Entity::applyDamage(const Damage& dmg)
	{
		m_health -= dmg.amount;
	}

	int32 Entity::getHealth()
	{
		return m_health;
	}

	const Stats& Entity::getStats()
	{
		return m_stats;
	}

	void Entity::update()
	{
		m_stats.reset();
		for (auto& effect : m_activeEffects)
		{
			if (effect->active)
				effect->effect(m_stats);
			effect->manageDuration();
		}

		// std::cout << "max_health: " << m_stats.max_health << " health_regen: " << m_stats.health_regen << " armor: " << m_stats.armor << " magic_resist: " << m_stats.magic_resist << std::endl;
	}

	void Entity::render(sf::RenderWindow& window)
	{
		window.draw(m_shape);
	}

	void Entity::addEffect(std::unique_ptr<StatusEffect> effect)
	{
		m_activeEffects.push_back(std::move(effect));
	}

	sf::RectangleShape& Entity::getShape()
	{
		return m_shape;
	}
}

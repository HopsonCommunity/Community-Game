#include "Entity.h"

#include <iostream>
#include "../level/LevelRenderer.h"

namespace Framework
{
	Entity::Entity()
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

	void Entity::update(float dt)
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
		Level::LevelRenderer::renderEntitySprite(position.x - sprite.getTextureRect().width / 2, position.y - sprite.getTextureRect().height, sprite);
	}

	void Entity::applyVelocity(float dt)
	{
		position.x += velocity.x * dt;
		position.y += velocity.y * dt;
		velocity.x = 0;
		velocity.y = 0;
	}

	void Entity::addEffect(std::unique_ptr<StatusEffect> effect)
	{
		m_activeEffects.push_back(std::move(effect));
	}

}

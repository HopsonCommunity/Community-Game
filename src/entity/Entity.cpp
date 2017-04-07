#include "Entity.h"

#include "component/Components.h"

#include "../util/Random.h"

namespace Framework
{
	Entity::Entity()
	: m_ID(Random::uint64InRange(0, 18446744073709551614))
	{
	}

	Entity::Entity(sf::Vector2f& position, sf::Sprite& sprite)
	: m_ID(Random::uint64InRange(0, 18446744073709551614))
	{
		addComponent(new PositionComponent(position));
		addComponent(new SpriteComponent(sprite));
	}

	void Entity::addComponent(Component* component)
	{
		if (component->getType())
			m_components[component->getType()] = component;
	}
}

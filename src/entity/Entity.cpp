#include "Entity.h"

#include "component/Components.h"

#include "../util/Random.h"

namespace Framework
{
	Entity::Entity()
	: m_ID(Random::uint64InRange(0, 18446744073709551614ULL))
	{
	}

	Entity::Entity(sf::Vector2f& position, sf::Sprite& sprite)
	: m_ID(Random::uint64InRange(0, 18446744073709551614ULL))
	{
		addComponent(std::make_unique<PositionComponent>(position));
		addComponent(std::make_unique<SpriteComponent>(sprite));
	}

	void Entity::addComponent(std::unique_ptr<Component> component)
	{
		if (component->getType())
			m_components[component->getType()] = std::move(component);
	}
}

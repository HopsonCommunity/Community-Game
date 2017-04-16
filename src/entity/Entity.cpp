#include "Entity.h"

#include "../util/Random.h"

namespace Entity
{
	Entity::Entity()
	: m_ID(Random::uint64InRange(0, 18446744073709551614ULL))
	{
	}

	void Entity::addComponent(std::unique_ptr<Component> component)
	{
		if (component->getType())
			m_components[component->getType()] = std::move(component);
	}
}

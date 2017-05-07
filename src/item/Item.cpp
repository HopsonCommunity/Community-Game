#include "Item.h"
#include "../maths/Random.h"

namespace Item
{
	Item::Item(Entity::Entity* owningEntity)
		: m_ID(Random::uint64InRange(0, 18446744073709551614ULL))
		, m_owningEntity(owningEntity)
	{

	}

	void Item::addComponent(std::unique_ptr<Component> component)
	{
		if (component->getType())
			m_components[component->getType()] = std::move(component);
	}
}

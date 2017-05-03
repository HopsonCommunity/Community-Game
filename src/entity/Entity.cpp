#include "Entity.h"

namespace Entity
{
	Entity::Entity()
		: m_ID(0)
	{
	}

	Entity::Entity(uint64 ID)
		: m_ID(ID)
	{
	}

	std::unique_ptr<Entity> Entity::clone(uint64 id)
	{
		std::unique_ptr<Entity> cloned = std::make_unique<Entity>(id);

		for (auto& pair : m_components)
			cloned->m_components[pair.first] = pair.second->clone();

		return cloned;
	}
}
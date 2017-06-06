#include "Item.h"

namespace Item
{
	Item::Item()
		: m_ID(0)
		, m_owningEntity(nullptr)
	{}

	Item::Item(Entity::Entity* owningEntity, uint64 ID)
		: m_ID(ID)
		, m_owningEntity(owningEntity)
	{}

	std::unique_ptr<Item> Item::clone(uint64 id)
	{
		std::unique_ptr<Item> cloned = std::make_unique<Item>(nullptr, id);

		for (auto& pair : m_components)
			cloned->m_components[pair.first] = pair.second->clone();

		return cloned;
	}


}

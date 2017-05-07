#include "InventoryComponent.h"

namespace Entity
{
	InventoryComponent::InventoryComponent(std::vector<std::shared_ptr<Item::Item> > items)
		: items(items)
	{}

	InventoryComponent::InventoryComponent(nlohmann::json json) {
		for (int i=0; i < json.size(); i++)
		{
			items.push_back(Item::ItemFactory::createItem(json));
		}
	}
}

#include "InventoryComponent.h"

namespace Entity
{
	InventoryComponent::InventoryComponent(std::vector<std::shared_ptr<Item::Item> > items)
		: items(items)
	{}

	InventoryComponent::InventoryComponent(nlohmann::json json) {

	}
}

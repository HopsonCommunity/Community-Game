#include "InventoryComponent.h"
#include "../../item/ItemFactory.h"

namespace Framework
{
	InventoryComponent::InventoryComponent(std::vector<std::unique_ptr<Item::Item> > items)
		: items(items)
	{}

	InventoryComponent::InventoryComponent(nlohmann::json json) {

	}

	ComponentType* InventoryComponent::getStaticType()
	{
		static ComponentType type({ "Inventory" });
		return &type;
	}

	ComponentType* InventoryComponent::getType() const
	{
		return getStaticType();
	}
}

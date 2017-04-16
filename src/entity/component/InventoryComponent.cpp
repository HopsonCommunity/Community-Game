#include "InventoryComponent.h"
#include "../../item/ItemFactory.h"

namespace Framework
{
	InventoryComponent::InventoryComponent(std::vector<std::unique_ptr<Item::Item> > items)
		: items(items)
	{}

	InventoryComponent::InventoryComponent(nlohmann::json json) {
		for (int i=0; i < json.size(); i++)
		{
			items.push_back(Item::ItemFactory::createItem(json));
		}
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

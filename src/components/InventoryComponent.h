#pragma once

#include "Component.h"

#include "../item/Item.h"

namespace Components 
{
    class InventoryComponent : public Component 
	{
	public:
		std::vector<std::unique_ptr<Item::Item>> items;

    public:
        InventoryComponent();
        InventoryComponent(nlohmann::json);

        static const uint ID = ComponentID::Inventory;
    };
}

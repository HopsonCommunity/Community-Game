#pragma once

#include "Component.h"

#include "../item/Item.h"

namespace Entity 
{
    class InventoryComponent : public Component 
	{
    public:
        InventoryComponent();
        InventoryComponent(nlohmann::json);

        std::vector<std::unique_ptr<Item::Item>> items;

        static const uint ID = ComponentID::Inventory;
    };
}

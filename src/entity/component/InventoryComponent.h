#pragma once

#include <vector>
#include <memory>
#include "../../item/Item.h"
#include "../../util/json.hpp"
#include "Component.h"

namespace Entity {
    class InventoryComponent : public Component {
    public:
        InventoryComponent();
        InventoryComponent(nlohmann::json);

        std::vector<std::unique_ptr<Item::Item> > items;

        static const uint ID = ComponentID::Inventory;
    };
}

#pragma once

#include <vector>
#include <memory>
#include "../../item/Item.h"
#include "../../util/json.hpp"
#include "Component.h"
#include "../../item/ItemFactory.h"

namespace Entity {
    class InventoryComponent : public Component {
    public:
        std::vector<std::shared_ptr<Item::Item> > items;
    public:
        InventoryComponent(std::vector<std::shared_ptr<Item::Item> > items);
        InventoryComponent(nlohmann::json);

        static const int ID = 100;

    };
}

#pragma once

#include <vector>
#include <memory>
#include "../../item/Item.h"
#include "../../util/json.hpp"

namespace Framework {
    class InventoryComponent : Component {
    public:
        InventoryComponent(std::vector<std::unique_ptr<Item::Item> > items);
        InventoryComponent(nlohmann::json);

        std::vector<std::unique_ptr<Item::Item> > items;

        static ComponentType* getStaticType();
        virtual ComponentType* getType() const override;
    };
}

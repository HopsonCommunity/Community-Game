#pragma once

#include "Item.h"
#include "../util/json.hpp"

namespace Item
{
    class ItemFactory
    {
    public:
        static std::unique_ptr<Item> createItem(const std::string& item);
        static std::unique_ptr<Item> createItem(nlohmann::json json);
    };
}

#pragma once

#include "Item.h"

namespace Item
{
    class ItemFactory
    {
    public:
        static std::unique_ptr<Item> createItem(const std::string& item);
    };
}
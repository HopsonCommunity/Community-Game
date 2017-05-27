#pragma once

#include "Item.h"
#include "../util/json.hpp"

namespace Item
{
    class ItemFactory
    {
    public:
        ItemFactory();

        std::unique_ptr<Item> createItem(std::string name);

    private:
        void createTemplate(std::string filePath);

        std::unordered_map<std::string, std::unique_ptr<Item>> m_templates;
        uint64 m_lastID;
    };
}

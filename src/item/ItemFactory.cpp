#include "ItemFactory.h"
#include "../util/json.hpp"

namespace Item
{
	std::unique_ptr<Item> ItemFactory::createItem(const std::string& name)
	{
		auto item = std::make_unique<Item>(nullptr);

		return item;
	}
	std::unique_ptr<Item> ItemFactory::createItem(nlohmann::json json)
	{

		///@TODO: Create json interpreter
		auto item = std::make_unique<Item>(nullptr);

		return item;
	}
}

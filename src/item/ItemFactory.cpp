#include "ItemFactory.h"

namespace Item
{
	std::unique_ptr<Item> ItemFactory::createItem(const std::string& name)
	{
		auto item = std::make_unique<Item>();

		return item;
	}
}
#include "ItemFactory.h"
#include "../util/FileUtil.h"
#include "../util/json.hpp"

namespace Item
{
	std::unique_ptr<Item> ItemFactory::createItem(const std::string& filePath)
	{
		std::string source = getFileContents("res/items/" + filePath + ".json");
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Item> item = std::make_unique<Item>();

		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (int i = 0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];
			///@TODO: All components "if's"
		}
		return item;
	}
}

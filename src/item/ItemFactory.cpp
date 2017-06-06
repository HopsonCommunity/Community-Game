#include "ItemFactory.h"

#include "../util/FileUtil.h"

#include "../components/SpriteComponent.h"

namespace Item
{
	ItemFactory::ItemFactory() : m_lastID(0)
	{

	}

	std::unique_ptr<Item> ItemFactory::createItem(std::string name) {
		if (m_templates.find(name) == m_templates.end())
			createTemplate(name);

		return m_templates.find(name)->second->clone(++m_lastID);
	}

	void ItemFactory::createTemplate(std::string filePath)
	{
		std::string source = getFileContents("res/items" + filePath);
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Item> item = std::make_unique<Item>();

		std::vector<nlohmann::json> componentsJSON = json["components"];

		for (unsigned int i=0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];

			if (componentJSON["componentType"].get<std::string>() == "Sprite")
				item->addComponent<Entity::SpriteComponent>(std::make_unique<Entity::SpriteComponent>(componentJSON));
		}
	}
}

#include "EntityFactory.h"

#include "../components/Components.h"

#include "../app/Application.h"
#include "../util/FileUtil.h"

namespace Entity
{
	EntityFactory::EntityFactory()
		: m_lastID(0)
	{
	}

	std::unique_ptr<Entity> EntityFactory::createEntity(std::string name)
	{
		if (m_templates.find(name) == m_templates.end())
			createTemplate(name);

		return m_templates.find(name)->second->clone(++m_lastID);
	}

	void EntityFactory::createTemplate(std::string filePath) 
	{
		std::string source = getFileContents("res/entities/" + filePath);
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (uint i = 0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];

			if (componentJSON["componentType"].get<std::string>() == "Physics")
				entity->addComponent<PhysicsComponent>(std::make_unique<PhysicsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Sprite")
				entity->addComponent<SpriteComponent>(std::make_unique<SpriteComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Stats")
				entity->addComponent<StatsComponent>(std::make_unique<StatsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Light")
				entity->addComponent<LightComponent>(std::make_unique<LightComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Script")
				entity->addComponent<ScriptComponent>(std::make_unique<ScriptComponent>(componentJSON));
		}

		m_templates[filePath] = std::move(entity);
	}
}
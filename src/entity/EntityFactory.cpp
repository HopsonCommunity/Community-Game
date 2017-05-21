#include "EntityFactory.h"

#include "component/Components.h"

#include "../app/Application.h"
#include "../util/FileUtil.h"
#include "../util/json.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

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

	std::unique_ptr<Entity> EntityFactory::createHostileEntity()
	{
		int hostileMob = Random::intInRange(0, m_hostileMobs.size() - 1);

		return createEntity(m_hostileMobs[hostileMob]);
	}

	void EntityFactory::createTemplate(std::string filePath) 
	{
		std::string source = getFileContents("res/entities/" + filePath);
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (unsigned int i = 0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];

			if (componentJSON["componentType"].get<std::string>() == "AI")
				entity->addComponent<AIComponent>(std::make_unique<AIComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Animator")
				entity->addComponent<AnimatorComponent>(std::make_unique<AnimatorComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Physics")
				entity->addComponent<PhysicsComponent>(std::make_unique<PhysicsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Move")
				entity->addComponent<MoveComponent>(std::make_unique<MoveComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Player")
				entity->addComponent<PlayerComponent>(std::make_unique<PlayerComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Sprite")
				entity->addComponent<SpriteComponent>(std::make_unique<SpriteComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Stats")
				entity->addComponent<StatsComponent>(std::make_unique<StatsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Hostile")
				entity->addComponent<HostileComponent>(std::make_unique<HostileComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Light")
				entity->addComponent<LightComponent>(std::make_unique<LightComponent>(componentJSON));
		}

		if (entity->getComponent<HostileComponent>())
			m_hostileMobs.push_back(filePath);

		m_templates[filePath] = std::move(entity);
	}
}
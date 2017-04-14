#include "EntityFactory.h"

#include <fstream>

#include "../Application.h"
#include "component/Components.h"
#include "../util/FileUtil.h"

namespace Framework 
{
	std::unique_ptr<Framework::Entity> EntityFactory::createEntity(std::string filePath) {
		
		std::string source = getFileContents("res/entities/" + filePath + ".json");
		nlohmann::json json = nlohmann::json::parse(source.c_str());

		std::unique_ptr<Framework::Entity> entity = std::make_unique<Framework::Entity>();
		
		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (unsigned int i = 0; i < componentsJSON.size(); i++)
		{
			nlohmann::json componentJSON = componentsJSON[i];

			if (componentJSON["componentType"].get<std::string>() == "AI")
				entity->addComponent(std::make_unique<Framework::AIComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Animator")
				entity->addComponent(std::make_unique<Framework::AnimatorComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Collision")
				entity->addComponent(std::make_unique<Framework::CollisionComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Player")
				entity->addComponent(std::make_unique<Framework::PlayerComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Position")
				entity->addComponent(std::make_unique<Framework::PositionComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Sprite")
				entity->addComponent(std::make_unique<Framework::SpriteComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Stats")
				entity->addComponent(std::make_unique<Framework::StatsComponent>(componentJSON));
			if (componentJSON["componentType"].get<std::string>() == "Velocity")
				entity->addComponent(std::make_unique<Framework::VelocityComponent>(componentJSON));
		}
		return entity;
	}
}

#include <fstream>
#include "EntityFactory.h"
#include "component/Components.h"

namespace Entity {

	std::unique_ptr<Framework::Entity> EntityFactory::createEntity(std::string filePath) {
		std::fstream stream(filePath);
		nlohmann::json json;
		stream >> json;
		std::unique_ptr<Framework::Entity> entity;
		entity = std::make_unique<Framework::Entity>();
		std::vector<nlohmann::json> componentsJSON = json["components"];
		for (int i=0; i < componentsJSON.size(); i++){
			nlohmann::json componentJSON = componentsJSON[i];
			if (componentJSON["componentType"] == "positionComponent") entity->addComponent(std::make_unique<Framework::PositionComponent>(componentJSON));
			else if (componentJSON["componentType"] == "SpriteComponent") entity->addComponent(std::make_unique<Framework::SpriteComponent>(componentJSON));
			else if (componentJSON["componentType"] == "AnimatorComponent") entity->addComponent(std::make_unique<Framework::AnimatorComponent>(componentJSON));
			else if (componentJSON["componentType"] == "StatsComponent") entity->addComponent(std::make_unique<Framework::StatsComponent>(componentJSON));
			else if (componentJSON["componentType"] == "CollisionComponent") entity->addComponent(std::make_unique<Framework::StatsComponent>(componentJSON));
			else if (componentJSON["componentType"] == "VelocityComponent") entity->addComponent(std::make_unique<Framework::VelocityComponent>(componentJSON));
		}
		return entity;
	}

}

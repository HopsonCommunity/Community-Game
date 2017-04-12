#include <fstream>
#include "EntityFactory.h"
#include "component/Components.h"
#include "../Application.h"
#include "animation/Animator.h"

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
			else if (componentJSON["componentType"] == "AIComponent") entity->addComponent(std::make_unique<Framework::AIComponent>(componentJSON));
		}
		return entity;
	}

	std::unique_ptr<Framework::Entity> EntityFactory::createPlayer()
	{
		std::unique_ptr<Framework::Entity> player = std::make_unique<Framework::Entity>();

		player->addComponent(std::make_unique<Framework::PositionComponent>());
		player->addComponent(std::make_unique<Framework::SpriteComponent>(sf::Sprite(Application::instance->getResources().textures.get("entity/player_modelDefault"), sf::IntRect(0, 0, 32, 64))));
		player->addComponent(std::make_unique<Framework::StatsComponent>());
		player->addComponent(std::make_unique<Framework::VelocityComponent>());
		player->addComponent(std::make_unique<Framework::CollisionComponent>(sf::FloatRect(0, 0, 32, 32)));
		player->addComponent(std::make_unique<Framework::AnimatorComponent>(Framework::Animator()));
		player->addComponent(std::make_unique<Framework::PlayerComponent>());

		Framework::VelocityComponent* c_vel = player->getComponent<Framework::VelocityComponent>();
		c_vel->speed = 200;

		Framework::AnimatorComponent* c_anim = player->getComponent<Framework::AnimatorComponent>();
		c_anim->animator.addAnimation("idle", 0, 0, 32, 8, 7);
		c_anim->animator.addAnimation("run", 0, 64, 32, 8, 14);
		c_anim->animator.setAnimation("idle");

		//auto health_boost = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);

		//Framework::StatsComponent* c_stats = player->getComponent<Framework::StatsComponent>();
		//c_stats->addEffect(health_boost);
		//c_stats->stats.health = health_boost->max_health;
		//c_stats->addEffect(std::make_shared<Defense>(20 * 5, 20, 30));

		return player;
	}

	std::unique_ptr<Framework::Entity> EntityFactory::createZombie(const sf::Vector2f& position)
	{
		std::unique_ptr<Framework::Entity> zombie = std::make_unique<Framework::Entity>();

		zombie->addComponent(std::make_unique<Framework::PositionComponent>(position));
		zombie->addComponent(std::make_unique<Framework::SpriteComponent>(sf::Sprite(Application::instance->getResources().textures.get("entity/enemy/zombie"), sf::IntRect(0, 0, 32, 64))));
		zombie->addComponent(std::make_unique<Framework::StatsComponent>());
		zombie->addComponent(std::make_unique<Framework::VelocityComponent>());
		zombie->addComponent(std::make_unique<Framework::CollisionComponent>(sf::FloatRect(0, 0, 32, 32)));
		zombie->addComponent(std::make_unique<Framework::AnimatorComponent>(Framework::Animator()));
		zombie->addComponent(std::make_unique<Framework::AIComponent>());

		Framework::VelocityComponent* c_vel = zombie->getComponent<Framework::VelocityComponent>();
		c_vel->speed = 100;

		Framework::AnimatorComponent* c_anim = zombie->getComponent<Framework::AnimatorComponent>();
		c_anim->animator.addAnimation("idle", 16, 0, 64, 4, 7);
		c_anim->animator.addAnimation("run", 16, 64, 64, 4, 14);
		c_anim->animator.setAnimation("idle");

		//StatsComponent* c_stats = getComponent<StatsComponent>();
		//c_stats->addEffect(health_boost);
		//c_stats->stats.health = health_boost->max_health;
		//c_stats->addEffect(std::make_shared<Defense>(20 * 5, 20, 30));

		return zombie;
	}

}

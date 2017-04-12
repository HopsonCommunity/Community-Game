#include "Zombie.h"

using namespace std::placeholders;

namespace Framework
{
	Zombie::Zombie(const sf::Vector2f& position)
	{
		addComponent(std::make_unique<Framework::PositionComponent>(position));
		addComponent(std::make_unique<Framework::SpriteComponent>(sf::Sprite(Application::instance->getResources().textures.get("entity/enemy/zombie"), sf::IntRect(0, 0, 32, 64))));
		addComponent(std::make_unique<Framework::StatsComponent>());
		addComponent(std::make_unique<Framework::VelocityComponent>());
		addComponent(std::make_unique<Framework::CollisionComponent>(sf::FloatRect(0, 0, 32, 32)));
		addComponent(std::make_unique<Framework::AnimatorComponent>(Animator()));
		addComponent(std::make_unique<Framework::AnimatorComponent>(Animator()));

		VelocityComponent* c_vel = getComponent<VelocityComponent>();
		c_vel->speed = 100;

		AnimatorComponent* c_anim = getComponent<AnimatorComponent>();
		c_anim->animator.addAnimation("idle", 16, 0, 64, 4, 7);
		c_anim->animator.addAnimation("run", 16, 64, 64, 4, 14);
		c_anim->animator.setAnimation("idle");

		auto health_boost = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);

		StatsComponent* c_stats = getComponent<StatsComponent>();
		c_stats->addEffect(health_boost);
		c_stats->stats.health = health_boost->max_health;
		c_stats->addEffect(std::make_shared<Defense>(20 * 5, 20, 30));
	}
	
	void Zombie::update(const Timestep& ts)
	{
		int32 xa = 0, ya = 0;
		VelocityComponent* c_vel = getComponent<VelocityComponent>();

		PositionComponent* c_pos = getComponent<PositionComponent>();
		PositionComponent* c_player_pos = State::SPlaying::instance->m_level.getEntity(State::SPlaying::instance->m_level.player_id)->getComponent<PositionComponent>();

		// Before feeding coords in A*, convert them to tile precision (x32)
		std::vector<Node*> path = AStar::findPath({ (int32)c_pos->position.x >> 5, (int32)c_pos->position.y >> 5 }, { (int32)c_player_pos->position.x >> 5, (int32)c_player_pos->position.y >> 5 }, &State::SPlaying::instance->m_level);
		if (!path.empty())
		{
			Vec2i vec = path.at(path.size() - 1)->pos;
			vec.x = vec.x << 5;
			vec.y = vec.y << 5;
			int offSet = 5; //Magic number. I'm using it to avoid zombie flickering in walls.
			if (c_pos->position.x < vec.x + offSet) xa++;
			if (c_pos->position.x > vec.x + offSet) xa--;
			if (c_pos->position.y < vec.y + offSet) ya++;
			if (c_pos->position.y > vec.y + offSet) ya--;
			path.clear();
		}

		c_vel->move(xa, ya);

		AnimatorComponent* c_anim = getComponent<AnimatorComponent>();
		c_anim->animator.setAnimation(c_vel->moving ? "run" : "idle");

		SpriteComponent* c_sprite = getComponent<SpriteComponent>();
		c_sprite->flipX = Application::instance->mousePosition().x > Application::instance->getWindow().getSize().x / 2;

		c_vel->moving = false;
	}
}
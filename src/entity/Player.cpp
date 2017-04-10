#include "Player.h"

#include "../Application.h"

#include "component/Components.h"

namespace Framework
{
	Player::Player()
	{
		addComponent(std::make_unique<Framework::PositionComponent>());
		addComponent(std::make_unique<Framework::SpriteComponent>(sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64))));
		addComponent(std::make_unique<Framework::StatsComponent>());
		addComponent(std::make_unique<Framework::VelocityComponent>());
		addComponent(std::make_unique<Framework::CollisionComponent>(sf::FloatRect(0, 0, 32, 32)));
		addComponent(std::make_unique<Framework::AnimatorComponent>(Animator()));

		VelocityComponent* c_vel = getComponent<VelocityComponent>();
		c_vel->speed = 200;

		AnimatorComponent* c_anim = getComponent<AnimatorComponent>();
		c_anim->animator.addAnimation("idle", 0, 0, 32, 8, 7);
		c_anim->animator.addAnimation("run", 0, 64, 32, 8, 14);
		c_anim->animator.setAnimation("idle");

		auto health_boost = std::make_shared<HealthBoost>(DURATION_INFINITE, 800, 0);
	
		StatsComponent* c_stats = getComponent<StatsComponent>();
		c_stats->addEffect(health_boost);
		c_stats->stats.health = health_boost->max_health;
		c_stats->addEffect(std::make_shared<Defense>(20 * 5, 20, 30));
	}

	void Player::update(const Timestep& ts)
	{
		VelocityComponent* c_vel = getComponent<VelocityComponent>();

		if (Application::instance->inputPressed(MOVE_UP))
			c_vel->move(-90);
		if (Application::instance->inputPressed(MOVE_DOWN))
			c_vel->move(90);
		if (Application::instance->inputPressed(MOVE_LEFT))
			c_vel->move(180);
		if (Application::instance->inputPressed(MOVE_RIGHT))
			c_vel->move(0);

		AnimatorComponent* c_anim = getComponent<AnimatorComponent>();
		c_anim->animator.setAnimation(c_vel->moving ? "run" : "idle");

		SpriteComponent* c_sprite = getComponent<SpriteComponent>();
		c_sprite->flipX = Application::instance->mousePosition().x > Application::instance->getWindow().getSize().x / 2;

		c_vel->moving = false;
	}
}
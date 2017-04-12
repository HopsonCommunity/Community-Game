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
		addComponent(std::make_unique<Framework::AIComponent>());

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

	}
}
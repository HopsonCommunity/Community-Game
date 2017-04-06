#include "Zombie.h"

#include "../../Application.h"
#include "../../level/Level.h"
#include "../Player.h"
#include "../../util/Maths.h"

namespace Framework
{
	Zombie::Zombie()
	{
		sprite = sf::Sprite(Application::instance->getResources().textures.get("player_modelDefault"), sf::IntRect(0, 0, 32, 64));

		m_animator.addAnim("idle", 0, 0, 32, 8, 7);
		m_animator.addAnim("run", 0, 64, 32, 8, 14);
		m_animator.setAnim("idle");
		m_speedWalk = 60;

		constexpr static uint health = 400;
		auto hb = std::make_shared<HealthBoost>(DURATION_INFINITE, health, 0);
		addEffect(hb);

		m_health = health;
	}

	void Zombie::update(const Timestep& ts)
	{
		Creature::update(ts);

		float dx = level->player->position.x - position.x;
		float dy = level->player->position.y - position.y;
		float theta = atan2(dy, dx);

		float angle = toDegrees(theta);

		if (angle > -135 && angle < -45)
			walk(UP);
		if (angle < 135 && angle > 45)
			walk(DOWN);
		if (angle > 135 || angle < -135)
			walk(LEFT);
		if (angle > -45 && angle < 45)
			walk(RIGHT);

		applyVelocity(ts.asSeconds());
		m_animator.setAnim(m_walking ? "run" : "idle");
	}
}
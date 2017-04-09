#include "System.h"

#include "../Entity.h"
#include "../component/Components.h"
#include "../../util/Timestep.h"

namespace Framework
{
	void MoveSystem::update(const Timestep& ts, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		CollisionComponent* c_comp = entity->getComponent<CollisionComponent>();

		if (c_pos && c_vel)
		{
			auto colliding = std::make_pair(false, false);//Physics::tileCollision(position, velocity, m_hitBox, *level, dt);

			if (!colliding.first)
				c_pos->position.x += c_vel->velocity.x * ts.asSeconds();
			if (!colliding.second)
				c_pos->position.y += c_vel->velocity.y * ts.asSeconds();

			c_vel->velocity.x = 0;
			c_vel->velocity.y = 0;
		}
	}

	void StatsSystem::update(const Timestep& ts, Entity* entity)
	{
		StatsComponent* c_stats = entity->getComponent<StatsComponent>();
		if (c_stats)
		{
			c_stats->stats.reset();
			for (auto effect : c_stats->active_effects)
			{
				effect->manageDuration();
				effect->effect(c_stats->stats);
			}
		}
	}
}
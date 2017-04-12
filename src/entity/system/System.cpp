#include "System.h"

#include "../Entity.h"
#include "../component/Components.h"
#include "../../util/Timestep.h"
#include "../physics/TileCollision.h"
#include "../../states/StatePlaying.h"
#include "../../level/LevelRenderer.h"

namespace Framework
{
	void MoveSystem::update(const Timestep& ts, Entity* entity)
	{
		// This is how you can get components from an entity. 
		// Returns nullptr if an entity doesn't have the specified component
		// Prefix entity components with c_
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		CollisionComponent* c_col = entity->getComponent<CollisionComponent>();

		// In this case for the movement system it requires that the entity has position and velocity components. 
		// This if statement is the same as: "if (c_pos != nullptr && c_vel != nullptr)"
		if (c_pos && c_vel)
		{
			// Here is defined what the system does to the entity.
			// The movement system moves the entities position, taking it's velocity,
			// speed and delta time into account

			// For now collision is disabled
			auto colliding = std::make_pair(false, false);
			
			if (!colliding.first)
				c_pos->position.x += c_vel->velocity.x * c_vel->speed * ts.asSeconds();
			if (!colliding.second)
				c_pos->position.y += c_vel->velocity.y * c_vel->speed * ts.asSeconds();

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

	void AnimatorSystem::update(const Timestep& ts, Entity* entity)
	{
		SpriteComponent* c_sprite = entity->getComponent<Framework::SpriteComponent>();
		AnimatorComponent* c_anim = entity->getComponent<Framework::AnimatorComponent>();

		if (c_sprite && c_anim)
		{
			c_anim->animator.update(ts, c_sprite->sprite);
		}
	}

	void RenderSystem::update(const Timestep& ts, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<Framework::PositionComponent>();
		SpriteComponent* c_sprite = entity->getComponent<Framework::SpriteComponent>();
		
		if (c_pos && c_sprite)
		{
			c_sprite->sprite.setScale(static_cast<float>(c_sprite->flipX ? 1 : -1), static_cast<float>(c_sprite->flipY ? 1 : -1));
			c_sprite->sprite.setOrigin(static_cast<float>(c_sprite->sprite.getTextureRect().width / 2), static_cast<float>(c_sprite->sprite.getTextureRect().height));
			Level::LevelRenderer::renderEntitySprite(c_pos->position.x, c_pos->position.y, c_sprite->sprite);
		}
	}
}

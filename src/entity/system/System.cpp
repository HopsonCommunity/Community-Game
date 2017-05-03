#include "System.h"

#include "../Entity.h"
#include "../EntityFactory.h"
#include "../component/Components.h"
#include "../../level/tile/TileCollision.h"

#include "../../maths/Maths.h"
#include "../../util/Log.h"
#include "../../util/Timestep.h"
#include "../../level/tile/TileFlooding.h"
#include "../../app/Application.h"

namespace Entity
{
	void move(Vec2 dest, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		
		if (dest.x != c_pos->position.x && dest.y != c_pos->position.y)
		{
			move({ dest.x, c_pos->position.y }, entity);
			move({ c_pos->position.x, dest.y }, entity);
		}

		c_pos->position.x = dest.x;
		c_pos->position.y = dest.y;
	}

	void MoveSystem::update(const Timestep& ts, Entity* entity)
	{
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		if (c_physics)
		{
			if (c_physics->object.inv_mass == 0.0f)
				return;

			c_physics->object.velocity += (c_physics->object.force * c_physics->object.inv_mass) * (ts.asSeconds() * 5.0f);

			Physics::tileCollision(c_physics->object);

			c_physics->object.pos += c_physics->object.velocity * ts.asSeconds();
			LOG_INFO(c_physics->object.mass, ", ", c_physics->object.inv_mass);
			c_physics->object.force = { 0, 0 };

			return;
		}

		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();

		if (c_sprite)
			if (c_sprite->flipOnVelocity)
			{
				if (c_vel->velocity.x > 0)
					c_sprite->flipX = true;
				else if (c_vel->velocity.x < 0)
					c_sprite->flipX = false;
			}

		if (c_pos && c_vel)
		{
			Vec2 dest(c_pos->position.x + c_vel->velocity.x * c_vel->speed * ts.asSeconds(), c_pos->position.y + c_vel->velocity.y * c_vel->speed * ts.asSeconds());
			
			move(dest, entity);
		}

		c_vel->velocity.x = 0;
		c_vel->velocity.y = 0;
	}

	void StatsSystem::update(const Timestep& ts, Entity* entity)
	{
		StatsComponent* c_stats = entity->getComponent<StatsComponent>();
		if (c_stats)
		{
			for (auto effect : c_stats->active_effects)
			{
				effect->manageDuration();
				effect->effect(c_stats->stats);
			}
		}
	}

	void AnimatorSystem::update(const Timestep& ts, Entity* entity)
	{
		SpriteComponent*    c_sprite = entity->getComponent<SpriteComponent>();
		AnimatorComponent*  c_anim = entity->getComponent<AnimatorComponent>();
		VelocityComponent*  c_vel = entity->getComponent<VelocityComponent>();

		if (c_sprite && c_anim)
		{
			if (c_vel)
				c_vel->moving ? c_anim->animator.setAnimation("run") : c_anim->animator.setAnimation("idle");

			c_anim->animator.update(ts, c_sprite->sprite);
		}
	}

	void RenderSystem::update(const Timestep& ts, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();

		if (c_pos && c_sprite)
		{
			c_sprite->sprite.setOrigin(c_sprite->origin);
			c_sprite->sprite.setScale(c_sprite->flipX ? 1.0f : -1.0f, 1.0f);
			
			sf::RenderStates states;
			if (!c_physics)
				states.transform.translate(c_pos->position);
			else
				states.transform.translate(c_physics->object.pos);

			Application::instance->getWindow().draw(c_sprite->sprite, states);
		}
	}

	void AISystem::update(const Timestep& ts, Entity* entity)
	{
		AIComponent* c_ai = entity->getComponent<AIComponent>();
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		if (c_ai && c_pos && c_vel)
			c_ai->behaviour->behave(entity);
	}

	void PlayerInputSystem::update(const Timestep& ts, Entity* entity)
	{
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		PlayerComponent* c_player = entity->getComponent<PlayerComponent>();
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();

		if (c_player && c_physics)
		{
			float xa = 0, ya = 0;

			if (Application::instance->inputPressed(MOVE_UP))
				ya--;
			if (Application::instance->inputPressed(MOVE_DOWN))
				ya++;
			if (Application::instance->inputPressed(MOVE_LEFT))
				xa--;
			if (Application::instance->inputPressed(MOVE_RIGHT))
				xa++;

			xa *= 100;
			ya *= 100;

			c_physics->object.force += { xa, ya };

			c_sprite->flipX = (int32)Application::instance->mousePosition().x > (int32)Application::instance->getWindow().getSize().x / 2;
		}
	}

	void LifeSystem::update(const Timestep& ts, Entity* entity)
	{
		LifeComponent* c_life = entity->getComponent<LifeComponent>();

		if (c_life)
		{
			if (c_life->done)
				///@TODO: Remove from level
			{
			}
			c_life->life -= ts.asSeconds();
			if (c_life->life <= 0)
				c_life->done = 1;
		}
	}
}
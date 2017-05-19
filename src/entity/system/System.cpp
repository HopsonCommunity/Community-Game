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
	void MoveSystem::update(const Timestep& ts, Entity* entity)
	{
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();

		if (c_physics)
		{
			auto colliding = Level::tileCollision(c_physics->pos, c_physics->velocity, c_physics->aabb, ts);
					
			if (!colliding.first)
				c_physics->pos.x += c_physics->velocity.x * ts.asSeconds();
			if (!colliding.second)
				c_physics->pos.y += c_physics->velocity.y * ts.asSeconds();
			
			if (c_sprite && c_sprite->flipOnVelocity)
				c_sprite->flipX = c_physics->velocity.x != 0 ? (c_physics->velocity.x > 0 ? false : true) : c_sprite->flipX;
				
			c_physics->velocity.x = 0;
			c_physics->velocity.y = 0;
		}
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
		PhysicsComponent*  c_physics = entity->getComponent<PhysicsComponent>();

		if (c_sprite && c_anim)
		{
			if (c_physics)
				c_physics->moving ? c_anim->animator.setAnimation("run") : c_anim->animator.setAnimation("idle");

			c_anim->animator.update(ts, c_sprite->sprite);
		}
	}

	void LightingSystem::update(const Timestep& ts, Entity* entity)
	{
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		LightComponent* c_light = entity->getComponent<LightComponent>();

		if (c_physics && c_light)
		{
			sf::Vector2<uint> old = { c_light->light.x, c_light->light.y };
			c_light->light.x = c_physics->pos.x / TILE_SIZE;
			c_light->light.y = c_physics->pos.y / TILE_SIZE;
			if (old.x != c_light->light.x || old.y != c_light->light.y)
				State::Playing::instance->getLevel().getTiles().requestRebuild(0);

			if (!c_light->added)
			{
				State::Playing::instance->getLevel().getTiles().addStaticLight(0, &c_light->light);
				c_light->added = true;
			}
		}
	}

	void RenderSystem::update(const Timestep& ts, Entity* entity)
	{
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();

		if (c_physics && c_sprite)
		{
			c_sprite->sprite.setOrigin(c_sprite->origin);
			c_sprite->sprite.setScale(c_sprite->flipX ? -1.0f : 1.0f, 1.0f);
			
			sf::RenderStates states;
			states.transform.translate(c_physics->pos);
			
			/* Draws AABB outline (for debugging purposes)
			auto rs = sf::RectangleShape(c_physics->aabb.max);
			rs.setPosition(c_physics->aabb.min);
			rs.setFillColor({ 0, 0, 0, 0 });
			rs.setOutlineColor({ 255, 0, 0, 255 });
			rs.setOutlineThickness(1);
			Application::instance->getWindow().draw(rs, states);
			*/

			Application::instance->getWindow().draw(c_sprite->sprite, states);
		}
	}

	void AISystem::update(const Timestep& ts, Entity* entity)
	{
		AIComponent* c_ai = entity->getComponent<AIComponent>();
		if (c_ai)
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

			if (xa != 0 || ya != 0)
				c_physics->setVelocity(xa, ya);
			else
				c_physics->moving = false;

			c_sprite->flipX = static_cast<int32>(Application::instance->mousePosition().x) < static_cast<int32>(Application::instance->getWindow().getSize().x) / 2;
		}
	}

	void LifeSystem::update(const Timestep& ts, Entity* entity)
	{
		LifeComponent* c_life = entity->getComponent<LifeComponent>();

		if (c_life)
		{
			if (c_life->done)
				State::Playing::instance->getLevel().removeEntity(entity);
			c_life->life -= ts.asSeconds();
			if (c_life->life <= 0)
				c_life->done = 1;
		}
	}
}
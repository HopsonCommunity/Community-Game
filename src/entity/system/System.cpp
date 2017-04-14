#include "System.h"

#include "../Entity.h"
#include "../component/Components.h"
#include "../../util/Timestep.h"
#include "../physics/TileCollision.h"
#include "../../states/StatePlaying.h"
#include "../../level/LevelRenderer.h"
#include "../../util/TileFlooding.h"
#include "../EntityFactory.h"

namespace Framework
{
	void move(sf::Vector2i dest, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		CollisionComponent* c_col = entity->getComponent<CollisionComponent>();

		if (dest.x != c_pos->position.x && dest.y != c_pos->position.y)
		{
			move({ dest.x, (int)c_pos->position.y }, entity);
			move({ (int)c_pos->position.x, dest.y }, entity);
		}

		if (c_col)
		{
			bool colliding = c_col ? Physics::tileCollision(dest, c_col->aabb) : false;
			if (!colliding)
			{
				c_pos->position.x = (float)dest.x;
				c_pos->position.y = (float)dest.y;
			}
		}
		else
		{
			c_pos->position.x = (float)dest.x;
			c_pos->position.y = (float)dest.y;
		}
	}

	void MoveSystem::update(const Timestep& ts, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();

		if (c_pos && c_vel)
		{
			sf::Vector2i dest((int)round(c_pos->position.x + c_vel->velocity.x * c_vel->speed * ts.asSeconds()), (int)round(c_pos->position.y + c_vel->velocity.y * c_vel->speed * ts.asSeconds()));

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
		SpriteComponent*    c_sprite = entity->getComponent<Framework::SpriteComponent>();
		AnimatorComponent*  c_anim   = entity->getComponent<Framework::AnimatorComponent>();
		VelocityComponent*  c_vel    = entity->getComponent<VelocityComponent>();

		if (c_sprite && c_anim)
		{
			if (c_vel)
				c_vel->moving ? c_anim->animator.setAnimation("run") : c_anim->animator.setAnimation("idle");

			c_anim->animator.update(ts, c_sprite->sprite);
		}
	}

	void RenderSystem::update(const Timestep& ts, Entity* entity)
	{
		PositionComponent* c_pos = entity->getComponent<Framework::PositionComponent>();
		SpriteComponent* c_sprite = entity->getComponent<Framework::SpriteComponent>();

		if (c_pos && c_sprite)
		{
			c_sprite->sprite.setScale(static_cast<float>(c_sprite->flipX ? 1 : -1), 1.0f);
			c_sprite->sprite.setOrigin(static_cast<float>(c_sprite->sprite.getTextureRect().width / 2), static_cast<float>(c_sprite->sprite.getTextureRect().height));
			Level::LevelRenderer::renderEntitySprite(c_pos->position.x, c_pos->position.y, c_sprite->sprite);
		}
	}

	void AISystem::update(const Timestep& ts, Entity* entity)
	{
		AIComponent* c_ai = entity->getComponent<AIComponent>();
		PositionComponent* c_pos = entity->getComponent<PositionComponent>();
		if (c_ai && c_pos)
		{
			if (c_ai->trackingEntity)
			{
				PositionComponent* c_enemy_pos = c_ai->trackingEntity->getComponent<PositionComponent>();
				VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();

				if (c_vel && c_enemy_pos)
				{
					std::vector<Util::Node*> path = c_ai->findPath({ (int32)c_pos->position.x >> 5, (int32)c_pos->position.y >> 5 }, { (int32)c_enemy_pos->position.x >> 5, (int32)c_enemy_pos->position.y >> 5 }, &State::SPlaying::instance->m_level);
					int xa = 0, ya = 0;

					if (path.size() > c_ai->trackingDistance * 1.5)
						c_ai->trackingEntity = nullptr;

					if (!path.empty())
					{
						Util::Vec2i vec = path.at(path.size() - 1)->pos;
						vec.x = vec.x << 5;
						vec.y = vec.y << 5;
						int offSet = 5; //Magic number. I'm using it to avoid zombie flickering in walls.
						if (c_pos->position.x < vec.x + offSet) xa++;
						if (c_pos->position.x > vec.x + offSet) xa--;
						if (c_pos->position.y < vec.y + offSet) ya++;
						if (c_pos->position.y > vec.y + offSet) ya--;
						path.clear();
					}

					if (xa != 0 || ya != 0)
						c_vel->move(xa, ya);
					else
						c_vel->moving = false;
				}
			}
			else
			{
				// Check if player is in distance of this entity and set it as target if it is,
				// otherwise set target to non-moving, necessary for the right animation to play

				Entity* player = State::SPlaying::instance->m_level.getEntity(State::SPlaying::instance->m_level.player_id);
				PositionComponent* c_pos_player = player->getComponent<PositionComponent>();

				// Tile flooding for every entity is not ideal as it really kills the fps
				//std::vector<Entity*> entities = TileFlooding::getAllEntitesNearOtherEntity((sf::Vector2i)c_pos->position, 6, &State::SPlaying::instance->m_level);
				//for (Entity* ent : entities)
				//	if (ent == player)
				//		c_ai->trackingEntity = player;

				///@TODO: Find better solution
				//Using euclidean distance for now
				if (Util::distance((Util::Vec2i)c_pos_player->position, (Util::Vec2i)c_pos->position) <= c_ai->trackingDistance * 32)
					c_ai->trackingEntity = player;
				else
				{
					VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
					if (c_vel)
						c_vel->moving = false;
				}
			}
		}

	}

	void PlayerInputSystem::update(const Timestep& ts, Entity* entity)
	{
		VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
		PlayerComponent* c_player = entity->getComponent<PlayerComponent>();
		SpriteComponent* c_sprite = entity->getComponent<SpriteComponent>();

		if (c_player && c_vel)
		{
			int xa = 0, ya = 0;

			if (Application::instance->inputPressed(MOVE_UP))
				ya--;
			if (Application::instance->inputPressed(MOVE_DOWN))
				ya++;
			if (Application::instance->inputPressed(MOVE_LEFT))
				xa--;
			if (Application::instance->inputPressed(MOVE_RIGHT))
				xa++;

			if (xa != 0 || ya != 0)
				c_vel->move(xa, ya);
			else
				c_vel->moving = false;

			c_sprite->
				flipX = (int32)Application::instance->mousePosition().x > (int32)Application::instance->getWindow().getSize().x / 2;

			if (c_vel->velocity.x > 0)
				c_sprite->flipX = true;
			else if (c_vel->velocity.x < 0)
				c_sprite->flipX = false;
		}
	}
}

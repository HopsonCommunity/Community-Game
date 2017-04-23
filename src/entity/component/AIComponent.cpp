#include "AIComponent.h"

#include "Components.h"

namespace Entity
{
	AIComponent::AIComponent(Behaviour behaviour)
		: behaviour(behaviour)
	{
	}

	AIComponent::AIComponent(nlohmann::json json)
	{
		if (json["behaviour"]["type"] == "FollowPlayer")
			behaviour = FollowPlayer(json["behaviour"]["trackingDistance"], &AStar::constructPath);
	}

	FollowPlayer::FollowPlayer(double trackingDistance, std::function<std::vector<AStar::Location>(AStar::Location, AStar::Location)> func)
		: trackingDistance(trackingDistance), findPath(func)
	{
	}

	void FollowPlayer::behave(Entity* entity)
	{
		if (target)
		{
			PositionComponent* c_pos = entity->getComponent<PositionComponent>();
			VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();

			PositionComponent* c_target_pos = target->getComponent<PositionComponent>();

			if (c_vel && c_target_pos)
			{
				std::vector<AStar::Location> path = AStar::constructPath({ (int32)c_pos->position.x >> 5, (int32)c_pos->position.y >> 5 }, { (int32)c_target_pos->position.x >> 5, (int32)c_target_pos->position.y >> 5 });

				int xa = 0, ya = 0;

				if (path.size() > trackingDistance * 1.5)
					target = nullptr;

				if (!path.empty())
				{
					AStar::Location loc = path.at(path.size() - 1);
					Vec2i vec = { std::get<0>(loc), std::get<1>(loc) };
					vec.x = vec.x << 5;
					vec.y = vec.y << 5;
					int offSet = 0;
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

			// Entity* player = State::SPlaying::instance->m_level.getEntity(State::SPlaying::instance->m_level.player_id);
			// PositionComponent* c_pos_player = player->getComponent<PositionComponent>();

			// Tile flooding for every entity is not ideal as it really kills the fps
			//std::vector<Entity*> entities = TileFlooding::getAllEntitesNearOtherEntity((sf::Vector2i)c_pos->position, 6, &State::SPlaying::instance->m_level);
			//for (Entity* ent : entities)
			//	if (ent == player)
			//		c_ai->trackingEntity = player;

			///@TODO: Find better solution
			// Using euclidean distance for now

			///@TODO: Fix this when we  have level.
			//if (distance((Vec2i)c_pos_player->position, (Vec2i)c_pos->position) <= c_ai->trackingDistance * 32)
			//	c_ai->trackingEntity = player;
			// else
			{
				VelocityComponent* c_vel = entity->getComponent<VelocityComponent>();
				if (c_vel)
					c_vel->moving = false;
			}
		}
	}
}
#include "AIComponent.h"

#include "Components.h"
#include "../../app/states/StatePlaying.h"
#include "../EntityFactory.h"

namespace Entity
{
	AIComponent::AIComponent(nlohmann::json json)
	{
		if (json["behaviour"]["type"] == "FollowPlayer")
			behaviour = new FollowPlayer(json["behaviour"]["trackingDistance"], &AStar::constructPath);
	}

	FollowPlayer::FollowPlayer(double trackingDistance, std::function<std::vector<AStar::Location>(AStar::Location, AStar::Location)> func)
		: trackingDistance(trackingDistance), findPath(func)
	{
	}

	void FollowPlayer::behave(Entity* entity)
	{
		PhysicsComponent* c_physics = entity->getComponent<PhysicsComponent>();
		if (target)
		{
			PhysicsComponent* c_target_physics = target->getComponent<PhysicsComponent>();

			if (c_target_physics)
			{
				std::vector<AStar::Location> path = AStar::constructPath({ (int32)c_physics->pos.x >> 5, (int32)c_physics->pos.y >> 5 }, { (int32)c_target_physics->pos.x >> 5, (int32)c_target_physics->pos.y >> 5 });

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
					if (c_physics->pos.x < vec.x + offSet) xa++;
					if (c_physics->pos.x > vec.x + offSet) xa--;
					if (c_physics->pos.y < vec.y + offSet) ya++;
					if (c_physics->pos.y > vec.y + offSet) ya--;
					path.clear();
				}

				if (xa != 0 || ya != 0)
					c_physics->setVelocity(xa, ya);
				else
					c_physics->moving = false;
			}
		}
		else
		{
			// Check if player is in distance of this entity and set it as target if it is,
			// otherwise set target to non-moving, necessary for the right animation to play

			Entity* player = State::Playing::instance->getLevel().player;
			PhysicsComponent* c_pos_player = player->getComponent<PhysicsComponent>();

			// Tile flooding for every entity is not ideal as it really kills the fps
			//std::vector<Entity*> entities = TileFlooding::getAllEntitesNearOtherEntity((sf::Vector2i)c_pos->position, 6, &State::SPlaying::instance->m_level);
			//for (Entity* ent : entities)
			//	if (ent == player)
			//		c_ai->trackingEntity = player;

			///@TODO: Find better solution
			// Using euclidean distance for now

			if (distance((Vec2i)c_pos_player->pos, (Vec2i)c_physics->pos) <= trackingDistance * 32)
				target = player;
			else
				c_physics->moving = false;
		}
	}
}
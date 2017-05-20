#include "AIComponent.h"

#include "Components.h"
#include "../../app/states/StatePlaying.h"
#include "../EntityFactory.h"

namespace Entity
{
	AIComponent::AIComponent(nlohmann::json json)
		: behaviour(nullptr)
	{
		if (json.find("behaviour") == json.end())
		{		
			LOG_ERROR("[JSON] Entity with AIComponent but no behaviour!");
			LOG_FATAL("[JSON] Entity with AIComponent but without a valid behaviour! (", json["behaviour"]["type"].get<std::string>(), ")");
		}
		if (json["behaviour"].find("type") == json["behaviour"].end())
		{
			LOG_ERROR("[JSON] Entity with AIComponent but without a behaviour type!");
			LOG_FATAL("[JSON] Entity with AIComponent but without a valid behaviour! (", json["behaviour"]["type"].get<std::string>(), ")");
		}

		if (json["behaviour"]["type"] == "FollowPlayer")
			behaviour = new FollowPlayer(json["behaviour"]["trackingDistance"], nullptr);
	}

	FollowPlayer::FollowPlayer(double trackingDistance, Entity* target)
		: target(nullptr), trackingDistance(trackingDistance)
	{
	}

	void FollowPlayer::behave(Entity* entity)
	{
		PhysicsComponent* c_phys = entity->getComponent<PhysicsComponent>();
		if (target)
		{
			PhysicsComponent* c_target_phys = target->getComponent<PhysicsComponent>();
			if (c_phys && c_target_phys)
			{
				std::vector<AStar::Location> path = AStar::constructPath(std::forward_as_tuple(static_cast<int32>(c_phys->pos.x) >> 5, static_cast<int32>(c_phys->pos.y) >> 5 ), std::forward_as_tuple(static_cast<int32>(c_target_phys->pos.x) >> 5, static_cast<int32>(c_target_phys->pos.y) >> 5 ));

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
					if (c_phys->pos.x < vec.x + offSet) xa++;
					if (c_phys->pos.x > vec.x + offSet) xa--;
					if (c_phys->pos.y < vec.y + offSet) ya++;
					if (c_phys->pos.y > vec.y + offSet) ya--;
					path.clear();
				}

				if (xa != 0 || ya != 0)
					c_phys->setVelocity(xa, ya);
				else
					c_phys->moving = false;
			}
		}
		else
		{
			// Check if player is in distance of this entity and set it as target if it is,
			// otherwise set target to non-moving, necessary for the right animation to play

			Entity* player = State::Playing::instance->getLevel().player;
			PhysicsComponent* c_phys_player = player->getComponent<PhysicsComponent>();

			// Tile flooding for every entity is not ideal as it really kills the fps
			//std::vector<Entity*> entities = TileFlooding::getAllEntitesNearOtherEntity((sf::Vector2i)c_pos->position, 6, &State::SPlaying::instance->m_level);
			//for (Entity* ent : entities)
			//	if (ent == player)
			//		c_ai->trackingEntity = player;

			///@TODO: Find better solution
			// Using euclidean distance for now

			if (distance(static_cast<Vec2i>(c_phys_player->pos), static_cast<Vec2i>(c_phys->pos)) <= trackingDistance * 32)
				target = player;
			else
			{
				if (c_phys)
					c_phys->moving = false;
			}
		}
	}
}
#include "AIComponent.h"

#include "Components.h"
#include "../../app/states/StatePlaying.h"
#include "../EntityFactory.h"

namespace Entity
{
	AIComponent::AIComponent(nlohmann::json json)
	{
		if (json["behaviour"]["type"] == "FollowPlayer")
			behaviour = new FollowPlayer(json["behaviour"]["trackingDistance"], nullptr);
	}

	FollowPlayer::FollowPlayer(double trackingDistance, Entity* target)
		: trackingDistance(trackingDistance)
	{
	}

	void FollowPlayer::behave(Entity* entity)
	{
		PhysicsComponent* c_entity_physics = entity->getComponent<PhysicsComponent>();
		if (!c_entity_physics)
			return;

		if (!target)
		{
			Entity* player = State::Playing::instance->getLevel().player;
			PhysicsComponent* c_player_physics = player->getComponent<PhysicsComponent>();

			///@TODO: Fix tile flooding

			if (distance((Vec2i)c_player_physics->pos, (Vec2i)c_player_physics->pos) <= trackingDistance * 32)
				target = player;
			else
				c_entity_physics->moving = false;
		}
		
		if (target)
		{
			PhysicsComponent* c_target_physics = target->getComponent<PhysicsComponent>();

			if (!c_target_physics)
				return;

			std::vector<AStar::Location> path = AStar::constructPath(
			{ (int32)c_entity_physics->pos.x >> 5, (int32)c_entity_physics->pos.y >> 5 }, 
			{ (int32)c_target_physics->pos.x >> 5, (int32)c_target_physics->pos.y >> 5 });

			if (path.size() > trackingDistance * 1.5)
				target = nullptr;

			float xa = 0, ya = 0;
			
			if (!path.empty())
			{
				Vec2i vec = { std::get<0>(path[0]), std::get<1>(path[0]) };
				vec /= 32;

				if (c_entity_physics->pos.x < vec.x) 
					xa++;
				if (c_entity_physics->pos.x > vec.x) 
					xa--;
				if (c_entity_physics->pos.y < vec.y) 
					ya++;
				if (c_entity_physics->pos.y > vec.y) 
					ya--;
				path.clear();
			}

			if (xa != 0 || ya != 0)
				c_entity_physics->setVelocity(xa, ya);
			else
				c_entity_physics->moving = false;
		}
	}
}
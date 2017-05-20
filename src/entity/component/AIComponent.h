#pragma once

#include "Component.h"
#include "../Entity.h"

#include "../../maths/AStar.h"
#include "../../util/json.hpp"

namespace Entity
{
	class Behaviour
	{
	public:
		virtual void behave(Entity* target) {};
	};

	class FollowPlayer : public Behaviour
	{
	public:
		Entity* target;
		double trackingDistance;
	public:
		FollowPlayer(double trackingDistance, Entity* target);

		void behave(Entity* entity) override;
	};

	class AIComponent : public Component
	{
	public:
		///@TODO: Make this smart ptr
		Behaviour* behaviour;
	public:
		AIComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<AIComponent>(*this);
		}

		static const uint ID = ComponentID::AI;
	};
}

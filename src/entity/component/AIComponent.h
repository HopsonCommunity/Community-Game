#pragma once

#include "Component.h"
#include "../Entity.h"

#include "../../maths/AStar.h"
#include "../../util/json.hpp"

namespace Entity
{
	class AIComponent : public Component
	{
	public:
		Entity* trackingEntity;
		double trackingDistance;

		std::function<std::vector<AStar::Location>(AStar::Location, AStar::Location)> findPath;
	public:
		AIComponent(double trackingDistance);
		AIComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<AIComponent>(*this);
		}

		static const int ID = 1;
	};
}

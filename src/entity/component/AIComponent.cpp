#include "AIComponent.h"

namespace Entity
{
	AIComponent::AIComponent(double trackingDistance)
		: findPath(&AStar::constructPath)
		, trackingEntity(nullptr)
		, trackingDistance(trackingDistance)
	{
	}

	AIComponent::AIComponent(nlohmann::json json)
		: findPath(&AStar::constructPath)
		, trackingEntity(nullptr)
		, trackingDistance(json["trackingDistance"])
	{
	}
}
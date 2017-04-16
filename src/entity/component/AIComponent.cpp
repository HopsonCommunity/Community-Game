#include "AIComponent.h"

namespace Entity
{
	AIComponent::AIComponent(double trackingDistance)
		:findPath(&Util::AStar)
		,trackingEntity(nullptr)
		,trackingDistance(trackingDistance)
	{

	}

	AIComponent::AIComponent(nlohmann::json json)
		: findPath(&Util::AStar)
		, trackingEntity(nullptr)
		, trackingDistance(json["trackingDistance"])
	{
		
	}
}

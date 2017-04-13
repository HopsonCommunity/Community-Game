#include "AIComponent.h"

namespace Framework
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

	ComponentType* AIComponent::getStaticType()
	{
		static ComponentType type({ "AI" });
		return &type;
	}

	ComponentType* AIComponent::getType() const
	{
		return getStaticType();
	}
}
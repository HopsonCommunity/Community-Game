#include "AIComponent.h"

namespace Framework
{
	AIComponent::AIComponent()
	{

	}

	AIComponent::AIComponent(nlohmann::json json)
	{

	}

	std::vector<Node*> AIComponent::findPath(Vec2i start, Vec2i end, Level::Level* level)
	{
		return AStar::findPath(start, end, level);
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
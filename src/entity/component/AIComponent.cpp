#include "AIComponent.h"

#include "../../util/Maths.h"

namespace Framework
{
	AIComponent::AIComponent(std::function<void(Entity* entity)> ai)
		: ai(ai)
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
#include "AnimatorComponent.h"

namespace Framework
{
	AnimatorComponent::AnimatorComponent(Animator animator)
		: animator(animator)
	{
	}

	AnimatorComponent::AnimatorComponent(nlohmann::json json) {
		///@TODO: json parsing
	}

	ComponentType* AnimatorComponent::getStaticType()
	{
		static ComponentType type({ "Animator" });
		return &type;
	}

	ComponentType* AnimatorComponent::getType() const
	{
		return getStaticType();
	}
}

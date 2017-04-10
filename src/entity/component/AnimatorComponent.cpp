#include "AnimatorComponent.h"

namespace Framework
{
	AnimatorComponent::AnimatorComponent(Animator animator)
		: animator(animator)
	{
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
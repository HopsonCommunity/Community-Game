#include "AnimatorComponent.h"

namespace Framework
{
	AnimatorComponent::AnimatorComponent(Animator animator)
		: animator(animator)
	{
	}

	AnimatorComponent::AnimatorComponent(nlohmann::json json)
		: animator(Animator())
	{
		std::vector<nlohmann::json> animations = json["animations"];
		for (int i = 0; i < animations.size(); i++)
		{
			nlohmann::json animation = animations[i];
			animator.addAnimation(animation["name"], animation["positionX"], animation["positionY"], animation["stride"], animation["length"], animation["fps"]);
		}
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

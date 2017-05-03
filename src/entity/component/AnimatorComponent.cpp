#include "AnimatorComponent.h"

namespace Entity
{
	AnimatorComponent::AnimatorComponent(Animator animator)
		: animator(animator)
	{
	}

	AnimatorComponent::AnimatorComponent(nlohmann::json json)
		: animator(Animator())
	{
		std::vector<nlohmann::json> animations = json["animations"];
		for (unsigned int i = 0; i < animations.size(); i++)
		{
			nlohmann::json animation = animations[i];
			animator.addAnimation(animation["name"], animation["positionX"], animation["positionY"], animation["stride"], animation["length"], animation["fps"]);
		}
	}
}
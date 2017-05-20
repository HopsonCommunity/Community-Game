#include "AnimatorComponent.h"

#include "../../util/Log.h"

namespace Entity
{
	AnimatorComponent::AnimatorComponent(Animator animator)
		: animator(animator)
	{
	}

	template <typename T>
	void handleJSON(nlohmann::json& animation, uint index, const std::string& varName, T& var)
	{
		if (animation.find(varName) == animation.end())
			LOG_WARN("[JSON] Entity with AnimatorComponent but Animation with index(", index, ") without \"", varName, "\"! Set to default..");
		else
			var = animation[varName].get<T>();
	}

	AnimatorComponent::AnimatorComponent(nlohmann::json json)
		: animator(Animator())
	{
		std::vector<nlohmann::json> animations = json["animations"];
		if (animations.empty())
			LOG_WARN("[JSON] Entity with AnimatorComponent but no animations!");

		for (uint i = 0; i < animations.size(); i++)
		{
			nlohmann::json animation = animations[i];

			std::string name = "$$animation_name";
			uint posX = 0, posY = 0, stride = 32, length = 2, fps = 14;

			handleJSON<std::string>(animation, i, "name", name);
			handleJSON<uint>(animation, i, "positionX", posX);
			handleJSON<uint>(animation, i, "positionY", posY);
			handleJSON<uint>(animation, i, "stride", stride);
			handleJSON<uint>(animation, i, "length", length);
			handleJSON<uint>(animation, i, "fps", fps);

			animator.addAnimation(name, posX, posY, stride, length, fps);
		}
	}
}

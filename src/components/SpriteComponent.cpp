#include "SpriteComponent.h"

#include "../app/Application.h"
#include "../util/Log.h"

namespace Components
{
	SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
		: sprite(sprite), flipX(false), animated(false)
	{
	}

	template <typename T>
	void handleJSON(nlohmann::json& animation, uint index, const std::string& varName, T& var)
	{
		if (animation.find(varName) == animation.end())
			LOG_WARN("[JSON] Entity with Animated sprite but animation with index(", index, ") without \"", varName, "\"! Set to default..");
		else
			var = animation[varName].get<T>();
	}

	SpriteComponent::SpriteComponent(nlohmann::json json)
		: flipX(false), animated(true)
	{
		if (json.find("src") == json.end())
			LOG_ERROR("[JSON] Entity with SpriteComponent but without sprite path!");
		else
			sprite = sf::Sprite(Application::get().getTexture(json["src"]), sf::IntRect(json["rect"]["left"], json["rect"]["top"], json["rect"]["width"], json["rect"]["height"]));

		sprite.setOrigin({ json["origin"]["x"], json["origin"]["y"] });

		if (json.find("animations") == json.end())
			return;

		std::vector<nlohmann::json> animations = json["animations"];
		if (animations.empty())
			animated = false;

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
	};
}

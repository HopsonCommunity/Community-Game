#include "SpriteComponent.h"

#include "../../app/Application.h"
#include "../../util/Log.h"

namespace Entity
{
	SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
		: sprite(sprite), flipOnVelocity(false), flipX(false)
	{
	}

	SpriteComponent::SpriteComponent(nlohmann::json json)
		: flipOnVelocity(false), flipX(false)
	{
		if (json.find("src") == json.end())
		LOG_ERROR("[JSON] Entity with SpriteComponent but without sprite path!");
		else
			sprite = sf::Sprite(Application::instance->getResources().textures.get(json["src"]), sf::IntRect(json["rect"]["left"], json["rect"]["top"], json["rect"]["width"], json["rect"]["height"]));

		origin = {json["origin"]["x"], json["origin"]["y"]};

		if (json.find("flipOnVelocity") != json.end())
			flipOnVelocity = json["flipOnVelocity"];
	};
}

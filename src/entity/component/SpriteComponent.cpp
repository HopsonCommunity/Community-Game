#include "SpriteComponent.h"

#include "../../app/Application.h"

namespace Entity
{
	SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
		: sprite(sprite)
	{
	}

	SpriteComponent::SpriteComponent(nlohmann::json json)
		: sprite(sf::Sprite(Application::instance->getResources().textures.get(json["src"]), sf::IntRect(json["rect"]["left"], json["rect"]["top"], json["rect"]["width"], json["rect"]["height"])))
		, origin({ json["origin"]["x"], json["origin"]["y"] })
	{
	};
}
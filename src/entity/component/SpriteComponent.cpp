#include "SpriteComponent.h"

namespace Framework
{
	SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
		: sprite(sprite)
	{
	}

	SpriteComponent::SpriteComponent(nlohmann::json json) 
	{
		///@TODO: json parsing
	};

	ComponentType* SpriteComponent::getStaticType()
	{
		static ComponentType type({ "Sprite" });
		return &type;
	}

	ComponentType* SpriteComponent::getType() const
	{ 
		return getStaticType(); 
	}
}

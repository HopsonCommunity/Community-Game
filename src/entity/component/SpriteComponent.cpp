#include "SpriteComponent.h"

namespace Framework
{
	SpriteComponent::SpriteComponent(const sf::Sprite& sprite)
		: sprite(sprite)
	{
	}

	ComponentType* SpriteComponent::getStaticType()
	{
		static ComponentType type({ "Sprite" });
		return &type;
	}

	ComponentType* SpriteComponent::getType() const
	{ 
		return getStaticType(); 
	};
}
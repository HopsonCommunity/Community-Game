#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Component.h"

namespace Framework
{
	class SpriteComponent : public Component
	{
	public:
		sf::Sprite sprite;
	public:
		SpriteComponent(const sf::Sprite& sprite);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
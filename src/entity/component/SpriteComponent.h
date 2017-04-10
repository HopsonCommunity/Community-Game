#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Component.h"
#include "../animation/Animator.h"

namespace Framework
{
	class SpriteComponent : public Component
	{
	public:
		sf::Sprite sprite;
		bool flipX, flipY;
	public:
		SpriteComponent(const sf::Sprite& sprite);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}
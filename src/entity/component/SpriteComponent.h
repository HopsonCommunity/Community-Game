#pragma once

#include "Component.h"

#include <SFML/Graphics/Sprite.hpp>

namespace Framework
{
	class SpriteComponent : public Component
	{
	public:
		Vec2 origin;
		sf::Sprite sprite;
		bool flipX, flipY;
	public:
		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Component.h"
#include "../animation/Animator.h"
#include "../../util/json.hpp"
#include "../../maths/Maths.h"

namespace Framework
{
	class SpriteComponent : public Component
	{
	public:
		vec2 origin;
		sf::Sprite sprite;
		bool flipX, flipY;
	public:
		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		static ComponentType* getStaticType();
		virtual ComponentType* getType() const override;;
	};
}

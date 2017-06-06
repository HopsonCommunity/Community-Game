#pragma once

#include "Component.h"
#include "../entity/animation/Animator.h"

#include <SFML/Graphics/Sprite.hpp>

namespace Entity
{
	class SpriteComponent : public Component
	{
	public:
		sf::Sprite sprite;
		bool flipX;
		bool animated;
		Animator animator;

		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override
		{
			return std::make_unique<SpriteComponent>(*this);
		}

		static const uint ID = ComponentID::Sprite;
	};
}

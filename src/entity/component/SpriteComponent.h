#pragma once

#include "Component.h"
#include "../animation/Animator.h"

#include <SFML/Graphics/Sprite.hpp>

namespace Entity
{
	class SpriteComponent : public Component
	{
	public:
		sf::Sprite sprite;
		bool flipOnVelocity; // flipX based on +- velocity
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

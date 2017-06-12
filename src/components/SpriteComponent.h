#pragma once

#include "Component.h"
#include "../graphics/Animator.h"

#include <SFML/Graphics/Sprite.hpp>

namespace Components
{
	class SpriteComponent : public Component
	{
	public:
		sf::Sprite sprite;
		bool flipX;
		bool animated;
		Graphics::Animator animator;

	public:
		SpriteComponent(const sf::Sprite& sprite);
		SpriteComponent(nlohmann::json json);

		std::unique_ptr<Component> clone() override { return std::make_unique<SpriteComponent>(*this); }

		static const uint ID = ComponentID::Sprite;
	};
}

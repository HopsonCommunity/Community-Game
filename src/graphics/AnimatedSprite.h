#pragma once

#include "../util/Types.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
	class AnimatedSprite
	{
	private:
		sf::Image* m_atlas;
		sf::Texture* m_currentFrame;

		uint m_speed;

		uint m_frameCounter = 0;
		uint m_frame = 0;

		const uint m_frameSize;
		const uint m_frameCount;
	public:
		AnimatedSprite(sf::Image* atlas, uint frameSize, uint frameCount, uint speed);
		~AnimatedSprite();

		void update();

		void glueToShape(sf::RectangleShape& shape, uint yOffset, bool flippedX);
	};
}
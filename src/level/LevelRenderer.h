#pragma once

#include "../util/Types.h"
#include "SFML/Graphics.hpp"

#include <vector>

namespace Level
{
	class LevelRenderer
	{
	private:
		static std::vector<std::pair<sf::Vector3f, sf::Sprite*>> sprites;

		static sf::RenderWindow* renderWindow;

	public:
		static void setRenderWindow(sf::RenderWindow* window);
		static void renderWallTileSide(uint32 x, uint32 y, sf::Sprite& sprite);
		static void renderWallTileTop(uint32 x, uint32 y, float height, sf::Sprite& sprite);
		static void renderEntitySprite(float x, float y, sf::Sprite& sprite);
		static void drawAll();
	};
}

#include "LevelRenderer.h"

#include <iostream>

namespace Level
{
	std::vector<std::pair<sf::Vector3f, sf::Sprite*>> LevelRenderer::sprites;
	sf::RenderWindow* LevelRenderer::renderWindow = nullptr;

	void LevelRenderer::setRenderWindow(sf::RenderWindow* window)
	{
		renderWindow = window;
	}

	void LevelRenderer::renderWallTileSide(uint32 x, uint32 y, sf::Sprite& sprite)
	{
		sf::Vector3f tilePosition(x, y + 32, 0);
		sprite.setOrigin(0, 32);
		sprites.push_back(std::make_pair(tilePosition, &sprite));
	}

	void LevelRenderer::renderWallTileTop(uint32 x, uint32 y, float height, sf::Sprite& sprite)
	{
		sf::Vector3f tilePosition(static_cast<float>(x), static_cast<float>(y + 32), height);
		sprite.setOrigin(0, 32);
		sprites.push_back(std::make_pair(tilePosition, &sprite));
	}

	void LevelRenderer::renderEntitySprite(float x, float y, sf::Sprite& sprite)
	{
		sf::Vector3f position(x, y, 0);
		sprites.push_back(std::make_pair(position, &sprite));
	}

	void LevelRenderer::drawAll()
	{
		//Sorting
		std::sort(sprites.begin(), sprites.end(),
			[](const std::pair<sf::Vector3f, sf::Sprite*>& lhs, const std::pair<sf::Vector3f, sf::Sprite*>& rhs) {
			return lhs.first.y < rhs.first.y;
		});

		//Rendering
		for (uint i = 0; i < sprites.size(); i++)
		{
			sf::Vector3f position = sprites[i].first;
			sf::Sprite* sprite = sprites[i].second;
			sprite->setPosition(position.x, position.y - position.z);
			renderWindow->draw(*sprite);
		}
		sprites.clear();
	}
}
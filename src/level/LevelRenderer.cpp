#include "LevelRenderer.h"

#include <iostream>

namespace Level
{

	std::vector<sf::Vector3f> LevelRenderer::positions;
	std::vector<sf::Sprite*> LevelRenderer::sprites;
	sf::RenderWindow* LevelRenderer::renderWindow = nullptr;

	void LevelRenderer::setRenderWindow(sf::RenderWindow* window)
	{
		renderWindow = window;
	}

	void LevelRenderer::renderWallTileSide(uint32 x, uint32 y, sf::Sprite& sprite)
	{
		sf::Vector3f tilePosition(x, y, 0);
		positions.push_back(tilePosition);
		sprites.push_back(&sprite);
	}

	void LevelRenderer::renderWallTileTop(uint32 x, uint32 y, float height, sf::Sprite& sprite)
	{
		sf::Vector3f tilePosition(x, y, height);
		positions.push_back(tilePosition);
		sprites.push_back(&sprite);
	}

	void LevelRenderer::renderEntitySprite(float x, float y, sf::Sprite& sprite)
	{
		sf::Vector3f position(x, y, 0);
		positions.push_back(position);
		sprites.push_back(&sprite);
	}

	void LevelRenderer::drawAll()
	{
		//Sorting
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			for (unsigned int j = 0; j < positions.size() - 1; j++)
			{
				if (positions[j].y > positions[j + 1].y)
				{
					sf::Vector3f position = positions[j];
					sf::Vector3f nextPosition = positions[j + 1];
					positions[j] = nextPosition;
					positions[j + 1] = position;
					sf::Sprite* sprite = sprites[j];
					sf::Sprite* nextSprite = sprites[j + 1];
					sprites[j] = nextSprite;
					sprites[j + 1] = sprite;					
				}
			}
		}

		//Rendering
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			sf::Vector3f position = positions[i];
			sf::Sprite* sprite = sprites[i];
			sprite->setPosition(position.x, position.y - position.z);
			renderWindow->draw(*sprite);
		}

		positions.clear();
		sprites.clear();
	}

}
#include "Level.h"

#include "../entity/Entity.h"
#include "LevelRenderer.h"
#include <iostream>

namespace Level
{

	Level::Level(unsigned int width, unsigned int height)
		: m_width(width),
		m_height(height)
	{
		m_tiles.resize(width*height);
	}

	void Level::addEntity(Framework::Entity* entity)
	{
		entity->level = this;
		m_entities.push_back(entity);
	}

	void Level::setTile(unsigned int x, unsigned int y, Tile::Tile& tile)
	{
		m_tiles[x + y * m_width] = &tile;
	}

	void Level::update(const Timestep& ts)
	{
		for (uint i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
				e->update(ts);
			}
		}
	}

	void Level::render(sf::RenderWindow& window)
	{
		for (uint x = 0; x < m_width; x++)
		{
			for (uint y = 0; y < m_height; y++)
			{
				if (m_tiles[x + y * m_width] != nullptr)
				{
					m_tiles[x + y * m_width]->render(x, y, window);
				}
			}
		}
		for (uint i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i] != nullptr)
			{
				Framework::Entity* e = m_entities[i];
				e->render(window);
			}
		}
		LevelRenderer::drawAll();
	}

}

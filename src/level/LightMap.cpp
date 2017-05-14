#include "LightMap.h"

#include "tile/TileMap.h"
#include "../maths/Color.h"

namespace Level
{
	LightMap::LightMap(std::vector<std::vector<TileNode*>>* tiles, uint width, uint height)
		: width(width)
		, height(height)
		, m_tiles(tiles)
	{
	}

	void LightMap::rebuildLight()
	{
		if (Dirty)
		{
			if (!Built)
				buildLight();
			Dirty = false;
		}
	}

	void LightMap::resetLight()
	{
		for (uint x = 0; x < width; x++)
			for (uint y = 0; y < height; y++)
			{
				// We can add ambient lightning later (like sky or something)
				(*m_tiles)[x][y]->light.color = sf::Color::Black;
				(*m_tiles)[x][y]->light.intensity = 0;
			}

		Built = false;
	}

	void LightMap::setIntensity(LightData* tile, sf::Color color, byte intensity) const
	{
		if (intensity > tile->intensity || canMixColors(tile->color, color))
		{
			tile->color = mixColors(tile->color, color);

			if (intensity != tile->intensity)
				tile->intensity = intensity;
		}
	}

	void LightMap::checkNeighbours(LightData* tile, uint x, uint y) const
	{
		if (x >= width || y >= height)
			return;

		int8 intensity = tile->intensity - tile->absorb;
		if (intensity < 0)
			return;

		sf::Color color = reapplyIntensity(tile->color, tile->intensity, intensity);

		if (x > 0) setIntensity(&(*m_tiles)[x - 1][y]->light, color, intensity);
		if (x < width - 1) setIntensity(&(*m_tiles)[x + 1][y]->light, color, intensity);
		if (y > 0) setIntensity(&(*m_tiles)[x][y - 1]->light, color, intensity);
		if (y < height - 1) setIntensity(&(*m_tiles)[x][y + 1]->light, color, intensity);

		color.r *= 0.9f;
		color.g *= 0.9f;
		color.b *= 0.9f;

		if (x > 0 && y < height - 1) setIntensity(&(*m_tiles)[x - 1][y + 1]->light, color, intensity);
		if (x < width - 1 && y > 0) setIntensity(&(*m_tiles)[x + 1][y - 1]->light, color, intensity);
		if (y > 0 && x > 0) setIntensity(&(*m_tiles)[x - 1][y - 1]->light, color, intensity);
		if (y < height - 1 && x < width - 1) setIntensity(&(*m_tiles)[x + 1][y + 1]->light, color, intensity);
	}

	void LightMap::addIntensity(uint x, uint y, sf::Color color, byte intensity)
	{
		Dirty = true;

		if (x >= width || y >= height)
			return;

		color = applyIntensity(color, intensity);
		(*m_tiles)[x][y]->light.color = mixColors((*m_tiles)[x][y]->light.color, color);

		if ((*m_tiles)[x][y]->light.intensity < intensity)
			(*m_tiles)[x][y]->light.intensity = intensity;
	}

	void LightMap::buildLight()
	{
		m_lightMask.clear();

		for (int32 t = 0; t < 25; t++)
			for (int32 i = 0; i < width; i++)
				for (int32 j = 0; j < height; j++)
				{
					checkNeighbours(&(*m_tiles)[i][j]->light, i , j);
				}

		for (int32 i = 0; i < width - 1; i++)
			for (int32 j = 0; j < height - 1; j++)
			{
				m_lightMask.push_back(sf::Vertex(getTileCenter(i, j), (*m_tiles)[i][j]->light.color));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i + 1, j), (*m_tiles)[i + 1][j]->light.color));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i + 1, j + 1), (*m_tiles)[i + 1][j + 1]->light.color));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i, j + 1), (*m_tiles)[i][j + 1]->light.color));
			}

		Built = true;
	}

	void LightMap::renderLight(sf::RenderWindow& window)
	{
		if (!m_lightMask.empty())
			window.draw(m_lightMask.data(), m_lightMask.size(), sf::Quads, sf::BlendMultiply);
	}
}
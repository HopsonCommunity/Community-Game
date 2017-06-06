#include "LightMap.h"

#include "tile/TileMap.h"
#include "../maths/Color.h"
#include "../util/Log.h"

namespace Level
{
	LightMap::LightMap(std::vector<std::vector<TileNode*>>* tiles, int32 width, int32 height)
		: width(width)
		, height(height)
		, m_requestedRebuild(false)
		, m_tiles(tiles)
	{
	}

	LightMap::~LightMap()
	{
		m_staticLights.clear();
	}

	void LightMap::rebuildLight()
	{
		if (!m_requestedRebuild)
			return;

		LOG_WARN("Rebuilding light..");
		m_requestedRebuild = false;

		resetLight();

		for (uint i = 0; i < m_staticLights.size(); i++)
		{
			auto light = m_staticLights[i];
			addIntensity(light->x, light->y, light->color, light->intensity);
		}

		buildLight();
	}

	void LightMap::resetLight() const
	{
		for (int32 x = 0; x < width; x++)
			for (int32 y = 0; y < height; y++)
			{
				(*m_tiles)[x][y]->light.color = Color::Black;
				(*m_tiles)[x][y]->light.intensity = 0;
			}
	}

	void LightMap::setIntensity(LightData* tile, Color color, byte intensity)
	{
		if (intensity > tile->intensity || canMixColors(tile->color, color))
		{
			tile->color = mixColors(tile->color, color);
			tile->intensity = intensity;
		}
	}

	void LightMap::addStaticLight(StaticLight* light)
	{
		m_staticLights.push_back(light);
	}

	void LightMap::removeStaticLight(StaticLight* light)
	{
		for (uint i = 0; i < m_staticLights.size(); i++)
			if (m_staticLights[i] == light)
			{
				m_staticLights.erase(m_staticLights.begin() + i);
				break;
			}
	}

	void LightMap::checkNeighbours(LightData* tile, int32 x, int32 y) const
	{
		if (x < 0 || y < 0 || x >= width || y >= height)
			return;

		char intensity = tile->intensity - tile->absorb;
		if (intensity < 0) 
			return;
		Color color = reapplyIntensity(tile->color, tile->intensity, intensity);

		if (x > 0) setIntensity(&(*m_tiles)[x - 1][y]->light, color, intensity);
		if (x < width - 1) setIntensity(&(*m_tiles)[x + 1][y]->light, color, intensity);
		if (y > 0) setIntensity(&(*m_tiles)[x][y - 1]->light, color, intensity);
		if (y < height - 1) setIntensity(&(*m_tiles)[x][y + 1]->light, color, intensity);

		color.r = byte(color.r * 0.9f);
		color.g = byte(color.g * 0.9f);
		color.b = byte(color.b * 0.9f);

		if (x > 0 && y < height - 1) setIntensity(&(*m_tiles)[x - 1][y + 1]->light, color, intensity);
		if (x < width - 1 && y > 0) setIntensity(&(*m_tiles)[x + 1][y - 1]->light, color, intensity);
		if (y > 0 && x > 0) setIntensity(&(*m_tiles)[x - 1][y - 1]->light, color, intensity);
		if (y < height - 1 && x < width - 1) setIntensity(&(*m_tiles)[x + 1][y + 1]->light, color, intensity);
	}

	void LightMap::addIntensity(int32 x, int32 y, Color color, byte intensity) const
	{
		if (x < 0 || y < 0 || x >= width || y >= height)
			return;

		color = applyIntensity(color, intensity);
		(*m_tiles)[x][y]->light.color = color;

		if ((*m_tiles)[x][y]->light.intensity < intensity)
			(*m_tiles)[x][y]->light.intensity = intensity;
	}

	Color LightMap::getTileLight(int32 x, int32 y) const
	{
		x = x < 0 ? 0 : x;
		y = y < 0 ? 0 : y;
		x = x >= width ? width - 1 : x;
		y = y >= height ? height - 1 : y;

		return (*m_tiles)[x][y]->light.color;
	}

	void LightMap::buildLight()
	{
		m_lightMask.clear();

		for (int l = LIGHT_MAX_LIGHTLEVEL - 1; l >= 0; l--)
			for (int32 i = 0; i < width; i++)
				for (int32 j = 0; j < height; j++)
					checkNeighbours(&(*m_tiles)[i][j]->light, i, j);

		for (int32 i = -1; i < width; i++)
			for (int32 j = -1; j < height; j++)
			{
				m_lightMask.push_back(sf::Vertex(getTileCenter(i, j), getTileLight(i, j)));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i + 1, j), getTileLight(i + 1, j)));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i + 1, j + 1), getTileLight(i + 1, j + 1)));
				m_lightMask.push_back(sf::Vertex(getTileCenter(i, j + 1), getTileLight(i, j + 1)));
			}
	}

	void LightMap::renderLight(sf::RenderWindow& window)
	{
		if (!m_lightMask.empty())
			window.draw(m_lightMask.data(), m_lightMask.size(), sf::Quads, sf::BlendMultiply);
	}
}

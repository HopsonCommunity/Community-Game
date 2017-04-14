#include "TileFlooding.h"

namespace Util
{
	std::vector<std::pair<Vec2i, int>> TileFlooding::tileFlooding(Vec2i entityPos, int radius, Level::Level* level)
	{
		std::vector<std::pair<Vec2i, int>> tiles;
		std::vector<std::pair<Vec2i, int>> temp;

		tiles.push_back(std::make_pair(sf::Vector2i(entityPos.x * 32, entityPos.y * 32), radius));

		int currentCost = radius;
		while (currentCost != 0)
		{
			for (const auto& val : tiles)
			{
				Vec2i pos = val.first;
				Vec2i up = pos + Vec2i(0, 32);
				Vec2i down = pos + Vec2i(0, -32);
				Vec2i left = pos + Vec2i(-32, 0);
				Vec2i right = pos + Vec2i(32, 0);

				if (!hasCoord(tiles, up))
					temp.push_back(std::make_pair(up, currentCost - 1));

				if (!hasCoord(tiles, down))
					temp.push_back(std::make_pair(down, currentCost - 1));

				if (!hasCoord(tiles, left))
					temp.push_back(std::make_pair(left, currentCost - 1));

				if (!hasCoord(tiles, right))
					temp.push_back(std::make_pair(right, currentCost - 1));
			}

			for (const auto& val : temp)
				tiles.push_back(val);

			temp.clear();

			currentCost--;
		}

		return tiles;
	}

	std::vector<Framework::Entity*> TileFlooding::getAllEntitesNearOtherEntity(Vec2i entityPos, int radius, Level::Level* level)
	{
		auto tiles = tileFlooding(entityPos, radius, level);

		std::vector<Framework::Entity*> entities;
		
		for (const auto& tile : tiles)
		{
			Framework::Entity* entity = level->getEntityOnTile(tile.first.x, tile.first.y);
			if (entity != nullptr)
				entities.push_back(entity);
		}

		return entities;
	}

	bool TileFlooding::hasCoord(const std::vector<std::pair<Vec2i, int>>& tiles, Vec2i toTest)
	{
		for (const auto& tile : tiles)
			if (tile.first == toTest)
				return true;

		return false;
	}
}
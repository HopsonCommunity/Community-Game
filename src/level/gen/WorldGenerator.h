#pragma once

#include "Leaf.h"

#include "../../Types.h"
#include "../../maths/Random.h"
#include "../tile/TileMap.h"

#include <SFML/System/Vector2.hpp>

namespace WGenerator
{
	struct Map {
		std::vector<std::vector<byte>> tiles;
		sf::Vector2<uint> playerPosition;
	};

	class WorldGenerator
	{
	public:
		WorldGenerator(uint t_width, uint t_height, uint t_seed, uint t_minSize = 15, uint t_maxSize = 40);

		void generateMap();
		Map getMap();

	private:

		std::vector<std::shared_ptr<Rect> > getRooms();
		std::vector<std::shared_ptr<Rect> > getRandomSquares();
		std::vector<std::shared_ptr<Rect> > getHalls();
		std::vector<std::vector<byte>> render(std::vector<std::pair<std::vector<std::shared_ptr<Rect>>, byte>> data);
		std::vector<std::vector<byte >> generateWalls(std::vector<std::vector<byte >> map, byte wallID, byte wallSideID);

		sf::Vector2<uint> placePlayer(uint roomId);

		uint m_width;
		uint m_height;
		uint m_minSize;
		uint m_maxSize;
		uint m_seed;
		Random::Generator<> m_generator;
		std::vector<std::shared_ptr<Leaf> > m_leafs;
	};
}

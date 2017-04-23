#pragma once

#include "Leaf.h"

#include "../../Types.h"
#include "../../maths/Random.h"
#include "../Tile/TileMap.h"

#include <SFML/System/Vector2.hpp>

namespace WGenerator
{
	struct Map {
		Level::TileMap tileMap;
		sf::Vector2<uint> playerPosition;
	};

	class WorldGenerator
	{
	public:
		WorldGenerator(uint t_width, uint t_height, uint t_seed, uint t_minSize = 15, uint t_maxSize = 40);

		void generateMap();
		Map getMap();

	private:

		std::vector<std::shared_ptr<Rectangle> > getRooms();
		std::vector<std::shared_ptr<Rectangle> > getRandomSquares();
		std::vector<std::shared_ptr<Rectangle> > getHalls();
		Level::TileMap render(std::vector<std::pair<std::vector<std::shared_ptr<Rectangle>>, byte>> data);

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

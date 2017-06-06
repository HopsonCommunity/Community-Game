#pragma once

#include "Leaf.h"

#include "../../Types.h"
#include "../../maths/Random.h"

#include "../tile/TileMap.h"

namespace WGenerator
{
	struct Map 
	{
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
		std::vector<std::shared_ptr<maths::IntRectangle>> getRooms();
		std::vector<std::shared_ptr<maths::IntRectangle>> getRandomSquares();
		std::vector<std::shared_ptr<maths::IntRectangle>> getHalls();
		std::vector<std::vector<byte>> render(std::vector<std::pair<std::vector<std::shared_ptr<maths::IntRectangle>>, byte>> data) const;

		sf::Vector2<uint> placePlayer(uint roomId);

		uint m_width, m_height;
		int32 m_minSize, m_maxSize;
		uint m_seed;
		Random::Generator<> m_generator;
		std::vector<std::shared_ptr<Leaf>> m_leafs;
	};
}

#pragma once

#include "Leaf.h"

#include "../../Types.h"
#include "../tile/TileMap.h"
#include "../../util/json.hpp"

#include "../tile/TileMap.h"

namespace WGenerator
{
	struct Map
	{
		Level::TileMap::AddList addList;
		sf::Vector2<uint> playerPosition;
	};

	class WorldGenerator
	{
	public:
		WorldGenerator(std::string folderName);

		void generateMap();
		Map getMap();

	private:
		nlohmann::json mainJSON;
		nlohmann::json obligatoryJSON;
		nlohmann::json randomJSON;

		std::vector<std::shared_ptr<IntRectangle>> getRooms();
		std::vector<std::shared_ptr<IntRectangle>> getRandomSquares();
		std::vector<std::shared_ptr<IntRectangle>> getHalls();
		void render(std::vector<std::pair<std::vector<std::shared_ptr<IntRectangle>>, byte>> data);

		void renderRooms();
		void renderRoom(IntRectangle rect, nlohmann::json json);

		sf::Vector2<uint> placePlayer(uint roomId);

		Random::Generator<> m_generator;
		std::vector<std::shared_ptr<Leaf>> m_leafs;

		Level::TileMap::AddList addList;
	};
}


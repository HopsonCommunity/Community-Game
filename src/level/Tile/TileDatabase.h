#pragma once

#include "Tile.h"

#include "../../Common.h"
#include "../../maths/Maths.h"
#include "../../util/json.hpp"
#include "../../util/FileUtil.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

namespace Level
{
	class TileDatabase
	{
	public:
		static TileDatabase& get();

	public:
		TileDatabase();

		template <typename T>
		void loadTile(const TileID& id, const std::string& filePath);

		Tile* getTile(byte id);

	private:
		std::vector<std::unique_ptr<Tile>> m_tiles;
	};

	template<typename T>
	void TileDatabase::loadTile(const TileID& id, const std::string& filePath)
	{
		using json = nlohmann::json;
		auto source = getFileContents("res/tiles/" + filePath + ".json");

		json json_ = json::parse(source.c_str());

		///TODO: Metadata

		//bool& b_passable = json_["Passable"].get<bool>;
		//bool& b_breakable = json_["Breakable"].get<bool>;
		int32 passable = true ? (int32)TileFlags::PASSABLE : 0x0;
		int32 breakable = false ? (int32)TileFlags::BREAKABLE : 0x0;

		auto uv = json_["Texture"].get<std::vector<short>>();

		m_tiles.push_back(std::make_unique<T>((byte)id, passable | breakable, sf::IntRect(uv[0] * TILE_SIZE, uv[1] * TILE_SIZE, TILE_SIZE, TILE_SIZE)));
	}
}
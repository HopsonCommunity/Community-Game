#pragma once

#include "Tile.h"

#include "../../Common.h"
#include "../../maths/Maths.h"
#include "../../util/Log.h"
#include "../../util/json.hpp"
#include "../../util/FileUtil.h"

#include <SFML/Graphics.hpp>

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

        const TileData getTileData(byte id) const { return m_tiles[id]->getData(); };

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

		int32 passable = json_["Passable"] ? (int32)TileFlags::PASSABLE : 0x0;
		int32 breakable = json_["Breakable"] ? (int32)TileFlags::BREAKABLE : 0x0;

		auto uv = json_["Texture"].get<std::vector<int32>>();

		m_tiles[(byte)id] = std::make_unique<T>((byte)id, passable | breakable, sf::IntRect(uv[0], uv[1], 1, 1));
	}
}

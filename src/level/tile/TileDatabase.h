#pragma once

#include "Tile.h"

#include "../../Common.h"
#include "../../maths/maths.h"
#include "../../util/Log.h"
#include "../../util/json.hpp"
#include "../../util/FileUtil.h"

#include <SFML/Graphics.hpp>

namespace Level
{
	class TileDatabase
	{
	public:
		TileDatabase();

		template <typename T>
		void loadTile(const TileID& id, const std::string& filePath);

		Tile* getTile(byte id);

		static TileDatabase& get() { static TileDatabase db; return db; };

        const TileData& getTileData(byte id) const { return m_tiles[id]->getData(); };

	private:
		std::vector<std::unique_ptr<Tile>> m_tiles;
	};

	template <typename T>
	void TileDatabase::loadTile(const TileID& id, const std::string& filePath)
	{
		using json = nlohmann::json;
		auto source = getFileContents("res/tiles/" + filePath + ".json");

		json json_ = json::parse(source.c_str());

		///TODO: Metadata

		int32 passable = json_["Passable"] ? (int32)TileFlags::PASSABLE : 0x0;
		int32 breakable = json_["Breakable"] ? (int32)TileFlags::BREAKABLE : 0x0;

		FloatRectangle bounds = { { 0, 0 },{ 0, 0 } };
		if (passable == 0x0)
		{
			if (json_.find("CollisionBox") == json_.end())
				LOG_WARN("[JSON] Entity with PhysicsComponent but without FloatRectangle! Setting to ", bounds, " as default.");
			else
				bounds = { { json_["CollisionBox"]["x"], json_["CollisionBox"]["y"] },{ json_["CollisionBox"]["width"], json_["CollisionBox"]["height"] } };
		}
		
		std::vector<nlohmann::json> textures_ = json_["Textures"];
		std::vector<Vec2> textures;
		for (uint i = 0; i < textures_.size(); i++)
		{
			nlohmann::json at = textures_[i];
			auto vec = at.get<std::vector<float>>();
			textures.push_back(Vec2(vec[0], vec[1]));
		}
			
		m_tiles[(byte)id] = std::make_unique<T>((byte)id, passable | breakable, bounds, textures);
	}
}

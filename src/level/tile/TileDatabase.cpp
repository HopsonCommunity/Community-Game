#include "TileDatabase.h"

#include "../../util/Log.h"

namespace Level
{
	TileDatabase& TileDatabase::get()
	{
		static TileDatabase td;
		return td;
	}

	TileDatabase::TileDatabase()
		: m_tiles((uint)TileID::End)
	{
		loadTile<TileDefault>(TileID::Void, "Void");
		loadTile<TileDefault>(TileID::Dungeon_BrickWall, "dungeon/BrickWall");
		loadTile<TileDefault>(TileID::Dungeon_BrickFloor, "dungeon/BrickFloor");
		ASSERT(getTile((byte)TileID::Void), "Void");
		ASSERT(getTile((byte)TileID::Dungeon_BrickWall), "BrickWall");
		ASSERT(getTile((byte)TileID::Dungeon_BrickFloor), "BrickFloor");
	}

	inline Tile* TileDatabase::getTile(byte id)
	{
		return m_tiles[id].get();
	}
}

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
		loadTile<TileDefault>(TileID::Cobblestone, "dungeon/Cobblestone");
		LOG_INFO(getTile((BYTE)TileID::Cobblestone)->getData().texture.left, " | ", getTile((BYTE)TileID::Cobblestone)->getData().texture.top);
		ASSERT(getTile((byte)TileID::Void), "Void");
		ASSERT(getTile((byte)TileID::Cobblestone), "Cobblestone");
	}

	inline Tile* TileDatabase::getTile(byte id)
	{
		return m_tiles[id].get();
	}
}
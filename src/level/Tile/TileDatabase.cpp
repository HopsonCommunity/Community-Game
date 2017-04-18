#include "TileDatabase.h"

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
	}

	inline Tile* TileDatabase::getTile(byte id)
	{
		return m_tiles[id].get();
	}
}
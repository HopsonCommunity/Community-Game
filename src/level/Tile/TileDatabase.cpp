#include "TileDatabase.h"

#include "../../util/Types.h"

namespace Level { namespace Tile
{
    Database& Database::get()
    {
        static Database database;
        return database;
    }

    Database::Database()
    :   m_tiles ((uint32)ID::Tile_Types_Count)
    {
        registerTile(ID::Light_Stone, "Light_Stone");
    }

    void Database::registerTile(ID id, std::string&& name)
    {
        m_tiles[(int)id] = Type(std::move(name));
    }
}}

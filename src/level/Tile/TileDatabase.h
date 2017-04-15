#pragma once

#include "TileType.h"
#include "TileID.h"

#include "../../util/Types.h"

#include <vector>

namespace Level { 
namespace Tile
{
    class Database
    {
        public:
            static Database& get();

            Database();

            const  Type::Data& getTileData(ID id) const
            {
                return m_tiles[uint8(id)].getData();
            }

            const  Type::Data& getTileData(uint8 id) const
            {
                return m_tiles[id].getData();
            }

        private:
            void registerTile(ID id, std::string&& name);

            std::vector<Type> m_tiles;
    };
}}


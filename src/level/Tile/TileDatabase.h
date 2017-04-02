#pragma once

#include <vector>

#include "TileType.h"
#include "TileID.h"

namespace Level { namespace Tile
{
    class Database
    {
        public:
            static Database& get();

            Database();

        private:
            void registerTile(ID id, std::string&& name);

            std::vector<Type> m_tiles;
    };


}}


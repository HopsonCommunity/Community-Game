#include "TileType.h"

namespace Level{ namespace Tile
{
    Type::Type(std::string&& fileName)
    {

    }

    const Type::Data& Type::getData()
    {
        return m_data;
    }


}}

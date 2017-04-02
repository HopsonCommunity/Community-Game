#include "TileType.h"

namespace Level{ namespace Tile
{
    Type::Type(std::string&& fileName)
    {
        const std::string fileNamePath = "res/tiles/" + fileName + ".tile";
        ///@TODO Load tile data here
    }

    const Type::Data& Type::getData() const
    {
        return m_data;
    }


}}

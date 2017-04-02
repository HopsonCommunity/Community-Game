#include "TileType.h"

#include <fstream>

namespace Level{ namespace Tile
{
    Type::Type(std::string&& fileName)
    {
        const std::string fileNamePath = "res/tiles/" + fileName + ".tile";
        ///@TODO Load tile data here


        std::ifstream inFile(fileNamePath);
        if (!inFile.is_open())
        {
            ///@TODO Handle this error
        }

        //Loads up the tile data from the "res/tiles/" folder
        std::string line;
        while (std::getline(inFile, line))
        {
            if (line == "Name")
            {
                std::getline(inFile, line);
                m_data.name = line;
            }
            else if (line == "Texture")
            {
                inFile >> m_data.texCoords.x >> m_data.texCoords.y;
            }
            else if (line == "ID")
            {
                int temp;
                inFile >> temp;
                m_data.id = (ID)temp;
            }
            else if (line == "Variation")
            {
                inFile >> m_data.textureVariations;
            }
            else if (line == "")
            {
                continue;
            }
            else
            {
                ///@TODO Handle this error
            }
        }

    }

    const Type::Data& Type::getData() const
    {
        return m_data;
    }


}}

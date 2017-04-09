#pragma once

#include <SFML/Graphics.hpp>

#include "TileID.h"
#include "../../util/Types.h"

namespace Level {
namespace Tile
{
    class Type
    {
        public:
            struct Data
            {
                std::string     name;
                sf::Vector2f    texCoords;
                ID              id;
                uint32          textureVariations;
            };

            Type() = default;
            Type(std::string&& fileName);

            const Data& getData() const;

        private:
            Data m_data;
    };
}}

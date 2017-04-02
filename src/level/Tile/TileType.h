#pragma once

#include <SFML/Graphics.hpp>

#include "TileID.h"

namespace Level{ namespace Tile
{
    class Type
    {
        public:
            struct Data
            {
                std::string  name;
                sf::Vector2i texCoords;
                ID           id;
                uint8        textureVariations;
            };

            Type() = default;
            Type(std::string&& fileName);

            const Data& getData() const;

        private:
            Data m_data;
    };
}}

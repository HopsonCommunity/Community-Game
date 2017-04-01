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
            };

            Type(std::string&& fileName);
            Type(const Type& other) = delete;
            Type& operator = (const Type& other) = delete;

            const Data& getData() const;

        private:
            Data m_data;
    };
}}

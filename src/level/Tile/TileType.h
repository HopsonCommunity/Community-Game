#pragma once

#include "TileID.h"

#include "../../maths/Maths.h"

#include <SFML/Graphics.hpp>

namespace Level {
namespace Tile
{
    class Type
    {
        public:
            struct Data
            {
                std::string     name;
                Vec2    texCoords;
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

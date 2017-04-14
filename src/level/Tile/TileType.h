#pragma once

#include <SFML/Graphics.hpp>

#include "TileID.h"
#include "../../util/Types.h"
#include "../../maths/Maths.h"

namespace Level {
namespace Tile
{
    class Type
    {
        public:
            struct Data
            {
                std::string     name;
                vec2    texCoords;
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

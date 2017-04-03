#pragma once

#include "../../util/Types.h"
#include "../LevelConstants.h"
#include <SFML\Graphics.hpp>

#include <memory>

namespace Level
{
namespace Tile
{

		class Tile
		{
            public:
                static const sf::Texture* tileset;
                static std::unique_ptr<Tile> fLightStone;
                static std::unique_ptr<Tile> fMedStone;
                static std::unique_ptr<Tile> fDarkStone;
                static std::unique_ptr<Tile> stoneWall;

                static void loadTiles();
				static void deleteTiles() {};

            protected:
                uint8 m_id;
                sf::Sprite m_sprite;

            private:
                Tile() {}

            public:
                Tile(uint8 id, sf::Sprite sprite);

                virtual void render(uint32 x, uint32 y, sf::RenderWindow& window);
		};

	}
}

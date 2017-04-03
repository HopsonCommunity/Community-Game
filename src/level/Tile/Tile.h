#pragma once

#include "../../util/Types.h"
#include <SFML\Graphics.hpp>

namespace Level
{
	namespace Tile
	{

#define TILE_SIZE 32

		class Tile
		{
		public:
			static const sf::Texture* tileset;
			static Tile* fLightStone;
			static Tile* fMedStone;
			static Tile* fDarkStone;
			static Tile* stoneWall;

			static void loadTiles();
			static void deleteTiles();

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

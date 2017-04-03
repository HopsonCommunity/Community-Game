#include "Tile.h"

#include <iostream>
#include "WallTile.h"
#include "../../Application.h"

#include <SFML/Graphics/View.hpp>

namespace Level
{
	namespace Tile
	{

		const sf::Texture* Tile::tileset = nullptr;
		Tile* Tile::fLightStone; 
		Tile* Tile::fMedStone;
		Tile* Tile::fDarkStone;
		Tile* Tile::stoneWall;

		void Tile::loadTiles()
		{
			tileset = &Application::instance->getResources().textures.get("tile_atlas");

			fLightStone = new Tile(0, sf::Sprite(*tileset, sf::IntRect(0, 32, 32, 32)));
			fMedStone = new Tile(1, sf::Sprite(*tileset, sf::IntRect(0, 64, 32, 32)));
			fDarkStone = new Tile(2, sf::Sprite(*tileset, sf::IntRect(0, 96, 32, 32)));
			stoneWall = new WallTile(3, sf::Sprite(*tileset, sf::IntRect(0, 128, 32, 32)), sf::Sprite(*tileset, sf::IntRect(0, 160, 32, 32)), 32);

			sf::View view;
			sf::Sprite sprite;
		}

		void Tile::deleteTiles()
		{
			delete tileset;
			delete fLightStone;
			delete fMedStone;
			delete fDarkStone;
			delete stoneWall;
		}

		Tile::Tile(uint8 id, sf::Sprite sprite)
			: m_id(id),
			m_sprite(sprite) 
		{}

		void Tile::render(uint32 x, uint32 y, sf::RenderWindow& window)
		{
			m_sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			window.draw(m_sprite);
		}

	}
}
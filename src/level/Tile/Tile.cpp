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
		std::unique_ptr<Tile> Tile::fLightStone;
		std::unique_ptr<Tile> Tile::fMedStone;
		std::unique_ptr<Tile> Tile::fDarkStone;
		std::unique_ptr<Tile> Tile::stoneWall;

		void Tile::loadTiles()
		{
			tileset = &Application::instance->getResources().textures.get("tile_atlas");

			fLightStone = std::make_unique<Tile>(0, sf::Sprite(*tileset, sf::IntRect(0, 32, 32, 32)));
			fMedStone   = std::make_unique<Tile>(1, sf::Sprite(*tileset, sf::IntRect(0, 64, 32, 32)));
			fDarkStone  = std::make_unique<Tile>(2, sf::Sprite(*tileset, sf::IntRect(0, 96, 32, 32)));
			stoneWall   = std::make_unique<WallTile>(3, sf::Sprite(*tileset, sf::IntRect(0, 128, 32, 32)), sf::Sprite(*tileset, sf::IntRect(0, 160, 32, 32)), 32);

			sf::View view;
			sf::Sprite sprite;
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

#include "Tile.h"

#include "WallTile.h"

#include "../Level.h"
#include "../../Application.h"

#include <SFML/Graphics/View.hpp>

#include <iostream>

namespace Level {
namespace Tile
{
	const sf::Texture* Tile::tileset = nullptr;
	std::unique_ptr<Tile> Tile::fLightStone;
	std::unique_ptr<Tile> Tile::fMedStone;
	std::unique_ptr<Tile> Tile::fDarkStone;
	std::unique_ptr<Tile> Tile::stoneWall;

	void Tile::loadTiles()
	{
		tileset = &Application::instance->getResources().textures.get("tiles/atlas");

		fLightStone = std::make_unique<Tile>(0,     sf::Sprite(*tileset, sf::IntRect(0, static_cast<int>(TILE_SIZE),	 static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), false);
		fMedStone   = std::make_unique<Tile>(1,     sf::Sprite(*tileset, sf::IntRect(0, static_cast<int>(TILE_SIZE) * 2, static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), false);
		fDarkStone  = std::make_unique<Tile>(2,     sf::Sprite(*tileset, sf::IntRect(0, static_cast<int>(TILE_SIZE) * 3, static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), false);
		stoneWall   = std::make_unique<WallTile>(3, sf::Sprite(*tileset, sf::IntRect(0, static_cast<int>(TILE_SIZE) * 4, static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), 
													sf::Sprite(*tileset, sf::IntRect(0, 160, static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), TILE_SIZE, true);
	}

	Tile::Tile(byte id, sf::Sprite sprite, bool solid)
		: m_id(id),
		m_sprite(sprite),
		m_solid(solid)
	{}

	void Tile::render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window)
	{
		Tile* nextTile = level.getTile(x, y + 1);
		if (nextTile == nullptr || !nextTile->isSolid())
		{
			m_sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			window.draw(m_sprite);
		}
	}
}}

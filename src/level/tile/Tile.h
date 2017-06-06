#pragma once

#include "../../maths/Maths.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace Level
{
	class Level;

	enum class TileFlags : int32
	{
		PASSABLE = 0x0001,
		BREAKABLE = 0x0002
	};

	enum class TileID : byte
	{
		Void = 0,
		Dungeon_BrickWall = 1,
		Dungeon_BrickFloor = 2,
		Dungeon_BrickWallSide = 3,

		End
	};

	struct TileData
	{
		byte id;
		int32 flags;
		sf::IntRect texture;
	};

	class Tile
	{
	public:
		Tile(byte id, int32 flags, sf::IntRect texture);

		// Each tile can have its own render logic
		virtual void render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window) = 0;

		// Fancy function returns :D (I don't even know if this would compile in GCC)
		inline auto getID() -> byte const { return m_data.id; }

        inline auto getData() -> TileData const { return m_data; }

		inline auto hasFlag(int32 flag) -> bool const { return (bool)(m_data.flags & flag); }

	private:
		TileData m_data;
	};

	class TileDefault : public Tile
	{
	public:
		TileDefault(byte id, int32 flags, sf::IntRect texture);

		void render(uint32 x, uint32 y, Level& level, sf::RenderWindow& window) override;
	};
}

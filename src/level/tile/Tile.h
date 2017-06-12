#pragma once

#include "../../Common.h"

#include "../../maths/maths.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Renderable2D;
	class Renderer2D;
}

namespace Level
{
	class Level;
	class TileDatabase;
	struct TileNode;

	enum class TileFlags : int32
	{
		PASSABLE = BIT(0),
		BREAKABLE = BIT(1)
	};

	enum class TileID : byte
	{
		Void = 0,
		Dungeon_BrickWall = 1,
		Dungeon_BrickFloor = 2,

		End
	};

	struct TileData
	{
		byte id;
		int32 flags;
		FloatRectangle bounds;
	};

	static Graphics::Renderable2D* renderable;

	class Tile
	{
	public:
		Tile(byte id, int32 flags, const FloatRectangle& bounds);

		// Each tile can have its own render logic
		virtual void render(uint x, uint y, TileDatabase& database, Graphics::Renderer2D& renderer, std::vector<std::vector<TileNode*>>& layer) = 0;

		inline byte getID() const { return m_data.id; }

        inline const TileData& getData() const { return m_data; }

		inline bool hasFlag(int32 flag) const { return (bool)(m_data.flags & flag); }

	protected:
		TileData m_data;
	};

	class TileDefault : public Tile
	{
	public:
		TileDefault(byte id, int32 flags, const FloatRectangle& bounds, const std::vector<Vec2> textures);

		void render(uint x, uint y, TileDatabase& database, Graphics::Renderer2D& renderer, std::vector<std::vector<TileNode*>>& layer) override;

	private:
		Vec2 m_texture;
	};

	class TileWall : public Tile
	{
	public:
		TileWall(byte id, int32 flags, const FloatRectangle& bounds, const std::vector<Vec2> textures);

		void render(uint x, uint y, TileDatabase& database, Graphics::Renderer2D& renderer, std::vector<std::vector<TileNode*>>& layer) override;

	private:
		Vec2 m_sideTexture;
		Vec2 m_topTexture;
	};
}

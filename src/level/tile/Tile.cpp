#include "Tile.h"

#include "../../graphics/Renderable2D.h"
#include "../../level/Level.h"
#include "TileDatabase.h"

namespace Level
{
	Tile::Tile(byte id, int32 flags, const FloatRectangle& bounds)
		: m_data({id, flags, bounds})
	{
		if (!renderable)
			renderable = new Graphics::Renderable2D({ 0, 0 }, { TILE_SIZE, TILE_SIZE }, sf::Color::White);
	}

	TileDefault::TileDefault(byte id, int32 flags, const FloatRectangle& bounds, const std::vector<Vec2> textures)
		: Tile(id, flags, bounds)
		, m_texture(textures[0])
	{
	}

	void TileDefault::render(uint x, uint y, TileDatabase& database, Graphics::Renderer2D& renderer, std::vector<std::vector<TileNode*>>& layer)
	{
		Vec2& renderTilePos = renderable->m_position;
		renderTilePos.x = x * TILE_SIZE;
		renderTilePos.y = y * TILE_SIZE;

		const float tx = m_texture.x * TILE_SIZE;
		const float ty = m_texture.y * TILE_SIZE;

		// Pointer arithmetic is faster than [] operator
		Vec2* uvPtr = const_cast<Vec2*>(&renderable->getUVs()[0]);
		*uvPtr++ = { tx, ty };
		*uvPtr++ = { tx, ty + TILE_SIZE};
		*uvPtr++ = { tx + TILE_SIZE, ty + TILE_SIZE };
		*uvPtr = { tx + TILE_SIZE, ty };

		renderer.submit(renderable);
	}
	
	TileWall::TileWall(byte id, int32 flags, const FloatRectangle& bounds, const std::vector<Vec2> textures)
		: Tile(id, flags, bounds)
		, m_sideTexture(textures[0])
		, m_topTexture(textures[1])
	{
	}
	
	void TileWall::render(uint x, uint y, TileDatabase& database, Graphics::Renderer2D& renderer, std::vector<std::vector<TileNode*>>& layer)
	{	
		/// Render side
		Vec2& renderTilePos = renderable->m_position;
		renderTilePos.x = x * TILE_SIZE;

		if (layer[x][y + 1]->id != TileID::Dungeon_BrickWall)
		{
			renderTilePos.y = y * TILE_SIZE;

			const float tx = m_sideTexture.x * TILE_SIZE;
			const float ty = m_sideTexture.y * TILE_SIZE;

			// Pointer arithmetic is faster than [] operator
			Vec2* uvPtr = const_cast<Vec2*>(&renderable->getUVs()[0]);
			*uvPtr++ = { tx, ty };
			*uvPtr++ = { tx, ty + TILE_SIZE };
			*uvPtr++ = { tx + TILE_SIZE, ty + TILE_SIZE };
			*uvPtr = { tx + TILE_SIZE, ty };

			renderer.submit(renderable);
		}

		/// Render top
		renderTilePos.y = y * TILE_SIZE - 32;

		const float tx = m_topTexture.x * TILE_SIZE;
		const float ty = m_topTexture.y * TILE_SIZE;

		// Pointer arithmetic is faster than [] operator
		Vec2* uvPtr = const_cast<Vec2*>(&renderable->getUVs()[0]);
		*uvPtr++ = { tx, ty };
		*uvPtr++ = { tx, ty + TILE_SIZE };
		*uvPtr++ = { tx + TILE_SIZE, ty + TILE_SIZE };
		*uvPtr = { tx + TILE_SIZE, ty };

		renderer.submit(renderable, Graphics::Renderer2D::RenderOrder::AFTER);
	}
}

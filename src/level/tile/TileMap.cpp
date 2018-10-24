#include "TileMap.h"

#include "TileDatabase.h"

#include "../LightMap.h"

#include "../../resources/ResourceHolder.h"
#include "../../app/Application.h"
#include "../../app/states/StatePlaying.h"
#include "../../components/PhysicsComponent.h"

namespace Level 
{
	TileMap::TileMap(uint width, uint height) 
		: width(width)
		, height(height)
		, m_renderTile(Graphics::Renderable2D({ 0, 0 }, { TILE_SIZE, TILE_SIZE }, sf::Color::White))
	{
		addLayer();
	
		m_renderState.texture = &Application::get().getTexture("/tile_atlas");
	
		m_renderer.m_states.texture = &Application::get().getTexture("/tile_atlas");
	}

	TileMap::~TileMap()
	{
		m_layers.clear();
	}
	
	void TileMap::addLayer() 
	{
		TileLayer* layer = new TileLayer();
		
		layer->lightMap = new LightMap(&layer->tiles, width, height);
		for (uint i = 0; i < width; i++)
		{
			std::vector<TileNode*> col;
			for (uint j = 0; j < height; j++)
				col.push_back(new TileNode{});
			layer->tiles.push_back(col);
		}

		m_layers.push_back(layer);
	}

	void TileMap::addTile(uint x, uint y, uint layer, byte id, byte metadata) 
	{
		addTiles(layer, { std::make_tuple(x, y, id, metadata) });
	}

	void TileMap::addTiles(uint layer, const AddList& tiles)
	{
		if (tiles.empty())
			return;

		for (auto t : tiles)
		{
			uint x, y;
			byte id, metadata;

			std::tie(x, y, id, metadata) = t;

			qAddTile(layer, x, y, id, metadata);
		}
		requestRebuild(layer);
	}

	void TileMap::qAddTile(uint layer, uint x, uint y, byte id, byte metadata)
	{
		if (m_layers.size() > layer)
		{
			TileNode* node = getTile(layer, x, y);
			if (node)
			{
				node->id = TileID(id);
				node->metadata = metadata;
				byte absorb = 2;
				if (TileID(id) == TileID::Dungeon_BrickWall)
					absorb = 30;
				node->light.absorb = absorb;
			}
		}
		else
		{
			addLayer();
			qAddTile(layer, x, y, id, metadata);
		}
	}

	TileNode* TileMap::getTile(uint layer, uint x, uint y)
	{
		if (x >= width || y >= height)
			return nullptr;

		return m_layers[layer]->tiles[x][y];
	}

	void TileMap::render(sf::RenderWindow& window, const IntRectangle& renderRegion)
	{
		TileDatabase& database = TileDatabase::get();

		m_renderer.begin();
		for (auto layer : m_layers)
			for (int32 x = renderRegion.getMinimumBound().x; x < renderRegion.getMaximumBound().x; x++)
			{
				if (x >= (int32)width || x <= 0)
					continue;
				
				for (int32 y = renderRegion.getMinimumBound().y; y < renderRegion.getMaximumBound().y; y++)
				{
					if (y >= (int32)height || y <= 0)
						continue;

					// --
					// Do not render tiles that can not be seen (dark)
					int32 xa = x - 1 <= 0 ? 1 : x - 1, xb = x + 1 >= (int32)height ? height - 1 : x + 1;
					int32 ya = y - 1 <= 0 ? 1 : y - 1, yb = y + 1 >= (int32)height ? height - 1 : y + 1;

					if (layer->tiles[xa][ya]->light.color == Color::Black && layer->tiles[xb][yb]->light.color == Color::Black
						&& layer->tiles[xa][yb]->light.color == Color::Black && layer->tiles[xb][ya]->light.color == Color::Black)
						continue;
					//--

					database.getTile((byte)layer->tiles[x][y]->id)->render(x, y, database, m_renderer, layer->tiles);
				}
			} 
	}

	void TileMap::presentBefore(sf::RenderWindow& window)
	{
		m_renderer.present(window);
	}

	void TileMap::presentAfter(sf::RenderWindow& window)
	{
		m_renderer.present(window, Graphics::Renderer2D::RenderOrder::AFTER);
	}

	void TileMap::renderLight(sf::RenderWindow& window)
	{
		for (auto layer : m_layers)
			layer->lightMap->renderLight(window);
	}

	void TileMap::addStaticLight(uint layer, StaticLight* light)
	{
		m_layers[layer]->lightMap->addStaticLight(light);
	}

	void TileMap::removeStaticLight(uint layer, StaticLight* light)
	{
		m_layers[layer]->lightMap->removeStaticLight(light);
	}

	void TileMap::requestRebuild(uint layer)
	{
		m_layers[layer]->lightMap->requestRebuild();
	}

	void TileMap::light()
	{
		for (auto& layer : m_layers)
			layer->lightMap->rebuildLight();
	}
}


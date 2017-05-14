#include "TileMap.h"

#include "TileDatabase.h"

#include "../LightMap.h"

#include "../../resources/ResourceHolder.h"
#include "../../app/Application.h"
#include "../../app/states/StatePlaying.h"
#include "../../entity/component/PhysicsComponent.h"

namespace Level 
{
	TileMap::TileMap(uint width, uint height) 
		: width(width)
		, height(height)
	{
		addLayer();
		generateVertexArray(0);
	
		m_renderState.texture = &Application::instance->getResources().textures.get("/tiles/atlas");

		m_lmap = new LightMap(&m_layers[0]->tiles, width, height);
	}

	TileMap::~TileMap()
	{
		for (auto& l : m_layers)
			l->tiles.clear();
	}
	
	void TileMap::addLayer() 
	{
		auto layer = std::make_unique<TileLayer>();

		for (uint i = 0; i < width; i++)
		{
			std::vector<TileNode*> col;
			for (uint j = 0; j < height; j++)
				col.push_back(new TileNode{});
			layer->tiles.push_back(col);
		}

		layer->vertexArray.reserve(width * height * 4);
		m_layers.push_back(std::move(layer));
	}

	void TileMap::addTile(uint x, uint y, uint layer, byte id, byte metadata) 
	{
		qAddTile(layer, x, y, id, metadata);
		generateVertexArray(layer);
	}

	// If you want to change multiple tiles at once it's better to batch
	// them so you generate the vertexarray after all have been added.
	// Instead of using only addTile() and generating the VA for every tile.
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
		generateVertexArray(layer);
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
				byte absorb = 5;
				if (TileID(id) == TileID::Dungeon_BrickFloor)
					absorb = 6;
				else if (TileID(id) == TileID::Dungeon_BrickWall)
					absorb = 20;
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

	void TileMap::render(sf::RenderWindow& window)
	{
		for (auto& layer : m_layers)
			window.draw(layer->vertexArray.data(), layer->vertexArray.size(), sf::PrimitiveType::Quads, m_renderState);
	}

	void TileMap::generateVertexArray(byte layer)
	{
		auto& l = m_layers[layer];
		l->vertexArray.clear();

		FOR_EACH_TILE(addTileVertices(l.get(), uint(x * TILE_SIZE), uint(y * TILE_SIZE), m_layers[layer]->tiles[x][y]))
	}

	void TileMap::addTileVertices(TileLayer* layer, uint xa, uint ya, TileNode* tile)
	{
		if (tile->id == TileID::Void)
			return;

		sf::IntRect uvs = TileDatabase::get().getTileData(byte(tile->id)).texture;

		float tx = uvs.left * TILE_SIZE;
		float ty = uvs.top * TILE_SIZE;

		float x = static_cast<float>(xa), y = static_cast<float>(ya);
		
		layer->vertexArray.push_back({ { x, y },                         { tx, ty } });
		layer->vertexArray.push_back({ {x + TILE_SIZE, y },              { tx + TILE_SIZE, ty } });
		layer->vertexArray.push_back({ { x + TILE_SIZE, y + TILE_SIZE }, { tx + TILE_SIZE, ty + TILE_SIZE } });
		layer->vertexArray.push_back({ { x, y + TILE_SIZE },             { tx, ty + TILE_SIZE } });
	}
}


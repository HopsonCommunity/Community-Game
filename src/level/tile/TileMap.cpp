#include "TileMap.h"
#include "TileDatabase.h"
#include "../../resources/ResourceHolder.h"
#include "../../app/Application.h"

namespace Level 
{
	TileMap::TileMap(uint width, uint height) 
		: width(width)
		, height(height)
	{
		addLayer();
		generateVertexArray(0);
		m_atlas = &Application::instance->getResources().textures.get("/tiles/atlas");
	}
	
	void TileMap::addLayer() 
	{
		auto layer = std::make_unique<TileLayer>();
		layer.get()->tiles = std::vector<std::vector<TileNode>>(width, std::vector<TileNode>(height, TileNode{}));
		layer.get()->vertexArray.reserve(width * height * 4);
		m_layers.push_back(std::move(layer));
	}

	void TileMap::addTile(uint x, uint y, uint layer, byte id, byte metadata) 
	{
		addTiles(layer, { {x, y, id, metadata} });
		generateVertexArray(layer);
	}

	// If you want to change multiple tiles at once it's better to batch
	// them so you generate the vertexarray after all have been added.
	// Instead of using only addTile() and generating the VA for every tile.
	void TileMap::addTiles(uint layer, const AddList& tiles)
	{
		for (auto t : tiles)
		{
			uint x = std::get<0>(t), y = std::get<1>(t);
			byte id = std::get<2>(t), metadata = std::get<3>(t);
			qAddTile(layer, x, y, id, metadata);
		}
		generateVertexArray(layer);
	}

	void TileMap::qAddTile(uint layer, uint x, uint y, byte id, byte metadata)
	{
		if (m_layers.size() > layer)
			m_layers[layer]->tiles[x][y] = TileNode{ id, metadata };
	}

	TileData TileMap::getTileData(uint layer, uint x, uint y) 
	{
		if (x >= width || y >= height)
			return TileDatabase::get().getTileData((byte)TileID::Void);

		return TileDatabase::get().getTileData(std::get<TILE_ID>(m_layers[layer]->tiles[x][y]));
	}

	void TileMap::generateVertexArray(byte layer)
	{
		for (uint y = 0; y < height; y++)
			for (uint x = 0; x < width; x++)
				addTileVertices(layer, x * TILE_SIZE, y * TILE_SIZE, m_layers[layer]->tiles[x][y]);
	}

	void TileMap::addTileVertices(byte layer, uint x, uint y, TileNode tile)
	{
		if (std::get<TILE_ID>(tile) == (byte)TileID::Void)
			return;

		Quad quad;

		setQuadVertexCoords(quad, x, y, tile);
		setQuadTextureCoords(quad, tile);

		auto l = m_layers[layer].get();

		l->vertexArray.push_back(quad.topLeft);
		l->vertexArray.push_back(quad.topRight);
		l->vertexArray.push_back(quad.bottomRight);
		l->vertexArray.push_back(quad.bottomLeft);
	}

	void TileMap::setQuadTextureCoords(TileMap::Quad &quad, TileNode tile)
	{
		sf::IntRect texCoords = TileDatabase::get().getTileData(std::get<TILE_ID>(tile)).texture;

		float tx = texCoords.left * TILE_SIZE;
		float ty = texCoords.top * TILE_SIZE;

		quad.topLeft.texCoords = { tx, ty };
		quad.topRight.texCoords = { tx + TILE_SIZE, ty };
		quad.bottomLeft.texCoords = { tx, ty + TILE_SIZE };
		quad.bottomRight.texCoords = { tx + TILE_SIZE, ty + TILE_SIZE };
	}

	void TileMap::setQuadVertexCoords(TileMap::Quad &quad, float x, float y, TileNode tile)
	{
		quad.topLeft.position = {x, y};
		quad.topRight.position = {x + TILE_SIZE, y};
		quad.bottomLeft.position = {x, y + TILE_SIZE};
		quad.bottomRight.position = {x + TILE_SIZE, y + TILE_SIZE};
	}

	void TileMap::render(sf::RenderWindow& window) 
	{
		sf::RenderStates states;
		states.texture = m_atlas;

		for (auto& layer : m_layers)
			window.draw(layer->vertexArray.data(), layer->vertexArray.size(), sf::PrimitiveType::Quads, states);
	}
}


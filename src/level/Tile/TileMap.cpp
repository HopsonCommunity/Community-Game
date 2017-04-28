#include "TileMap.h"
#include "TileDatabase.h"
#include "../../resources/ResourceHolder.h"
#include "../../app/Application.h"

namespace Level 
{
	TileMap::TileMap() 
	{
	}
	
	TileMap::TileMap(uint width, uint height) 
		: width(width)
		, height(height)
	{
		addLayer();
		generateVertexArray(0);
		m_tileTexture = &Application::instance->getResources().textures.get("/tiles/atlas");
	}
	
	void TileMap::addLayer() 
	{
		TileLayer layer = {std::vector<std::vector<TileMapNode>>(width, std::vector<TileMapNode>(height, TileMapNode(0, 0)))};
		m_layers.push_back(layer);
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
			m_layers[layer].tiles[x][y] = TileMapNode(id, metadata);
	}

	TileData TileMap::getTileData(uint layer, uint x, uint y) 
	{
		return TileDatabase::get().getTileData(m_layers[layer].tiles[x][y].getID());
	}

	void TileMap::generateVertexArray(byte layer)
	{
		m_vertexArray.reserve(width * height * 4);
	
		for (uint y=0; y < height; y++)
			for (uint x=0; x < width; x++)
				addTileVertices(layer, x * TILE_SIZE, y * TILE_SIZE, m_layers[layer].tiles[x][y]);
	}

	void TileMap::addTileVertices(byte layer, uint x, uint y, TileMapNode tile) 
	{
		if (tile.getID() == (byte)TileID::Void) 
			return;

		sf::IntRect uvs = TileDatabase::get().getTileData(tile.getID()).texture;

		m_vertexArray.push_back({ { (float)x + TILE_SIZE, (float)y - TILE_SIZE }, { (float)uvs.left, (float)uvs.top } });
		m_vertexArray.push_back({ { (float)x, (float)y - TILE_SIZE },{ (float)uvs.left + (float)uvs.width, (float)uvs.top } });
		m_vertexArray.push_back({ { (float)x, (float)y},{ (float)uvs.left, (float)uvs.top + (float)uvs.height } });
		m_vertexArray.push_back({ { (float)x + TILE_SIZE, (float)y},{ (float)uvs.left + (float)uvs.width, (float)uvs.top + (float)uvs.height } });
	}

	void TileMap::draw(sf::RenderWindow& window) 
	{
		sf::RenderStates states;
		states.texture = m_tileTexture;

		window.draw(m_vertexArray.data(), m_vertexArray.size(), sf::PrimitiveType::Quads, states);
	}
}


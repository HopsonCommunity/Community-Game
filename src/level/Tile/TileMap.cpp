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
		TileLayer layer = {std::vector<std::vector<TileMapNode>>(width, std::vector<TileMapNode>(height, TileMapNode(1, 0)))};
		m_layers.push_back(layer);
	}

	void TileMap::addTile(uint x, uint y, uint layer, byte id, byte metadata) 
	{
		if (m_layers.size() > layer) 
		{
			m_layers[layer].tiles[x][y] = TileMapNode(id, metadata);
		}
	}

	 TileData TileMap::getTileData(uint layer, uint x, uint y) 
	 {
		return TileDatabase::get().getTileData(m_layers[layer].tiles[x][y].getID());
	 }

	void TileMap::generateVertexArray(byte layer) 
	{
		if (m_buffer)
			delete m_buffer;
		m_indexCount = 0;

		for (uint y=0; y < height; y++)
			for (uint x=0; x < width; x++)
				addTileVertices(layer, x * TILE_SIZE, y * TILE_SIZE, m_layers[layer].tiles[x][y]);
	}

	void TileMap::addTileVertices(byte layer, uint x, uint y, TileMapNode tile) 
	{
		if (tile.getID() == 0) 
			return;

		sf::IntRect uvs = TileDatabase::get().getTileData(tile.getID()).texture;

		m_buffer->position = { (float)x, (float)y };
		m_buffer->texCoords = { (float)uvs.left, (float)uvs.top };
		m_buffer++;

		m_buffer->position = { (float)x + TILE_SIZE, (float)y};
		m_buffer->texCoords = { (float)uvs.left + uvs.width, (float)uvs.top };
		m_buffer++;

		m_buffer->position = { (float)x, (float)y + TILE_SIZE};
		m_buffer->texCoords = { (float)uvs.left, (float)uvs.top + uvs.height };
		m_buffer++;

		m_buffer->position = { (float)x + TILE_SIZE, (float)y + TILE_SIZE};
		m_buffer->texCoords = { (float)uvs.left + uvs.width, (float)uvs.top + uvs.height };
		m_buffer++;

		m_indexCount += 6;
	}

	void TileMap::draw(sf::RenderWindow& window) 
	{
		sf::RenderStates states;
		states.texture = m_tileTexture;

		window.draw(m_buffer, m_indexCount, sf::PrimitiveType::Triangles, states);
	}
}


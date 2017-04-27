#include "TileMap.h"
#include "TileDatabase.h"
#include "../../resources/ResourceHolder.h"
#include "../../app/Application.h"

namespace Level {
	TileMap::TileMap() {

	}
	TileMap::TileMap(uint width, uint height) : width(width), height(height){
		addLayer();
		generateVertexArray(0);
		m_tileTexture = &Application::instance->getResources().textures.get("/tiles/atlas");
	}
	void TileMap::addLayer() {
		TileLayer layer = {std::vector<std::vector<TileMapNode> >(width, std::vector<TileMapNode>(height, TileMapNode(0, 0)))};
		m_layers.push_back(layer);
	}

	void TileMap::addTile(uint x, uint y, uint layer, byte id, byte metadata) {
		if (m_layers.size() > layer) {
			m_layers[layer].tiles[x][y] = TileMapNode(id, metadata);
		}
	}

	 TileData TileMap::getTileData(uint layer, uint x, uint y) 
	 {
		return TileDatabase::get().getTileData(m_layers[layer].tiles[x][y].getID());
	 }

	void TileMap::generateVertexArray(byte layer) {
		m_vertexArrays[layer].resize(width * height * 4);
		for (uint y=0; y < height; y++)
		{
			for (uint x=0; x < width; x++)
			{
				addTileVertices(layer, x * TILE_SIZE, y * TILE_SIZE, m_layers[layer].tiles[x][y]);
			}
		}
	}

	void TileMap::addTileVertices(byte layer, uint x, uint y, TileMapNode tile) {
		if (tile.getID() == 0) return;

		Quad quad;

		setQuadVertexCoords(quad, x, y, tile);
		setQuadTextureCoords(quad, tile);

		m_vertexArrays[layer].append(quad.topLeft);
		m_vertexArrays[layer].append(quad.topRight);
		m_vertexArrays[layer].append(quad.bottomRight);
		m_vertexArrays[layer].append(quad.bottomLeft);
	}

	void TileMap::setQuadTextureCoords(TileMap::Quad &quad, TileMapNode tile) {
		sf::IntRect texCoords = TileDatabase::get().getTileData(tile.getID()).texture;

		float tx = (float)(texCoords.left * TILE_SIZE);
		float ty = (float)(texCoords.top * TILE_SIZE);

		quad.topLeft.texCoords = {tx, ty};
		quad.topRight.texCoords = {tx + TILE_SIZE, ty};
		quad.bottomLeft.texCoords = {tx, ty + TILE_SIZE};
		quad.topLeft.texCoords = {tx + TILE_SIZE, ty + TILE_SIZE};
	}

	void TileMap::setQuadVertexCoords(TileMap::Quad &quad, int x, int y, TileMapNode tile) {
		quad.topLeft.position = {(float)x, (float)y};
		quad.topRight.position = { (float)x + TILE_SIZE, (float)y};
		quad.bottomLeft.position = { (float)x, (float)y + TILE_SIZE};
		quad.bottomRight.position = { (float)x + TILE_SIZE, (float)y + TILE_SIZE};
	}

	void TileMap::draw(sf::RenderWindow& window) {
		sf::RenderStates states;
		states.texture = m_tileTexture;

		window.draw(m_vertexArrays[0]);
	}
}


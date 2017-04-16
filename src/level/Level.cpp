#include "Level.h"

#include "LevelRenderer.h"

#include "../states/StatePlaying.h"
#include "../entity/Entity.h"
#include "../entity/component/Components.h"

#include <iostream>

namespace Level
{
	Level::Level(unsigned int width, unsigned int height)
		: m_width(width),
		m_height(height)
	{
		m_tiles.resize(width*height);

		m_renderSystem = std::make_unique<Entity::RenderSystem>();

		m_updateSystems.push_back(std::make_unique<Entity::MoveSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::StatsSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::AISystem>());
		m_updateSystems.push_back(std::make_unique<Entity::PlayerInputSystem>());
		m_updateSystems.push_back(std::make_unique<Entity::AnimatorSystem>());
	}

	void Level::addEntity(std::unique_ptr<Entity::Entity> entity)
	{
		m_entities.push_back(std::move(entity));
	}

	Entity::Entity* Level::getEntity(const uint64 & id)
	{
		for (auto& entity : m_entities)
		{
			if (entity->getID() == id)
				return entity.get();
		}
		return nullptr;
	}

	void Level::setTile(unsigned int x, unsigned int y, Tile::Tile& tile)
	{
		m_tiles[x + y * m_width] = &tile;
	}

    Tile::Tile* Level::getTile(unsigned int x, unsigned int y)
    {
        if (x < 0 || x >= m_width || y < 0 || y >= m_height)
            return nullptr;
        return
            m_tiles[x + y * m_width];
    }

	Entity::Entity* Level::getEntityOnTile(unsigned int x, unsigned int y)
	{
		for (const auto& entity : m_entities)
		{
			Entity::PositionComponent* c_pos = entity.get()->getComponent<Entity::PositionComponent>();
			if (c_pos)
				if (c_pos->position.x == x && c_pos->position.y == y)
					return entity.get();
		}
		return nullptr;
	}

	void Level::update(const Timestep& ts)
	{
		for (auto& entity : m_entities)
		{
			for (auto& system : m_updateSystems)
				system->update(ts, entity.get());
			entity.get()->update(ts);
		}

	}

	void Level::render(sf::RenderWindow& window)
	{
		sf::View view = State::SPlaying::instance->getCamera();
		float left = view.getCenter().x - view.getSize().x / 2;
		float right = view.getCenter().x + view.getSize().x / 2;
		float top = view.getCenter().y - view.getSize().y / 2;
		float bottom = view.getCenter().y + view.getSize().y / 2;
		int x0 = (int)(left / TILE_SIZE);
		int y0 = (int)(top / TILE_SIZE);
		int x1 = (int)(right / TILE_SIZE) + 1;
		int y1 = (int)(bottom / TILE_SIZE) + 2;

		for (int x = x0; x < x1; x++)
			for (int y = y0; y < y1; y++)
			{
				if (x < 0 || static_cast<uint>(x) >= m_width || y < 0 || static_cast<uint>(y) >= m_height)
					continue;

				if (m_tiles[x + y * m_width] != nullptr)
					m_tiles[x + y * m_width]->render(x, y, *this, window);
			}
		
		for (auto& entity : m_entities)
			m_renderSystem->update(Timestep(0) /*Render doesn't need delta time*/, entity.get());

		LevelRenderer::drawAll();
	}
}

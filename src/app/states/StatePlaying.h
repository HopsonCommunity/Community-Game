#pragma once

#include "../../level/tile/TileMap.h"
#include "StateBase.h"

namespace State
{
	class Playing : public Base
	{
	public:
		Playing(Application* app, sf::RenderWindow* window);

		void event(sf::Event& event) override;
		void input() override;
		void update(const Timestep& ts) override;
		void render(sf::RenderWindow& window) override;
		void tick() override;

	private:
		// Level::TileMap m_level;

		void singleplayerCallback() {}
		void multiplayerCallback() {}
		void creditsCallback() {}
	};
}
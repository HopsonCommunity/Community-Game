#include "StatePlaying.h"

#include "../Application.h"

#include "../../Common.h"
#include "../../maths/Random.h"

namespace State
{
	Playing::Playing(Application* app, sf::RenderWindow* window)
		: Base(app)
		// , m_level(Level::TileMap(20, 20))
	{
	}

	void Playing::event(sf::Event & event)
	{
	}

	void Playing::input()
	{
	}

	void Playing::update(const Timestep& ts)
	{
	}

	void Playing::render(sf::RenderWindow& window)
	{
	}

	void Playing::tick()
	{
	}
}
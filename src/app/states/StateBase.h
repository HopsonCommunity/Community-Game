#pragma once

class Application;

#include "../../util/Timestep.h"

#include "../../events/Events.h"

namespace sf
{
	class RenderWindow;
	class Event;
}

namespace State
{
	class Base
	{
	public:
		Base(Application* app)
			: m_pApplication(app)
		{ }

		virtual ~Base() = default;

		Base(Base& other) = delete;
		Base& operator= (Base& other) = delete;

		virtual void onEvent(Events::Event& event) = 0;
		virtual void update(const Timestep& ts) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
		virtual void tick() = 0;

	protected:
		Application* m_pApplication;
	};
}

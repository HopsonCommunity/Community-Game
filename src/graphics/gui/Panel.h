#pragma once

#include "../../Common.h"

#include "../../events/Events.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace GUI
{
	class Widget;

	class Panel : public Events::IEventListener
	{
	public:
		Panel();
		~Panel();

		Widget* add(Widget* widget);
		void remove(Widget* widget);
		void clear();

		void onEvent(Events::Event& event) override;
		bool mousePressed(Events::MousePressedEvent& e);
		bool mouseReleased(Events::MouseReleasedEvent& e);
		bool mouseMoved(Events::MouseMovedEvent& e);

		void update();
		void render(sf::RenderWindow& window);

		const std::vector<Widget*>& getWidgets() const { return m_widgets; }

	private:
		std::vector<Widget*> m_widgets;
	};
}
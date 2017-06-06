#pragma once

#include "Panel.h"

#include "../../events/Events.h"
#include "../../maths/Maths.h"

namespace GUI
{
	class Widget
	{
	protected:
		bool m_active;
		bool m_focused;

		Panel* m_panel;
		maths::Rectangle m_bounds;

	private:
		Widget() {}
	
	protected:
		Widget(const maths::Rectangle& bounds);
	
	public:
		virtual bool mousePressed(Events::MousePressedEvent& e);
		virtual bool mouseReleased(Events::MouseReleasedEvent& e);
		virtual bool mouseMoved(Events::MouseMovedEvent& e);

		virtual void update();
		virtual void render(sf::RenderWindow& renderer);

		const maths::Rectangle& getBounds() const { return m_bounds; }
		maths::Rectangle& getBounds() { return m_bounds; }
		void setBounds(const maths::Rectangle& bounds) { m_bounds = bounds; }

		bool isActive() const { return m_active; }
		void setActive(bool active) { m_active = active; }
	};
}
#pragma once

#include "Panel.h"

#include "../../events/Events.h"
#include "../../maths/maths.h"

namespace GUI
{
	class Widget
	{
	protected:
		bool m_active;
		bool m_focused;

		Panel* m_panel;
		FloatRectangle m_bounds;

	private:
		Widget() {}
	
	protected:
		Widget(const FloatRectangle& bounds);
	
	public:
		virtual bool mousePressed(Events::MousePressedEvent& e);
		virtual bool mouseReleased(Events::MouseReleasedEvent& e);
		virtual bool mouseMoved(Events::MouseMovedEvent& e);

		virtual void update();
		virtual void render(sf::RenderWindow& renderer);

		const FloatRectangle& getBounds() const { return m_bounds; }
		FloatRectangle& getBounds() { return m_bounds; }
		void setBounds(const FloatRectangle& bounds) { m_bounds = bounds; }

		bool isActive() const { return m_active; }
		void setActive(bool active) { m_active = active; }
	};
}
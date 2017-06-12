#include "Widget.h"

#include "../../app/Application.h"

namespace GUI
{
	Widget::Widget(const FloatRectangle& bounds)
		: m_bounds(bounds)
		, m_active(true)
		, m_focused(false)
	{
	}

	bool Widget::mousePressed(Events::MousePressedEvent& e)
	{
		return false;
	}

	bool Widget::mouseReleased(Events::MouseReleasedEvent& e)
	{
		return false;
	}

	bool Widget::mouseMoved(Events::MouseMovedEvent& e)
	{
		return false;
	}

	void Widget::update()
	{
	}

	void Widget::render(sf::RenderWindow & renderer)
	{
	}
}
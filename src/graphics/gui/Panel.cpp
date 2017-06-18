#include "Panel.h"

#include "Widget.h"

#include "../../app/Application.h"

namespace GUI
{
	using namespace Events;

	Panel::Panel()
	{
		Application::get().pushPanel(this);
	}

	Panel::~Panel()
	{
		clear();

		Application::get().popPanel(this);
	}

	Widget* Panel::add(Widget* widget)
	{
		m_widgets.push_back(widget);
		return widget;
	}

	void Panel::remove(Widget* widget)
	{
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			if (m_widgets[i] == widget)
			{
				m_widgets.erase(m_widgets.begin() + i);
				delete m_widgets[i];
				break;
			}
		}
	}

	void Panel::clear()
	{
		for (uint i = 0; i < m_widgets.size(); i++)
			delete m_widgets[i];

		m_widgets.clear();
	}

	void Panel::onEvent(Events::Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseReleasedEvent>(_METHOD(&Panel::mouseReleased));
		dispatcher.dispatch<MousePressedEvent>(_METHOD(&Panel::mousePressed));
		dispatcher.dispatch<MouseMovedEvent>(_METHOD(&Panel::mouseMoved));
	}

	bool Panel::mousePressed(Events::MousePressedEvent& e)
	{
		Vec2 mouse = Application::get().uiMousePos();
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			Widget* widget = m_widgets[i];
			if (widget->getBounds().contains(mouse))
			{
				if (widget->isActive())
					if (widget->mousePressed(e))
						return true;
			}
		}
		return false;
	}

	bool Panel::mouseReleased(Events::MouseReleasedEvent& e)
	{
		Vec2 mouse = Application::get().uiMousePos();
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			Widget* widget = m_widgets[i];
			if (widget->getBounds().contains(mouse))
			{
				if (widget->isActive())
					if (widget->mouseReleased(e))
						return true;
			}
		}
		return false;
	}

	bool Panel::mouseMoved(Events::MouseMovedEvent& e)
	{
		for (uint i = 0; i < m_widgets.size(); i++)
		{
			Widget* widget = m_widgets[i];
			if (widget->isActive())
				if (widget->mouseMoved(e))
					return true;
		}
		return false;
	}

	void Panel::update()
	{
		for (Widget* widget : m_widgets)
		{
			if (widget->isActive())
				widget->update();
		}
	}

	void Panel::render(sf::RenderWindow& window)
	{
		for (Widget* widget : m_widgets)
		{
			if (widget->isActive())
				widget->render(window);
		}
	}
}
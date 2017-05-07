#include "UI.h"

namespace UI
{
	UI::UI(sf::RenderWindow* owningWindow)
		: m_owningWindow(owningWindow)
		, m_uiView(Vec2(static_cast<float>(owningWindow->getSize().x / 2), static_cast<float>(owningWindow->getSize().y / 2)), Vec2(static_cast<float>(owningWindow->getSize().x), static_cast<float>(owningWindow->getSize().y)))
	{
	}

	UI::~UI()
	{
	}

	void UI::update(Input::Input& input)
	{
		for (UIComponent* comp : m_components)
		{
			auto transform = comp->getTransform();
			auto mousePos = input.mousePosition(*m_owningWindow);
			if (transform.contains(mousePos))
			{
				auto relativeMP = mousePos - sf::Vector2i(transform.left, transform.top);
				if (!m_mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					comp->click(relativeMP.x, relativeMP.y);
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					comp->clickAndHold(relativeMP.x, relativeMP.y);
				else
					comp->hover(relativeMP.x, relativeMP.y);
			}
			else
				comp->none();
		}

		m_mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}

	void UI::render()
	{
		sf::View oldView = m_owningWindow->getView();
		m_owningWindow->setView(m_uiView);
		for (UIComponent* comp : m_components)
			comp->render(*m_owningWindow);
		m_owningWindow->setView(oldView);
	}

	void UI::addComponent(UIComponent& component)
	{
		m_components.push_back(&component);
	}
}
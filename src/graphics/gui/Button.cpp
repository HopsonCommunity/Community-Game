#include "Button.h"

#include "../../app/Application.h"

namespace GUI
{
	Button::Button(Graphics::Label* label, const FloatRectangle& bounds, const ActionHandler& handler)
		: Widget(bounds)
		, m_label(label)
		, m_actionHandler(handler)
		, m_state(ButtonState::UNPRESSED)
		, m_atlas((sf::Texture*)&Application::get().getTexture("/gui/button"))
		, m_sprite(new sf::RectangleShape(m_bounds.size))
	{
		m_label->setAlignment(Graphics::Label::Alignment::CENTER);
		m_label->setPosition({ m_bounds.size.x * .5f, m_bounds.size.y * .25f});

		m_sprite->setTexture(m_atlas);
		updateTexture();
	}

	Button::~Button()
	{
		delete m_label;
		delete m_sprite;
	}
	
	void Button::updateTexture()
	{
		int32 yOffset = m_hovered ? 14 : 0;
		if (m_state == ButtonState::PRESSED)
			yOffset = 27;

		m_sprite->setTextureRect({ 0, yOffset, 56, 14 });
	}

	bool Button::mousePressed(Events::MousePressedEvent& e)
	{
		m_state = ButtonState::PRESSED;

		return true;
	}

	bool Button::mouseReleased(Events::MouseReleasedEvent& e)
	{
		if (m_state == ButtonState::PRESSED)
			m_actionHandler();

		m_state = ButtonState::UNPRESSED;

		return true;
	}

	bool Button::mouseMoved(Events::MouseMovedEvent& e)
	{
		const Vec2 mouse = Application::get().uiMousePos();
		if (!m_bounds.contains(mouse))
			m_state = ButtonState::UNPRESSED;

		return false;
	}

	void Button::update()
	{
		const Vec2 mouse = Application::get().uiMousePos();
		m_hovered = m_bounds.contains(mouse);
		updateTexture();
	}

	void Button::render(sf::RenderWindow& window)
	{
		m_states.transform = sf::Transform().translate(m_bounds.position);
		window.draw(*m_sprite, m_states);
		m_label->render(window, m_states);
	}
}

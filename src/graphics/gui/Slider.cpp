#include "Slider.h"

#include "../../app/Application.h"

namespace GUI
{
	Slider::Slider(const FloatRectangle& bounds, bool vertical)
		: Widget(bounds)
		, m_value(0.0f)
		, m_state(SliderState::UNPRESSED)
		, m_headOffset(0.0f)
		, m_callback(&Slider::NoCallback)
		, m_vertical(vertical)
		, m_atlas((sf::Texture*)&Application::get().getTexture("/gui/slider"))
		, m_bgSprite(new sf::RectangleShape(m_bounds.size))
	{
		float size = vertical ? bounds.width : bounds.height;
		m_headBounds = FloatRectangle(bounds.x, bounds.y, size, size);

		m_headSprite = new sf::RectangleShape(m_headBounds.size);
		m_headSprite->setTexture(m_atlas);
		m_bgSprite->setTexture(m_atlas);
		m_bgSprite->setTextureRect({ 0, 0, 56, 14 });
	}

	Slider::Slider(const FloatRectangle& bounds, float value, const ValueChangedCallback& callback, bool vertical)
		: Widget(bounds)
		, m_value(value)
		, m_state(SliderState::UNPRESSED)
		, m_headOffset(0.0f)
		, m_callback(callback)
		, m_vertical(vertical)
		, m_atlas((sf::Texture*)&Application::get().getTexture("/gui/slider"))
		, m_bgSprite(new sf::RectangleShape(m_bounds.size))
	{
		float size = vertical ? bounds.width : bounds.height;
		m_headBounds = FloatRectangle(bounds.x, bounds.y, size, size);

		m_headSprite = new sf::RectangleShape(m_headBounds.size);
		m_headSprite->setTexture(m_atlas);
		m_bgSprite->setTexture(m_atlas);
		m_bgSprite->setTextureRect({ 0, 0, 56, 14 });
	}
	
	bool Slider::mousePressed(Events::MousePressedEvent& e)
	{
		Vec2 mouse = Application::get().uiMousePos();
		if (m_hovered)
		{
			m_state = SliderState::PRESSEDHEAD;
			m_headOffset = m_vertical ? (mouse.y - m_headBounds.y - m_headBounds.height / 2) : (mouse.x - m_headBounds.x - m_headBounds.width / 2);
		}

		return true;
	}

	bool Slider::mouseReleased(Events::MouseReleasedEvent& e)
	{
		m_state = SliderState::UNPRESSED;
		return true;
	}

	bool Slider::mouseMoved(Events::MouseMovedEvent& e)
	{
		Vec2 mouse = Application::get().uiMousePos();
		if (m_state == SliderState::PRESSEDHEAD)
		{
			if (m_vertical)
				setValue((mouse.y - m_bounds.getMinimumBound().y - m_headOffset) / (m_bounds.height));
			else
				setValue((mouse.x - m_bounds.getMinimumBound().x - m_headOffset) / (m_bounds.width));
		}

		return false;
	}

	void Slider::update()
	{
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_state = SliderState::UNPRESSED;

		Vec2 mouse = Application::get().uiMousePos();
		m_hovered = m_headBounds.contains(mouse);
		updateTexture();

		if (m_vertical)
			m_headBounds.y = m_bounds.getMinimumBound().y + m_headBounds.height / 2 + m_value * (m_bounds.height - m_headBounds.height) - m_headBounds.height /2;
		else
			m_headBounds.x = m_bounds.getMinimumBound().x + m_headBounds.width / 2 + m_value * (m_bounds.width - m_headBounds.width) - m_headBounds.width / 2;
	}
	
	void Slider::render(sf::RenderWindow& window)
	{
		m_states.transform = sf::Transform().translate(m_bounds.position);
		window.draw(*m_bgSprite, m_states);
		m_states.transform = sf::Transform().translate(m_headBounds.position);
		window.draw(*m_headSprite, m_states);
	}

	void Slider::updateTexture()
	{
		int32 xOffset = m_hovered ? 12 : 0;
		if (m_state == SliderState::PRESSEDHEAD)
			xOffset = 24;
		
		m_headSprite->setTextureRect({ xOffset, 14, 12, 14 });
	}

	void Slider::setValue(float value)
	{
		value = clamp(value, 0.0f, 1.0f);
		m_value = value;
		m_callback(value);
	}
}

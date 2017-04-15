#include "UISlider.h"

namespace UI
{
	UISlider::UISlider(Label label, sf::Rect<int> rect, std::function<void(float)> callback)
		: UIComponent(rect)
		, m_callback(callback)
		, m_rect(rect)
		, m_label(label)
		, m_sliderState(0)
	{
		m_label.setAlignment(Label::Alignment::CENTER);

		textures.insert(std::pair<int, const sf::Texture>(0, Application::instance->getResources().textures.get("gui/slider/knob_idle")));
		textures.insert(std::pair<int, const sf::Texture>(1, Application::instance->getResources().textures.get("gui/slider/knob_hover")));
		textures.insert(std::pair<int, const sf::Texture>(2, Application::instance->getResources().textures.get("gui/slider/knob_pressed")));
		textures.insert(std::pair<int, const sf::Texture>(3, Application::instance->getResources().textures.get("gui/slider/background")));

		m_label.setPosition({ (float)rect.left + rect.width / 2, (float)rect.top + rect.height / 4 });

		m_bgSprite.setTexture(textures[3]);
		m_bgSprite.setPosition(static_cast<float>(m_rect.left), static_cast<float>(m_rect.top));
		m_bgSprite.setScale((float)m_rect.width / 56.0f, (float)m_rect.height / 14.0f);

		m_scaleX = (float)rect.width / 56.0f;

		determineSliderPosition();

		setTexture(0);
	}

	void UISlider::click(int x, int y)
	{
		determineSliderState(x);
		determineSliderPosition();

		if (m_currentMode != 2)
			setTexture(2);

		if (m_oldSliderState != m_sliderState)
			m_callback(m_sliderState);
	}

	void UISlider::clickAndHold(int x, int y)
	{
		determineSliderState(x);
		determineSliderPosition();

		if (m_oldSliderState != m_sliderState)
			m_callback(m_sliderState);
	}

	void UISlider::hover(int x, int y)
	{
		if (m_currentMode != 1)
			setTexture(1);
	}

	void UISlider::none()
	{
		if (m_currentMode != 0)
			setTexture(0);
	}

	void UISlider::render(sf::RenderWindow& window)
	{
		window.draw(m_bgSprite);
		window.draw(m_sliderSprite);
		m_label.render(window);
	}

	void UISlider::setTexture(int mode)
	{
		m_sliderSprite.setTexture(textures[mode]);

		m_sliderSprite.setScale((float)m_rect.width / 56.0f, (float)m_rect.height / 14.0f);
		m_currentMode = mode;
	}

	void UISlider::determineSliderState(int x)
	{
		m_oldSliderState = m_sliderState;

		if (x < 3 * m_scaleX)
			m_sliderState = 0;
		else if (x > 53 * m_scaleX)
			m_sliderState = 1;
		else
		{
			float xNorm = (float)x / m_scaleX;
			xNorm -= 3;
			m_sliderState = xNorm / 50.0f;
		}
	}

	void UISlider::determineSliderPosition()
	{
		m_sliderSprite.setPosition(static_cast<float>(m_rect.left + m_sliderState * 50.0f * m_scaleX), static_cast<float>(m_rect.top));
	}
}

#include "UIButton.h"

namespace UI
{
	UIButton::UIButton(Label label, sf::Rect<int> rect, std::function<void()> callback)
	: UIComponent(rect)
	, m_sprite()
	, m_callback(callback)
	, m_rectangle(rect)
	, m_label(label)
	{
		m_label.setAlignment(Label::Alignment::CENTER);

		textures.insert(std::pair<int, const sf::Texture>(0, Application::instance->getResources().textures.get("gui/button/idle")));
		textures.insert(std::pair<int, const sf::Texture>(1, Application::instance->getResources().textures.get("gui/button/hover")));
		textures.insert(std::pair<int, const sf::Texture>(2, Application::instance->getResources().textures.get("gui/button/pressed")));

		setTexture(0);
	}

	void UIButton::click(int x, int y)
	{
		if (m_currentMode != 2)
			setTexture(2);
		m_callback();
	}

	void UIButton::hover(int x, int y)
	{
		if (m_currentMode != 1)
			setTexture(1);
	}
	 
	void UIButton::none()
	{
		if (m_currentMode != 0)
			setTexture(0);
	}

	void UIButton::render(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
		m_label.setPosition({(float)m_rectangle.left + m_rectangle.width / 2, (float)m_rectangle.top + m_rectangle.height / 4});
		m_label.render(window);
	}

	void UIButton::setTexture(int mode)
	{
		m_sprite.setTexture(textures[mode]);
		m_sprite.setPosition(m_rectangle.left, m_rectangle.top);
		m_sprite.setScale((float)m_rectangle.width / 56.0f, (float)m_rectangle.height / 14.0f);
		m_currentMode = mode;
	}
}
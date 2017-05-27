#include "UIButton.h"

namespace UI
{
	UIButton::UIButton(Label label, sf::Rect<int> rect, std::function<void()> callback)
		: UIComponent(rect)
		, m_callback(callback)
		, m_sprite()
		, m_rectangle(rect)
		, m_label(label)
	{
		m_label.setAlignment(Label::Alignment::CENTER);

		textures.insert(std::make_pair(0, Application::instance->getResources().textures.get("gui/button/idle")));
		textures.insert(std::make_pair(1, Application::instance->getResources().textures.get("gui/button/hover")));
		textures.insert(std::make_pair(2, Application::instance->getResources().textures.get("gui/button/pressed")));

		setTexture(0);
	}

	void UIButton::click(int x, int y)
	{
		if (m_currentMode != 2)
			setTexture(2);
		m_callback();
	}

	void UIButton::clickAndHold(int x, int y)
	{
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
		m_label.setPosition({ static_cast<float>(m_rectangle.left) + m_rectangle.width / 2, static_cast<float>(m_rectangle.top) + m_rectangle.height / 4 });
		m_label.render(window);
	}

	void UIButton::setTexture(int mode)
	{
		m_sprite.setTexture(textures[mode]);
		m_sprite.setPosition(static_cast<float>(m_rectangle.left), static_cast<float>(m_rectangle.top));
		m_sprite.setScale(static_cast<float>(m_rectangle.width) / 56.0f, static_cast<float>(m_rectangle.height) / 14.0f);
		m_currentMode = mode;
	}
}
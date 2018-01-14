#include "Label.h"

namespace Graphics
{
	Label::Label(const std::string& text, const sf::Font& font, uint size, Alignment alignment)
		: m_text(sf::Text(text, font, size)), m_alignment(alignment)
	{
	}

	void Label::render(sf::RenderWindow& m_window, sf::RenderStates states)
	{
		m_window.draw(m_text, states);
	}

	void Label::setAlignment(const Alignment& alignment)
	{
		m_alignment = alignment;
		updateBounds();
	}

	void Label::setText(const std::string& text)
	{
		m_text.setString(text);
		updateBounds();
	}

	void Label::setPosition(Vec2 position)
	{
		m_position = position;
		updateBounds();
	}

	void Label::updateBounds()
	{
		const sf::FloatRect rect = m_text.getLocalBounds();
		const Vec2 size(rect.width, rect.height);
		switch (m_alignment)
		{
		case Alignment::LEFT:
			m_alignmentOffset.x = 0;
			break;
		case Alignment::CENTER:
			m_alignmentOffset.x = -size.x * 0.5f;
			break;
		case Alignment::RIGHT:
			m_alignmentOffset.x = -size.x;
			break;
		default:
			break;
		}
		m_text.setPosition(m_position + m_alignmentOffset);
	}
}

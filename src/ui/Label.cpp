#include "Label.h"

namespace UI
{
	Label::Label(sf::Text text, Alignment alignment)
	: m_text(text), m_alignment(alignment)
	{
	}

	void Label::render(sf::RenderWindow& m_window)
	{
		m_text.setPosition(m_position + m_alignmentOffset);
		m_window.draw(m_text);
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

	void Label::setPosition(vec2 position)
	{
		m_position = position;
	}

	void Label::updateBounds()
	{
		sf::FloatRect rect = m_text.getLocalBounds();
		vec2 size(rect.width, rect.height);
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
	}
}

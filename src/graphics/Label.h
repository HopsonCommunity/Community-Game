#pragma once

#include "../maths/Maths.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
	// Wrapper for sf::Text with alignments
	class Label
	{
	public:
		enum class Alignment
		{
			NONE = 0, LEFT, CENTER, RIGHT
		};

	public:
		explicit Label(const std::string& text, const sf::Font& font, uint size, Alignment alignment = Alignment::LEFT);

		void render(sf::RenderWindow& m_window, sf::RenderStates states = sf::RenderStates());

		void setAlignment(const Alignment& alignment);
		void setText(const std::string& text);

		void setPosition(Vec2 position);

		sf::Text& getText() { return m_text; }
		Alignment getAlignment() const { return m_alignment; }

	private:
		Vec2 m_position;

		sf::Text m_text;
		Alignment m_alignment;
		Vec2 m_alignmentOffset;

		void updateBounds();
	};
}
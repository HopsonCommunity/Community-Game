#pragma once

#include <SFML/Graphics.hpp>

namespace UI
{
	// Wrapper for sf::Text with alignments
	class Label
	{
	public:
		enum class Alignment
		{
			NONE = 0, LEFT, CENTER, RIGHT
		};
	private:
		sf::Vector2f m_position;

		sf::Text m_text;
		Alignment m_alignment;
		sf::Vector2f m_alignmentOffset;
	public:
		Label(sf::Text text);
	
		void render(sf::RenderWindow& m_window);

		void setAlignment(const Alignment& alignment);
		void setText(const std::string& text);

		void setPosition(sf::Vector2f position);

		inline sf::Text& getText() { return m_text; }
		inline Alignment getAlignment() const { return m_alignment; }
	private:
		void updateBounds();
	};
}
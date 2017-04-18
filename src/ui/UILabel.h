#pragma once

#include <SFML/Graphics.hpp>

#include "../maths/Maths.h"

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

	public:
		Label(sf::Text text, Alignment alignment = Alignment::LEFT);

		void render(sf::RenderWindow& m_window);

		void setAlignment(const Alignment& alignment);
		void setText(const std::string& text);

		void setPosition(Vec2 position);

		inline sf::Text& getText() { return m_text; }
		inline Alignment getAlignment() const { return m_alignment; }

	private:
		Vec2 m_position;

		sf::Text m_text;
		Alignment m_alignment;
		Vec2 m_alignmentOffset;

		void updateBounds();
	};
}
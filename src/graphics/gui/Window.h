#pragma once

#include "../../Common.h"

#include "Widget.h"

#include "../Label.h"
#include "../../maths/maths.h"

namespace GUI
{
	// Do not confuse with 'real' window.
	class Window : public Widget
	{
		struct Manifold
		{
			bool active;
			Vec2 offset;
		};
	public:
		Window(const std::string& title, const FloatRectangle& bounds, const Vec2& minSize = Vec2(65, 65));

		bool mousePressed(Events::MousePressedEvent& e) override;
		bool mouseReleased(Events::MouseReleasedEvent& e) override;
		bool mouseMoved(Events::MouseMovedEvent& e) override;

		void update() override;
		void render(sf::RenderWindow& window) override;

		void rebuildVertexArray();

		void validateSize();
		void validatePosition();

		void updateButtons();

	private:
		Graphics::Label m_title;
		Vec2 m_minSize;

		Manifold m_moving;
		Manifold m_resizing;

		sf::RenderStates m_states;
		std::vector<sf::Vertex> m_vao;

		FloatRectangle close_button;
		FloatRectangle resize_button;
		FloatRectangle move_section;
	};
}
#pragma once

#include "Widget.h"
#include "../Label.h"

namespace GUI
{
	class Button : public Widget
	{
	public:
		using ActionHandler = std::function<void()>;

	private:
		enum class ButtonState
		{
			UNPRESSED, PRESSED
		};

	protected:
		Graphics::Label* m_label;
		ButtonState m_state;
		ActionHandler m_actionHandler;

		sf::Texture* m_atlas;
		sf::RenderStates m_states;
		sf::RectangleShape* m_sprite;

		bool m_hovered;

	public:
		Button(Graphics::Label* label, const FloatRectangle& bounds, const ActionHandler& handler = &Button::NoAction);
		~Button();
		
		bool mousePressed(Events::MousePressedEvent& e) override;
		bool mouseReleased(Events::MouseReleasedEvent& e) override;
		bool mouseMoved(Events::MouseMovedEvent& e) override;

		virtual void update() override;
		virtual void render(sf::RenderWindow& window) override;
		
		void updateTexture();

		void setAction(const ActionHandler& action) { m_actionHandler = action; }

	private:
		static void NoAction() {}
	};
}
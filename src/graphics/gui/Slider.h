#pragma once

#include "Widget.h"
#include "../Label.h"

#include "../../maths/Rectangle.h"

namespace GUI
{
	class Slider : public Widget
	{
	public:
		using ValueChangedCallback = std::function<void(float)>;
	
	private:
		enum class SliderState
		{
			UNPRESSED, PRESSEDHEAD
		};

	private:
		FloatRectangle m_headBounds;
		float m_value;
		float m_headOffset;
		SliderState m_state;
		ValueChangedCallback m_callback;
		bool m_vertical;

		bool m_hovered;

		sf::Texture* m_atlas;
		sf::RenderStates m_states;
		sf::RectangleShape* m_bgSprite;
		sf::RectangleShape* m_headSprite;

	public:
		Slider(const FloatRectangle& bounds, bool vertical = false);
		Slider(const FloatRectangle& bounds, float value = 0.0f, const ValueChangedCallback& callback = &Slider::NoCallback, bool vertical = false);

		bool mousePressed(Events::MousePressedEvent& e) override;
		bool mouseReleased(Events::MouseReleasedEvent& e) override;
		bool mouseMoved(Events::MouseMovedEvent& e) override;

		virtual void update() override;
		virtual void render(sf::RenderWindow& window) override;

		void updateTexture();

		void setCallback(const ValueChangedCallback& callback) { m_callback = callback; }
		inline const ValueChangedCallback& getCallback() const { return m_callback; }

		inline float getValue() const { return m_value; }
		void setValue(float value);

	private:
		static void NoCallback(float) {}
	};
}
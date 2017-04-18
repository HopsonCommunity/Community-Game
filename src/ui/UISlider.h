#pragma once

#include "UIComponentBase.h"
#include "UILabel.h"

#include "../app/Application.h"

#include <unordered_map>
#include <functional>

namespace UI
{
	class UISlider : public UIComponent
	{
	public:
		UISlider(Label label, sf::Rect<int> rect, std::function<void(float)> callback);

		void click(int x, int y);
		void hover(int x, int y);
		void clickAndHold(int x, int y);
		void none();
		void render(sf::RenderWindow& window);

	private:
		std::function<void(float)> m_callback;
		sf::Sprite m_bgSprite;
		sf::Sprite m_sliderSprite;
		sf::Rect<int> m_rect;
		Label m_label;

		std::unordered_map<int, const sf::Texture> textures;

		void setTexture(int mode);
		inline void determineSliderState(int x);
		inline void determineSliderPosition();

		int m_currentMode;

		float m_sliderState;
		float m_oldSliderState;

		float m_scaleX;
	};
}
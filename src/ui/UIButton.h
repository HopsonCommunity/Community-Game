#pragma once

#include "UIComponentBase.h"
#include "UILabel.h"

#include "../app/Application.h"

#include <functional>
#include <unordered_map>

namespace UI
{
	class UIButton : public UIComponent
	{
	public:
		UIButton(Label label, sf::Rect<int> rect, std::function<void()> callback);

		void click(int x, int y) override;
		void clickAndHold(int x, int y) override;
		void hover(int x, int y) override;
		void none() override;
		void render(sf::RenderWindow& window) override;

	private:
		std::function<void()> m_callback;
		sf::Sprite m_sprite;
		sf::Rect<int> m_rectangle;
		Label m_label;

		std::unordered_map<int, const sf::Texture> textures;

		void setTexture(int mode);

		int m_currentMode;
	};
}

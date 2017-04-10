#pragma once

#include "UIComponentBase.h"

#include "../Application.h"
#include "Label.h"

#include <functional>

namespace UI
{
    class UIButton : public UIComponent
    {
    public:
        UIButton(Label label, sf::Rect<int> rect, std::function<void()> callback);

        void click(int x, int y);
        void clickAndHold(int x, int y);
        void hover(int x, int y);
        void none();
        void render(sf::RenderWindow& window);
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


#pragma once

#include <vector>
#include <memory>

#include "../input/Input.h"
#include "UIComponentBase.h"

namespace UI
{
    class UI
    {
    public:
        UI(sf::RenderWindow* owningWindow);
        ~UI();

        void addComponent(UIComponent& component);

        void update(Input::Input& input);
        void render();
    private:
        std::vector<UIComponent*> m_components;
        sf::RenderWindow* m_owningWindow;
        sf::View m_uiView;

        bool m_mousePressed;
    };
}

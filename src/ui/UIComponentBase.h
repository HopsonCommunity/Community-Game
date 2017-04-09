#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../input/Input.h"

namespace UI
{
    class UIComponent
    {
    public:
        UIComponent(sf::Rect<int> transform) : m_transform(transform) { }

        virtual void hover(int x, int y) = 0;
        virtual void click(int x, int y) = 0;
        virtual void none() = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        const sf::Rect<int>& getTransform() { return m_transform; }
    protected:
        sf::Rect<int> m_transform;
    };

}

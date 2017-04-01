#include "StatePlaying.h"

namespace State
{
    SPlaying::SPlaying(Application* app)
    :   SBase           (app)
    ,   m_testSprite    ({100, 100})    //Set the size of the sprite
    ,   m_tileMap       ({}, 5, 5)
    {
        m_testSprite.setFillColor(sf::Color::Red);
    }

    void SPlaying::event(sf::Event& event)
    {

    }

    void SPlaying::input()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_testVelocity.x += 0.1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_testVelocity.x -= 0.1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_testVelocity.y -= 0.1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_testVelocity.y += 0.1;
        }
    }

    void SPlaying::update(float dt)
    {
        m_testSprite.move(m_testVelocity);

        ///@TODO Make velocity dampening scale with FPS/ dt
        m_testVelocity *= 0.98f;
    }

    void SPlaying::render(sf::RenderWindow& window)
    {
        window.draw(m_testSprite);
        m_tileMap.draw(window);
    }
}

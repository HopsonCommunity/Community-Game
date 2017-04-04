#include "DebugMenu.h"

#include <vector>
#include <iostream>
#include <SFML/Window.hpp>

namespace Debug
{
    DebugMenu::DebugMenu(const sf::Font& font)
        : m_active(false)
    {
        menu[0].setFont         (font);
        menu[0].setOutlineColor (sf::Color::Black);
        menu[0].setFillColor    (sf::Color::White);
        menu[0].setPosition     ({ 0, 0 });

        menu[1].setFont         (font);
        menu[1].setOutlineColor (sf::Color::Black);
        menu[1].setFillColor    (sf::Color::White);
        menu[1].setPosition({ GUI_WIDTH / 3, 0 });

        menu[2].setFont         (font);
        menu[2].setOutlineColor (sf::Color::Black);
        menu[2].setFillColor    (sf::Color::White);
        menu[2].setPosition({ GUI_WIDTH / 3 * 2 , 0 });
    }

    void DebugMenu::addEntry(const std::string& name, bool* value)
    {
        if (m_boolMap.find(name) != m_boolMap.end() || m_intMap.find(name) != m_intMap.end() || m_floatMap.find(name) != m_floatMap.end())
            return;

        DebugMenuBoolEntry entry = { name, value };

        m_boolMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd)
    {
        if (m_boolMap.find(name) != m_boolMap.end() || m_intMap.find(name) != m_intMap.end() || m_floatMap.find(name) != m_floatMap.end())
            return;

        DebugMenuIntEntry entry = { name, value, rangeBeg, rangeEnd };

        m_intMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd)
    {
        if (m_boolMap.find(name) != m_boolMap.end() || m_intMap.find(name) != m_intMap.end() || m_floatMap.find(name) != m_floatMap.end())
            return;

        DebugMenuFloatEntry entry = { name, value, rangeBeg, rangeEnd };

        m_floatMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::removeEntry(const std::string& name)
    {
        if (m_boolMap.find(name) != m_boolMap.end())
            m_boolMap.erase(name);

        if (m_floatMap.find(name) != m_floatMap.end())
            m_floatMap.erase(name);

        if (m_intMap.find(name) != m_intMap.end())
            m_intMap.erase(name);
    }

    void DebugMenu::input()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && !m_active)
        {
            m_active = true;
            m_window.create(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "Debug Menu");
        }

        if (m_active)
        {
            sf::Event ev;
            while (m_window.pollEvent(ev))
                if (ev.type == sf::Event::Closed)
                {
                    m_window.close();
                    m_active = false;
                }
        }
    }

    void DebugMenu::render()
    {
        if (!m_active)
            return;

        std::vector<DebugMenuBoolEntry> bools;
        std::vector<DebugMenuFloatEntry> floats;
        std::vector<DebugMenuIntEntry> ints;

        bools.reserve(m_boolMap.size());
        floats.reserve(m_floatMap.size());
        ints.reserve(m_intMap.size());

        for (auto kv : m_boolMap)
            bools.push_back(kv.second);

        for (auto kv : m_floatMap)
            floats.push_back(kv.second);

        for (auto kv : m_intMap)
            ints.push_back(kv.second);

        if (m_window.isOpen())
        {
            sf::Event e;

            while (m_window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                    m_window.close();

            }

            m_window.clear();

            for (auto& entry : bools)
            {
                menu[0].setString(createText(entry));
                m_window.draw(menu[0]);
            }

            for (auto& entry : floats)
            {
                menu[1].setString(createText(entry));
                m_window.draw(menu[1]);
            }

            for (auto& entry : ints)
            {
                menu[2].setString(createText(entry));
                m_window.draw(menu[2]);
            }

            m_window.display();
        }

        return;
    }

    std::string DebugMenu::createText(DebugMenuBoolEntry& entry)
    {
        std::string returnText = entry.name;

        returnText += " ";

        if (*(entry.value))
            returnText += "true";
        else
            returnText += "false";
        return returnText;
    }

    std::string DebugMenu::createText(DebugMenuIntEntry& entry)
    {
        std::string returnText = entry.name;
        returnText += " ";
        returnText += std::to_string(*(entry.value));
        return returnText;
    }

    std::string DebugMenu::createText(DebugMenuFloatEntry& entry)
    {
        std::string returnText = entry.name;
        returnText += " ";
        returnText += std::to_string(*(entry.value));
        return returnText;
    }

}

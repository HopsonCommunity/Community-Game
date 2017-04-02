#include "DebugMenu.h"

#include <vector>
#include <iostream>
#include <SFML/Window.hpp>

namespace Debug
{
    DebugMenu::DebugMenu()
    {
        // TODO (developer): Change this path for a relative
        if(!font.loadFromFile("/home/paul/CLionProjects/community-game/res/fonts/arial.ttf"))
        {
            std::cerr << "Cannot load font file" << std::endl;
            exit(0);
        }

        menu[0].setFont(font);
        menu[0].setColor(sf::Color::White);
        menu[0].setPosition({  GUI_WIDTH / 2, GUI_HEIGHT / (GUI_DISPLAY_VARS + 1) * 1  });

        menu[1].setFont(font);
        menu[1].setColor(sf::Color::White);
        menu[1].setPosition({  GUI_WIDTH / 2, GUI_HEIGHT / (GUI_DISPLAY_VARS + 1) * 2  });

        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setPosition({  GUI_WIDTH / 2, GUI_HEIGHT / (GUI_DISPLAY_VARS + 1) * 3  });
    }
	
    void DebugMenu::addEntry(const std::string& name, bool* value)
    {
        ///@ Fix is-existing check
        //if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
        //    return;
        
        DebugMenuBoolEntry entry = { name, value };

        m_boolMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd)
    {
        ///@ Fix is-existing check
        //if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
        //    return;

        DebugMenuIntEntry entry = { name, value, rangeBeg, rangeEnd };

        m_intMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd)
    {
        ///@ Fix is-existing check
        //if (m_boolMap.find(name) != m_boolMap.end() || m_intMap.find(name) != m_intMap.end() || m_floatMap.find(name) != m_floatMap.end())
        //    return;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
            if(!(m_active)) {
		m_active = true;
		window.create(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "Debug Menu");
	    }
	} else
            m_active = false;
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

        int currentText;

        ///@TODO: Use our sfml text abstraction

        if(window.isOpen())
        {
            sf::Event e;

            while(window.pollEvent(e))
            {
                if(e.type == sf::Event::Closed)
                    window.close();

            }

            window.clear();

            for (auto& entry : bools)
            {
                std::cout << createText(entry) << std::endl;
                menu[0].setString("Hello");
                window.draw(menu[0]);
                //drawText(0, currentText++ * 10, createText(entry));
            }

            for (auto& entry : floats)
            {
                std::cout << createText(entry) << std::endl;
                menu[1].setString(createText(entry));
                window.draw(menu[1]);
                //drawText(0, currentText++ * 10, createText(entry));
            }

            for (auto& entry : ints)
            {
                std::cout << createText(entry) << std::endl;
                menu[2].setString(":D");
                window.draw(menu[2]);
                //drawText(0, currentText++ * 10, createText(entry));
            }

            window.display();
        }

        return;
    }

    std::string DebugMenu::createText(DebugMenuBoolEntry& entry)
    {
        std::string returnText = entry.name;
        returnText += " ";
        returnText += std::to_string(*(entry.value));
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

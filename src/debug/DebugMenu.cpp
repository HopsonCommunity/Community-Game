#include "DebugMenu.h"

#include <vector>
#include <iostream>
#include <SFML\Window.hpp>

namespace Debug
{
    void DebugMenu::addEntry(const std::string& name, bool* value)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
            return;
        
        DebugMenuBoolEntry entry = { name, value };

        m_boolMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
            return;

        DebugMenuIntEntry entry = { name, value, rangeBeg, rangeEnd };

        m_intMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_active = true;
        else
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

        for (auto& entry : bools)
            std::cout << createText(entry) << std::endl;
            //drawText(0, currentText++ * 10, createText(entry));
        for (auto& entry : floats)
            std::cout << createText(entry) << std::endl;
            //drawText(0, currentText++ * 10, createText(entry));
        for (auto& entry : ints)
            std::cout << createText(entry) << std::endl;
            //drawText(0, currentText++ * 10, createText(entry));
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
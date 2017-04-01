#include "DebugMenu.h"

#include <SFML/>

namespace Debug
{
    void DebugMenu::addEntry(const std::string& name, bool* value)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
            return;

        m_boolMap.insert(std::make_pair(name, value));
    }

    void DebugMenu::addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
            return;

        DebugMenuIntEntry entry = { value, rangeBeg, rangeEnd };

        m_intMap.insert(std::make_pair(name, entry));
    }

    void DebugMenu::addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd)
    {
        if (m_boolMap.find(name) == m_boolMap.end() || m_intMap.find(name) == m_intMap.end() || m_floatMap.find(name) == m_floatMap.end())
            return;

        DebugMenuFloatEntry entry = { value, rangeBeg, rangeEnd };

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

    }

    void DebugMenu::update()
    {

    }

    void DebugMenu::render()
    {

    }
}
#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Application.h"

namespace Debug
{
    const int GUI_WIDTH = 1280;
    const int GUI_HEIGHT = 720;

    const int GUI_DISPLAY_VARS = 3;
    
    struct DebugMenuIntEntry
    {
        const std::string name;
        int* value;
        int rangeBeg;
        int rangeEnd;
    };

    struct DebugMenuFloatEntry
    {
        const std::string name;
        float* value;
        float rangeBeg;
        float rangeEnd;
    };

    struct DebugMenuBoolEntry
    {
        const std::string name;
        bool* value;
    };

    class DebugMenu
    {
    public:
        DebugMenu(const sf::Font& font);

        void addEntry(const std::string& name, bool* value);
        void addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd);
        void addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd);

        void removeEntry(const std::string& name);

        void input();
        void update();
        void render();
    private:
        std::unordered_map<std::string, DebugMenuBoolEntry> m_boolMap;
        std::unordered_map<std::string, DebugMenuIntEntry> m_intMap;
        std::unordered_map<std::string, DebugMenuFloatEntry> m_floatMap;

        bool m_active;
        int m_selectedEntry;
        int m_numEntries;

        std::string createText(DebugMenuBoolEntry& entry);
        std::string createText(DebugMenuIntEntry& entry);
        std::string createText(DebugMenuFloatEntry& entry);
        
        sf::RenderWindow m_window;

        int actualSelectedItem;
        sf::Text menu[3];
    };
}

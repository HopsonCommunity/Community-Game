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

    // Each struct is how data is saved internally to later draw in the GUI
    //rangeBeg and rangeEnd are for upcoming sliders
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
        // Constructs the instance and sets the font to be used, also needs a pointer to fps
        DebugMenu(const sf::Font& font);

        // Adds a bool to display onto the GUI
        void addEntry(const std::string& name, bool* value);

        // Adds an int to display onto the GUI, rangeBeg and rangeEnd are for the slider range
        void addEntry(const std::string& name, int* value, int rangeBeg, int rangeEnd);

        // Adds a float to display onto the GUI, rangeBeg and rangeEnd are for the slider range
        void addEntry(const std::string& name, float* value, float rangeBeg, float rangeEnd);

        //Removes an entry from the menu
        void removeEntry(const std::string& name);

        // Used internally for updating state of the debugging window
        void input();

        // Renders current values to the debugging window
        void render();
    private:
        // Maps to store
        std::unordered_map<std::string, DebugMenuBoolEntry> m_boolMap;
        std::unordered_map<std::string, DebugMenuIntEntry> m_intMap;
        std::unordered_map<std::string, DebugMenuFloatEntry> m_floatMap;

        bool m_active;
        sf::RenderWindow m_window;
        sf::Text m_menu[3];

        std::string createText(DebugMenuBoolEntry& entry);
        std::string createText(DebugMenuIntEntry& entry);
        std::string createText(DebugMenuFloatEntry& entry);
    };
}

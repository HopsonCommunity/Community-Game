#pragma once

#include <string>
#include <unordered_map>

namespace Debug
{
    struct DebugMenuIntEntry
    {
        const std::string& name;
        int* value;
        int rangeBeg;
        int rangeEnd;
    };

    struct DebugMenuFloatEntry
    {
        const std::string& name;
        float* value;
        float rangeBeg;
        float rangeEnd;
    };

    struct DebugMenuBoolEntry
    {
        const std::string& name;
        bool* value;
    };

    class DebugMenu
    {
    public:
        DebugMenu() { };

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
    };
}

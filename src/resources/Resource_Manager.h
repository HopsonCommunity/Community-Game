#pragma once

#include <unordered_map>

template <typename Res>
class Resource_Manager
{
    public:
        const Res& get(const std::string& name)
        {
            if (m_resourceMap.find())
            {
                ///@TODO Throw error on fail?
                add(name);
            }
            return qGet(name);
        }

        const Res& qGet(const std::string& name)
        {
            ///@TODO Maybe change to use operator []?
            return m_resourceMap.at(name);
        }

        void add(const std::string& name)
        {
            Res res;
            res.loadFromFile(name);
            m_resourceMap.insert(std::make_pair(name, res));
        }

    private:
        std::unordered_map<std::string, Res> m_resourceMap;
};

#pragma once
#include <vector>

/* Can be more efficient by reserving space based off of data size instead of
 * allowing std::vector to allocate its self */

class ZVector {
public:
    ZVector() {}
    ZVector(std::size_t dataSize) : m_dataSize(dataSize / sizeof(char)) {}

    unsigned int size() { return (unsigned int)(m_data.size() / m_dataSize); }

    char* data() {
        return m_data.data();
    }

    template<typename T>
    unsigned int add(T t) {
        char* dataPtr = (char*)&t;
        m_data.insert(m_data.end(), dataPtr, dataPtr + m_dataSize);
        return (unsigned int)(m_data.size() / m_dataSize) - 1;
    }

    unsigned int addPtr(void* data) {
        m_data.insert(m_data.end(), reinterpret_cast<char*>(data), reinterpret_cast<char*>(data) + m_dataSize);
        return (unsigned int)(m_data.size() / m_dataSize) - 1;
    }

    void clear() { m_data.clear(); }
    void reserve(unsigned int n) { m_data.reserve(n*m_dataSize); }
    void remove(unsigned int i) { m_data[i] = m_data.back(); m_data.pop_back(); }

    template<typename T>
    T* get(unsigned int i) {
        if((i*m_dataSize) > m_data.size()) {
            return nullptr;
        }
        return reinterpret_cast<T*>(&m_data[i*m_dataSize]);
    }
    void* operator[](unsigned int i) {
        if((i*m_dataSize) >= m_data.size()) {
            return nullptr;
        }
        return &m_data[i*m_dataSize];
    }

    /* Removes n elements from the end */
    ZVector& operator-=(unsigned int n) {
        if(m_data.size() < (n*m_dataSize)) {
            m_data.resize(0);
        } else {
            m_data.resize(m_data.size() - (n*m_dataSize));
        }
        return *this;
    }

    /* Adds an element to the end */
    template<typename T>
    ZVector& operator+=(T t) {
        char* dataPtr = (char*)&t;
        m_data.insert(m_data.end(), dataPtr, dataPtr + m_dataSize);
        return *this;
    }

private:
    std::size_t m_dataSize; /* Number of char NOT sizeof() result */
    std::vector<char> m_data;
};

class ZSparse {
public:
    ZSparse() {}
    ZSparse(std::size_t dataSize) : m_dataSize(dataSize / sizeof(char)) {}

    unsigned int size() { return m_numData; }
    void clear() {
        m_freeData.clear();
        m_freeData.resize(0);
        m_data.clear();
        m_data.resize(0);
        m_numData = 0;
    }

    char* data() {
        return m_data.data();
    }

    template<typename T>
    unsigned int add(T t) {
        unsigned int index;
        if(m_freeData.size() != 0) {
            index = m_freeData.back();
            *(reinterpret_cast<T*>(&m_data[index*m_dataSize])) = t;
            m_freeData.pop_back();
        } else {
            char* dataPtr = (char*)&t;
            m_data.insert(m_data.end(), dataPtr, dataPtr + m_dataSize);
            index = (unsigned int)(m_data.size() / m_dataSize) - 1;
        }
        ++m_numData;
        return index;
    }

    /* Unfriendly! Use templated add!*/
    unsigned int addPtr(void* data) {
        unsigned int index;
        if(m_freeData.size() != 0) {
            index = m_freeData.back();
            std::memcpy(&m_data[index*m_dataSize], data, sizeof(char)*m_dataSize);
            m_freeData.pop_back();
        } else {
            m_data.insert(m_data.end(), reinterpret_cast<char*>(data), reinterpret_cast<char*>(data) + m_dataSize);
            index = (unsigned int)(m_data.size() / m_dataSize) - 1;
        }
        ++m_numData;
        return index;
    }

    void remove(unsigned int i) {
        if(i > (m_data.size() / m_dataSize)) { return; }
        m_freeData.emplace_back(i);
        --m_numData;
    }

    template<typename T>
    T* get(unsigned int i) {
        if((i*m_dataSize) > m_data.size()) {
            return nullptr;
        }
        return reinterpret_cast<T*>(&m_data[i*m_dataSize]);
    }
    void* operator[](unsigned int i) {
        if((i*m_dataSize) >= m_data.size()) {
            return nullptr;
        }
        return &m_data[i*m_dataSize];
    }

    /* Removes n elements from the end */
    ZSparse& operator-=(unsigned int n) {
        for(unsigned int i = 0; i < (unsigned int)m_freeData.size(); ++i) {
            if(m_freeData[i] > ((m_data.size() - (n*m_dataSize)) / m_dataSize)) {
                if(i == ((unsigned int)m_freeData.size() - 1)) {
                    m_freeData.pop_back();
                } else {
                    m_freeData[i] = m_freeData.back();
                    m_freeData.pop_back();
                    --i;
                }
            }
        }
        if(m_data.size() < (n*m_dataSize)) {
            m_data.resize(0);
        } else {
            m_data.resize(m_data.size() - (n*m_dataSize));
        }
        m_numData -= n;
        return *this;
    }

    /* Adds an element to the sparse */
    template<typename T>
    unsigned int operator+=(T t) {
        unsigned int index;
        if(m_freeData.size() != 0) {
            index = m_freeData.back();
            *(reinterpret_cast<T*>(&m_data[index*m_dataSize])) = t;
            m_freeData.pop_back();
        } else {
            char* dataPtr = (char*)&t;
            m_data.insert(m_data.end(), dataPtr, dataPtr + m_dataSize);
            index = (unsigned int)(m_data.size() / m_dataSize) - 1;
        }
        ++m_numData;
        return index;
    }

private:
    std::size_t m_dataSize = 0; /* Number of char NOT sizeof() result */
    unsigned int m_numData = 0;
    std::vector<unsigned int> m_freeData;
    std::vector<char> m_data;
};
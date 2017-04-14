#pragma once

#include <random>
#include <ctime>

#include "Types.h"

namespace Random
{
    void init();
    int32     intInRange      (int32 lowBound, int32 highBound);
    uint64    uint64InRange   (uint64 lowBound, uint64 highBound);

    template<typename RandomEngine = std::minstd_rand>
    class Generator
    {
        public:
            Generator(uint64 seed = std::time(nullptr))
            {
                m_device.seed(static_cast<unsigned int>(seed));
            }

            void setSeed(uint64 seed)
            {
                m_device.seed(static_cast<unsigned int>(seed));
            }

            int32 intInRange (int32 lowBound, int32 highBound)
            {
                std::uniform_int_distribution<int32> dist(lowBound, highBound);
                return dist (m_device);
            }

            uint64 uint64InRange (uint64 lowBound, uint64 highBound)
            {
                std::uniform_int_distribution<uint64> dist(lowBound, highBound);
                return dist (m_device);
            }

        private:
            RandomEngine m_device;
    };
}

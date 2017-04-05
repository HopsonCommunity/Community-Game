#pragma once

#include "../../util/Types.h"
#include "../../util/Random.h"
#include "Leaf.h"

namespace WGenerator
{
    class WorldGenerator
    {
        public:
            WorldGenerator(uint t_width, uint t_height, uint t_seed);

            void generate();
            std::vector<std::vector<byte> > debug();

        private:
            uint m_minSize = 15;
            uint m_maxSize = 40;
            uint m_width;
            uint m_height;
            uint m_seed;
            Random::Generator<> m_generator;
            std::vector<std::shared_ptr<Leaf> > m_leafs;
    };
}
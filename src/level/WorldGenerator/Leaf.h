#pragma once

#include "Rectangle.h"

#include "../../util/Random.h"

#include <memory>

namespace WGenerator
{
    class Leaf
    {
        public:
            Leaf(Rectangle t_block, std::shared_ptr<Random::Generator<> > t_generator, uint t_minSize);

            bool split();
            void createRooms();

            std::shared_ptr<Rectangle> room;
            Rectangle block;

            std::vector<Rectangle> halls;

            std::shared_ptr<Leaf> leftChild;
            std::shared_ptr<Leaf> rightChild;

        private:
            void createHall(std::shared_ptr<Rectangle> left, std::shared_ptr<Rectangle> right);
            std::shared_ptr<Rectangle> getRoom();

            std::shared_ptr<Random::Generator<> > generator;
            uint m_minSize = 7;
    };
}

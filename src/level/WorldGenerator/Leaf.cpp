#include <iostream>
#include "Leaf.h"

namespace WGenerator
{
    Leaf::Leaf(Rectangle t_block, std::shared_ptr<Random::Generator<> > t_generator, uint t_minSize)
    :   block       (t_block)
    ,   generator   (t_generator)
    ,   m_minSize   (t_minSize)
    {
    }

    bool Leaf::split()
    {
        if (leftChild || rightChild) return false;

        bool splitOrientation = (bool)generator->uint64InRange(0, 1);

        if (block.width > block.height && block.width / block.height >= 1.25) splitOrientation = false;
        else if (block.height > block.width && block.height / block.width >= 1.25) splitOrientation = true;

        uint max = (splitOrientation ? block.height : block.width) - m_minSize;
        if (max <= m_minSize) return false;

        uint splitPosition = (uint)generator->uint64InRange(m_minSize, max);

        if (splitOrientation)
        {
            leftChild = std::make_shared<Leaf>(Rectangle(block.x, block.y, block.width, splitPosition), generator, m_minSize);
            rightChild = std::make_shared<Leaf>(Rectangle(block.x, block.y + splitPosition, block.width, block.height - splitPosition), generator, m_minSize);
        }
        else
        {
            leftChild = std::make_shared<Leaf>(Rectangle(block.x, block.y, splitPosition, block.height), generator, m_minSize);
            rightChild = std::make_shared<Leaf>(Rectangle(block.x + splitPosition, block.y, block.width - splitPosition, block.height), generator, m_minSize);
        }
        return true;
    }

    void Leaf::createRooms()
    {
        if(leftChild || rightChild)
        {
            if(leftChild)
            {
                leftChild->createRooms();
            }
            if(rightChild)
            {
                rightChild->createRooms();
            }
            if(leftChild && rightChild)
            {
                createHall(leftChild->getRoom(), rightChild->getRoom());
            }
        }
        else
        {
            Rectangle rect = Rectangle();
            rect.width = (uint) generator->uint64InRange(3, block.width - 2);
            rect.height = (uint) generator->uint64InRange(3, block.height - 2);
            rect.x = (uint) generator->uint64InRange(1, block.width - rect.width - 1) + block.x;
            rect.y = (uint) generator->uint64InRange(1, block.height - rect.height - 1) + block.y;
            room = std::make_shared<Rectangle>(rect);
        }
    }

    void Leaf::createHall(std::shared_ptr<Rectangle> left, std::shared_ptr<Rectangle> right)
    {
        std::pair<uint, uint> point1;
        std::pair<uint, uint> point2;


        point1 = std::make_pair((uint)(left->x + (left->width / 2)), (uint)(left->y + (left->height / 2)));
        point2 = std::make_pair((uint)(right->x + (right->width / 2)), (uint)(right->y + (right->height)/2));

        int w = point2.first - point1.first;
        int h = point2.second - point1.second;

        if (w < 0)
        {
            if (h < 0)
            {
                if (generator->uint64InRange(0, 100) < 50)
                {
                    halls.push_back(Rectangle(point2.first, point1.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point2.first, point2.second, 3, (uint)std::abs(h)));
                }
                else
                {
                    halls.push_back(Rectangle(point2.first, point2.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point1.first, point2.second, 3, (uint)std::abs(h)));
                }
            }
            else if (h > 0)
            {
                if (generator->uint64InRange(0, 100) < 50)
                {
                    halls.push_back(Rectangle(point2.first, point1.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point2.first, point1.second, 3, (uint)std::abs(h)));
                }
                else
                {
                    halls.push_back(Rectangle(point2.first, point2.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point1.first, point1.second, 3, (uint)std::abs(h)));
                }
            }
            else
            {
                halls.push_back(Rectangle(point2.first, point2.second, (uint)std::abs(w), 3));
            }
        }
        else if (w > 0)
        {
            if (h < 0)
            {
                if (generator->uint64InRange(0, 100) < 50)
                {
                    halls.push_back(Rectangle(point1.first, point2.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point1.first, point2.second, 3, (uint)std::abs(h)));
                }
                else
                {
                    halls.push_back(Rectangle(point1.first, point1.second, (uint)std::abs(w) + 3, 3));
                    halls.push_back(Rectangle(point2.first, point2.second, 3, (uint)std::abs(h)));
                }
            }
            else if (h > 0)
            {
                if (generator->uint64InRange(0, 100) < 50)
                {
                    halls.push_back(Rectangle(point1.first, point1.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point2.first, point1.second, 3, (uint)std::abs(h)));
                }
                else
                {
                    halls.push_back(Rectangle(point1.first, point2.second, (uint)std::abs(w), 3));
                    halls.push_back(Rectangle(point1.first, point1.second, 3, (uint)std::abs(h)));
                }
            }
            else
            {
                halls.push_back(Rectangle(point1.first, point1.second, (uint)std::abs(w), 3));
            }
        }
        else
        {
            if (h < 0)
            {
                halls.push_back(Rectangle(point2.first, point2.second, 3, (uint)std::abs(h)));
            }
            else if (h > 0)
            {
                halls.push_back(Rectangle(point1.first, point1.second, 3, (uint)std::abs(h)));
            }
        }

    }

    std::shared_ptr<Rectangle> Leaf::getRoom()
    {
        if (room) {
            return room;
        }
        else
        {
            std::shared_ptr<Rectangle> lRoom;
            std::shared_ptr<Rectangle> rRoom;

            if(leftChild)
            {
                lRoom = leftChild->getRoom();
            }
            if(rightChild)
            {
                rRoom = rightChild->getRoom();
            }
            if(!lRoom && !rRoom)
            {
                return nullptr;
            }
            else if (!rRoom) return std::shared_ptr<Rectangle>(lRoom);
            else if (!lRoom) return std::shared_ptr<Rectangle>(rRoom);
            else if (generator->uint64InRange(0, 100) > 50) return std::shared_ptr<Rectangle>(rRoom);
            else return std::shared_ptr<Rectangle>(lRoom);
        }
    }
}

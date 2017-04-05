#include <iostream>
#include "WorldGenerator.h"

namespace WGenerator
{
    WorldGenerator::WorldGenerator(uint t_width, uint t_height, uint t_seed) : m_width(t_width), m_height(t_height), m_seed(t_seed), m_generator()
    {
        m_generator.setSeed(m_seed);
    }

    void WorldGenerator::generate()
    {
        std::shared_ptr<Leaf> root = std::make_shared<Leaf>(Rectangle(0, 0, m_width, m_height), std::make_shared<Random::Generator<> >(m_generator),
                                                                  m_minSize);
        m_leafs.push_back(root);
        bool didSplit = true;
        while (didSplit)
        {
            didSplit = false;
            for (uint i = 0; i < m_leafs.size(); i++)
            {
                if (!(m_leafs[i]->leftChild) && !(m_leafs[i]->rightChild))
                {
                    if (m_leafs[i]->block.width > m_maxSize || m_leafs[i]->block.height > m_maxSize ||
                        m_generator.intInRange(0, 100) > 25)
                    {
                        if (m_leafs[i]->split())
                        {
                            m_leafs.push_back(m_leafs[i]->leftChild);
                            m_leafs.push_back(m_leafs[i]->rightChild);
                            didSplit = true;
                        }
                    }
                }
            }
        }
        root->createRooms();
    }

    std::vector<std::vector<byte> > WorldGenerator::debug()
    {
        std::vector<std::vector<byte> > map(m_width, std::vector<byte>(m_height, 1));

        std::vector<Rectangle> rects;

//Rooms

        for (int i=0; i < m_leafs.size(); i++){
            if (m_leafs[i]->room) {
                rects.push_back(*m_leafs[i]->room);
            }
        }


//Random blocks

        uint x = (uint)rects.size();
        for (int i=0; i < x; i++)
        {
            for (int j=0; j < 10; j++)
            {
                Rectangle rect = Rectangle();
                rect.width = (uint) m_generator.uint64InRange(2, 5);
                rect.height = (uint) m_generator.uint64InRange(2, 5);
                rect.x = (uint) m_generator.uint64InRange(rects[i].x,
                                                          rects[i].x + rects[i].width - (int) (rect.width / 2));
                rect.y = (uint) m_generator.uint64InRange(rects[i].y,
                                                          rects[i].y + rects[i].height - (int) (rect.height / 2));
                rects.push_back(rect);
            }
        }



//Halls
        std::vector<Rectangle> hal;

        for (int i=0; i < m_leafs.size(); i++){
            for (int j=0; j < m_leafs[i]->halls.size(); j++){
                hal.push_back(m_leafs[i]->halls[j]);
            }
        }


        for (int i=0; i<rects.size(); i++)
        {
            for (int j=0; j < rects[i].width; j++)
            {
                for (int k=0; k < rects[i].height; k++)
                {
                    if (map.size() > rects[i].x + j)
                    {
                        if (map[rects[i].x + j].size() > rects[i].y + k)
                        {
                            map[j + rects[i].x][k + rects[i].y] = 0;
                        }
                    }
                }
            }
        }
        for (int i=0; i<hal.size(); i++)
        {
            for (int j=0; j < hal[i].width; j++)
            {
                for (int k=0; k < hal[i].height; k++)
                {
                    if (map.size() > hal[i].x + j)
                    {
                        if (map[hal[i].x + j].size() > hal[i].y + k)
                        {
                            map[j + hal[i].x][k + hal[i].y] = 0;
                        }
                    }
                }
            }
        }

        for(int i=0; i<map.size(); i++){
            map[i].push_back(1);
        }
        map.push_back(std::vector<byte>(map[0].size(), 1));

        for (int i=0; i < map.size(); i++)
        {
            for (int j=0; j < map[i].size(); j++)
            {
                if(map[i][j] == 1) std::cout<<"XXX";
                else std::cout<<"   ";
            }
            std::cout<<std::endl;
        }
        return map;
    }
}
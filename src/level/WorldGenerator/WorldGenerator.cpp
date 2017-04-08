#include <iostream>
#include "WorldGenerator.h"

namespace WGenerator
{
    WorldGenerator::WorldGenerator(uint t_width, uint t_height, uint t_seed, uint t_minSize, uint t_maxSize)
		: m_width(t_width), m_height(t_height), m_seed(t_seed), m_generator(), m_minSize(t_minSize), m_maxSize(t_maxSize)
    {
        m_generator.setSeed(m_seed);
    }

    void WorldGenerator::generateMap()
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

	std::vector<std::shared_ptr<Rectangle> > WorldGenerator::getRooms()
	{
		std::vector<std::shared_ptr<Rectangle> > rectangles;
		for (int i=0; i < m_leafs.size(); i++)
		{
			if (m_leafs[i]->room)
			{
				rectangles.push_back(m_leafs[i]->room);
			}
		}
		return rectangles;
	}

	std::vector<std::shared_ptr<Rectangle> >  WorldGenerator::getRandomSquares()
	{
		std::vector<std::shared_ptr<Rectangle> > rooms;
		for (int i=0; i < m_leafs.size(); i++)
		{
			if (m_leafs[i]->room)
			{
				rooms.push_back(m_leafs[i]->room);
			}
		}
		std::vector<std::shared_ptr<Rectangle> > rectangles;
		for (int i=0; i < rooms.size(); i++)
		{
			for (int j=0; j < 10; j++)
			{
				std::shared_ptr<Rectangle>  rect = std::make_shared<Rectangle>(Rectangle());
				rect->width = (uint) m_generator.uint64InRange(2, 5);
				rect->height = (uint) m_generator.uint64InRange(2, 5);
				rect->x = (uint) m_generator.uint64InRange(rooms[i]->x,
														  rooms[i]->x + rooms[i]->width - (int) (rect->width / 2));
				rect->y = (uint) m_generator.uint64InRange(rooms[i]->y,
														  rooms[i]->y + rooms[i]->height - (int) (rect->height / 2));
				rectangles.push_back(rect);
			}
		}
		return rectangles;
	}

	std::vector<std::shared_ptr<Rectangle> > WorldGenerator::getHalls()
	{
		std::vector<std::shared_ptr<Rectangle> > rectangles;
		for (int i=0; i < m_leafs.size(); i++)
		{
			for (int j=0; j < m_leafs[i]->halls.size(); j++)
			{
				rectangles.push_back(std::make_shared<Rectangle>(m_leafs[i]->halls[j]));
			}
		}
		return rectangles;
	}

	std::vector<std::vector<byte > > WorldGenerator::render(std::vector<std::pair<std::vector<std::shared_ptr<Rectangle> >, byte > > data)
	{
		std::vector<std::vector<byte> > map(m_width, std::vector<byte>(m_height, 0));
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].first.size(); j++)
			{
				for (int k = 0; k < data[i].first[j]->width; k++)
				{
					for (int l = 0; l < data[i].first[j]->height; l++)
					{
						if (map.size() > data[i].first[j]->x + k)
						{
							if (map[data[i].first[j]->x + k].size() > data[i].first[j]->y + l)
							{
								map[k + data[i].first[j]->x][l + data[i].first[j]->y] = data[i].second;
							}
						}
					}
				}
			}
		}
		return map;
	}

	Map WorldGenerator::getMap(){
		Map map;
		std::vector<std::pair<std::vector<std::shared_ptr<Rectangle> >, byte > > data;
		data.push_back(std::make_pair<std::vector<std::shared_ptr<Rectangle> >, byte >(getRooms(), 1));
		data.push_back(std::make_pair<std::vector<std::shared_ptr<Rectangle> >, byte >(getRandomSquares(), 1));
		data.push_back(std::make_pair<std::vector<std::shared_ptr<Rectangle> >, byte >(getHalls(), 1));
		map.tiles = render(data);
		return map;
	}
}

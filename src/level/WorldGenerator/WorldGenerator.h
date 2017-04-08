#pragma once

#include <SFML/Audio.hpp>
#include "../../util/Types.h"
#include "../../util/Random.h"
#include "Leaf.h"

namespace WGenerator
{
    struct Map {
        std::vector<std::vector<byte> > tiles;
        std::vector<std::pair<sf::Vector2f, byte> > entites;
        sf::Vector2f player;
    };

    class WorldGenerator
    {
        public:
            WorldGenerator(uint t_width, uint t_height, uint t_seed, uint t_minSize = 15, uint t_maxSize = 40);

            void generateMap();
            Map getMap();

        private:

            std::vector<std::shared_ptr<Rectangle> > getRooms();
            std::vector<std::shared_ptr<Rectangle> > getRandomSquares();
            std::vector<std::shared_ptr<Rectangle> > getHalls();
            sf::Vector2f placePlayer(uint roomId);
            std::vector<std::pair<sf::Vector2f, byte> > placeEntities(uint spawnRoomId, byte id);
            std::vector<std::vector<byte > > render(std::vector<std::pair<std::vector<std::shared_ptr<Rectangle> >, byte > > data);

            uint m_minSize;
            uint m_maxSize;
            uint m_width;
            uint m_height;
            uint m_seed;
            Random::Generator<> m_generator;
            std::vector<std::shared_ptr<Leaf> > m_leafs;
    };
}

#include "WorldGenerator.h"
#include "../../util/FileUtil.h"

namespace WGenerator
{
	WorldGenerator::WorldGenerator(std::string folderName)
	{
		mainJSON = nlohmann::json::parse(getFileContents("res/worlds/" + folderName + "/world.json").c_str());
		obligatoryJSON = nlohmann::json::parse(getFileContents("res/worlds/" + folderName + "/obligatory.json").c_str());
		randomJSON = nlohmann::json::parse(getFileContents("res/worlds/" + folderName + "/random.json").c_str());

		if (! (mainJSON["seed"] == "random")) m_generator.setSeed(mainJSON["seed"]);

		for (int i=0; i < mainJSON["width"]; i++) {
			for (int j=0; j<mainJSON["height"]; j++) {
				addList.push_back({i, j, mainJSON["defaultWall"], 0});
			}
		}
	}

	void WorldGenerator::generateMap()
	{
		std::shared_ptr<Leaf> root = std::make_shared<Leaf>(IntRectangle(0, 0, mainJSON["width"], mainJSON["height"]), std::make_shared<Random::Generator<>>(m_generator),
															mainJSON["minLeafSize"], mainJSON["minHallWidth"], mainJSON["maxHallWidth"]);
		m_leafs.push_back(root);
		bool didSplit = true;
		while (didSplit)
		{
			didSplit = false;
			for (uint i = 0; i < m_leafs.size(); i++)
			{
				if (!m_leafs[i]->leftChild && !m_leafs[i]->rightChild)
				{
					int randomizedValue = m_generator.intInRange(0, 100);
					if (m_leafs[i]->block.width > mainJSON["maxLeafSize"] || m_leafs[i]->block.height > mainJSON["maxLeafSize"] ||
						randomizedValue > 25)
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

	std::vector<std::shared_ptr<IntRectangle>> WorldGenerator::getRooms()
	{
		std::vector<std::shared_ptr<IntRectangle>> Rects;
		for (uint i = 0; i < m_leafs.size(); i++)
			if (m_leafs[i]->room)
				Rects.push_back(m_leafs[i]->room);
		return Rects;
	}

	std::vector<std::shared_ptr<IntRectangle>>  WorldGenerator::getRandomSquares()
	{
		std::vector<std::shared_ptr<IntRectangle> > rooms;
		for (uint i = 0; i < m_leafs.size(); i++)
			if (m_leafs[i]->room)
				rooms.push_back(m_leafs[i]->room);

		std::vector<std::shared_ptr<IntRectangle>> Rects;
		for (uint i = 0; i < rooms.size(); i++)
		{
			for (int j = 0; j < 10; j++)
			{
				std::shared_ptr<IntRectangle>  rect = std::make_shared<IntRectangle>(IntRectangle());
				rect->width = static_cast<int32>(m_generator.uint64InRange(2, 5));
				rect->height = static_cast<int32>(m_generator.uint64InRange(2, 5));
				rect->x = static_cast<int32>(m_generator.uint64InRange(rooms[i]->x,
																	   rooms[i]->x + rooms[i]->width - static_cast<int32>(rect->width / 2)));
				rect->y = static_cast<int32>(m_generator.uint64InRange(rooms[i]->y,
																	   rooms[i]->y + rooms[i]->height - static_cast<int32>(rect->height / 2)));
				Rects.push_back(rect);
			}
		}
		return Rects;
	}

	std::vector<std::shared_ptr<IntRectangle>> WorldGenerator::getHalls()
	{
		std::vector<std::shared_ptr<IntRectangle>> Rects;
		for (uint i = 0; i < m_leafs.size(); i++)
			for (uint j = 0; j < m_leafs[i]->halls.size(); j++)
				Rects.push_back(std::make_shared<IntRectangle>(m_leafs[i]->halls[j]));

		return Rects;
	}

	void WorldGenerator::render(std::vector<std::pair<std::vector<std::shared_ptr<IntRectangle>>, byte>> data)
	{
		std::vector<std::vector<byte>> map(mainJSON["width"], std::vector<byte>(mainJSON["height"], 0));
		for (uint i = 0; i < data.size(); i++)
			for (uint j = 0; j < data[i].first.size(); j++)
				for (int32 k = 0; k < data[i].first[j]->width; k++)
					for (int32 l = 0; l < data[i].first[j]->height; l++)
						if (map.size() > static_cast<uint>(data[i].first[j]->x + k))
							if (map[data[i].first[j]->x + k].size() > static_cast<uint>(data[i].first[j]->y + l))
								addList.push_back(std::make_tuple(k + data[i].first[j]->x, l + data[i].first[j]->y, data[i].second, 0));
	}

	Map WorldGenerator::getMap()
	{
		Map map;
		std::vector<std::pair<std::vector<std::shared_ptr<IntRectangle>>, byte>> data;
		//data.push_back(std::make_pair<std::vector<std::shared_ptr<IntRectangle>>, byte>(getRooms(), mainJSON["defaultFloor"]));
		//data.push_back(std::make_pair<std::vector<std::shared_ptr<IntRectangle>>, byte>(getRandomSquares(), mainJSON["defaultFloor"]));
		data.push_back(std::make_pair<std::vector<std::shared_ptr<IntRectangle>>, byte>(getHalls(), mainJSON["defaultFloor"]));
		renderRooms();
		render(data);
		uint numberOfRooms = getRooms().size();
		map.addList = addList;
		map.playerPosition = placePlayer(static_cast<uint>(m_generator.uint64InRange(0, numberOfRooms)));
		return map;
	}

	sf::Vector2<uint> WorldGenerator::placePlayer(uint roomId)
	{
		std::vector<std::shared_ptr<IntRectangle>> rooms = getRooms();
		return sf::Vector2<uint>((rooms[roomId]->x * 2 + rooms[roomId]->width) / 2, (rooms[roomId]->y * 2 + rooms[roomId]->height) / 2);
	}

	void WorldGenerator::renderRooms() {
		std::vector<std::shared_ptr<IntRectangle>>rooms = getRooms();
		uint roomIterator = 0;
		std::vector<nlohmann::json> obligatory = obligatoryJSON;
		std::cout<<obligatory.size();
		for(int i=0; i < obligatory.size(); i++) {
			uint j = (uint)m_generator.uint64InRange(obligatory.at(i)["min"], obligatory.at(i)["max"]);
			std::cout<<j;
			for (; j>0; j--) {
				if (roomIterator < rooms.size()){
					renderRoom(*rooms[roomIterator], obligatory[i]);
				}
				else break;
				roomIterator++;
			}
		}
		std::vector<nlohmann::json> random = randomJSON;
		for (; roomIterator < rooms.size(); roomIterator++){
			uint x = (uint)m_generator.uint64InRange(0, 100);
			uint i=0;
			while (true){
				if (i >= random.size()) break;
				if (random.at(i)["chance"] > x) {
					renderRoom(*rooms[roomIterator], random[i]);
					break;
				}
				i++;
			}
		}
	}

	void WorldGenerator::renderRoom(IntRectangle rect, nlohmann::json json) {
		for (int i=0; i < rect.width; i++){
			for (int j=0; j<rect.height; j++) {
				addList.push_back({i + rect.x, j + rect.y, json["wall"], 0});
			}
		}
		for (int i=1; i < rect.width - 1; i++){
			for (int j=1; j<rect.height - 1; j++) {
				addList.push_back({i + rect.x, j + rect.y, json["floor"], 0});
			}
		}
	}
}

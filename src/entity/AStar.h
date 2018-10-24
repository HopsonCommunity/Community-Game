#pragma once

#include "../Common.h"

#include "../maths/maths.h"
#include "../util/PriorityQueue.h"

#include <SFML/Graphics.hpp>

namespace AStar
{
	typedef std::tuple<int32, int32> Location;

	static std::array<Location, 8> directions
	{ 
		Location{ 1, 0 }, 
		Location{ 1, -1 },
		Location{ -1, 1 },
		Location{ 1, 1 },
		Location{ -1, -1 },
		Location{ 0, -1 },
		Location{ -1, 0 }, 
		Location{ 0, 1 } 
	};

	std::vector<Location> neighbors(Location id);

	inline double distance(Location a, Location b)
	{
		int x1, y1, x2, y2;
		std::tie(x1, y1) = a;
		std::tie(x2, y2) = b;
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
	
	// Manhattan distance
	// If you are wondering: In Manhattan you tell somebody where to go by
	// telling him how many blocks he has to go up/side (everything is square grid based
	// there). This is what the function is doing. A* doesnt need precise cost to the end  
	// just an estimate so it's good enough. Avoids using expensive sqrt(..)
	inline double heuristic(Location a, Location b)
	{
		int x1, y1, x2, y2;
		std::tie(x1, y1) = a;
		std::tie(x2, y2) = b;
		return abs(x1 - x2) + abs(y1 - y2);
	}

	void search(Location start, Location goal, std::unordered_map<Location, Location>& came_from,
		std::unordered_map<Location, double>& cost_so_far);

	std::vector<Location> constructPath(Location start, Location goal);
}

namespace std
{
	template<>
	struct hash<AStar::Location>
	{
		size_t operator() (const AStar::Location& pos) const
		{
			std::hash<int> hasher;
			auto h1 = hasher(std::get<0>(pos));
			auto h2 = hasher(std::get<1>(pos));

			return std::hash<int>{}((static_cast<int>(h1 ^ h2)) >> 2);
		}
	};
}

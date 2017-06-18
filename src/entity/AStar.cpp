#include "AStar.h"

#include "../app/states/StatePlaying.h"

namespace AStar
{
	std::vector<Location> neighbors(Location id)
	{
		int32 x, y, dx, dy;
		std::tie(x, y) = id;
		std::vector<Location> results;

		for (auto dir : directions)
		{
			std::tie(dx, dy) = dir;
			Location next(x + dx, y + dy);
			if (State::Playing::get().isTilePassable(0, x + dx, y + dy))
				results.push_back(next);
		}

		if ((x + y) % 2 == 0)
			std::reverse(results.begin(), results.end());

		return results;
	}

	void search(Location start, Location goal, std::unordered_map<Location, Location>& came_from, std::unordered_map<Location, double>& cost_so_far)
	{
		PriorityQueue<Location, double> frontier;
		frontier.put(start, 0);

		came_from[start] = start;
		cost_so_far[start] = 0;

		while (!frontier.empty())
		{
			auto current = frontier.get();

			if (current == goal)
				break;

			for (auto next : neighbors(current))
			{
				double new_cost = cost_so_far[current] + distance(current, next);
				if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
				{
					cost_so_far[next] = new_cost;
					double priority = new_cost + heuristic(next, goal);
					frontier.put(next, priority);
					came_from[next] = current;
				}
			}
		}
	}

	std::vector<Location> constructPath(Location start, Location goal)
	{
		std::unordered_map<Location, Location> came_from;
		std::unordered_map<Location, double> cost_so_far;
		search(start, goal, came_from, cost_so_far);

		std::vector<Location> path;
		Location current = goal;
		path.push_back(current);
		while (current != start)
		{
			current = came_from[current];
			path.push_back(current);
		}

		State::Playing::get().getLevel().m_visualPath.clear();
		for (uint i = 0; i < path.size(); i++)
		{
			Location& loc = path[i];
			State::Playing::get().getLevel().m_visualPath.push_back(Vec2i(std::get<0>(loc), std::get<1>(loc)));
		}

		return path;
	}
}
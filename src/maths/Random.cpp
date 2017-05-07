#include "Random.h"

namespace Random
{
	namespace
	{
		std::minstd_rand rd;
	}

	void init()
	{
		rd.seed(static_cast<uint>(std::time(nullptr)));
	}

	int32 intInRange(int32 lowBound, int32 highBound)
	{
		std::uniform_int_distribution<int32> dist(lowBound, highBound);
		return dist(rd);
	}

	uint64 uint64InRange(uint64 lowBound, uint64 highBound)
	{
		std::uniform_int_distribution<uint64> dist(lowBound, highBound);
		return dist(rd);
	}

	char getRandomChar()
	{
		return (char)('A' + intInRange(0, 23));
	}
}
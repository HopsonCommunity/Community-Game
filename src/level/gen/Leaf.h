#pragma once

#include "../../maths/Maths.h"

#include <memory>

namespace WGenerator
{
	class Leaf
	{
	public:
		Leaf(Rect t_block, std::shared_ptr<Random::Generator<> > t_generator, uint t_minSize);

		bool split();
		void createRooms();

		std::shared_ptr<Rect> room;
		Rect block;

		std::vector<Rect> halls;

		std::shared_ptr<Leaf> leftChild;
		std::shared_ptr<Leaf> rightChild;

	private:
		void createHall(std::shared_ptr<Rect> left, std::shared_ptr<Rect> right);
		std::shared_ptr<Rect> getRoom();

		std::shared_ptr<Random::Generator<> > generator;
		uint m_minSize = 7;
	};
}

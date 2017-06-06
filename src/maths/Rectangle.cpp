#include "Rectangle.h"

namespace maths
{
	Rectangle::Rectangle()
		: position(Vec2()), size(Vec2())
	{
	}

	Rectangle::Rectangle(const Vec2& position, const Vec2& size)
		: position(position), size(size)
	{
	}

	Rectangle::Rectangle(float x, float y, float width, float height)
		: position(Vec2(x, y)), size(Vec2(width, height))
	{
	}

	bool Rectangle::intersects(const Rectangle& other) const
	{
		return (size > other.position && position < other.size) || (position > other.size && size < other.position);
	}

	bool Rectangle::contains(const Vec2& point) const
	{
		return point.x > getMinimumBound().x && point.y > getMinimumBound().y && point.x < getMaximumBound().x && point.y < getMaximumBound().y;
	}


	IntRectangle::IntRectangle()
		: x(0)
		, y(0)
		, width(0)
		, height(0)
	{
	}

	IntRectangle::IntRectangle(int32 x, int32 y, int32 width, int32 height)
		: x(x)
		, y(y)
		, width(width)
		, height(height)
	{
	}

	IntRectangle::IntRectangle(Vec2i min, Vec2i max)
		: x(min.x)
		, y(min.y)
		, width(max.x)
		, height(max.y)
	{
	}

	bool IntRectangle::contains(Vec2i point)
	{
		if (point.x < x || point.x > x + width || point.y < y || point.y > y + height)
			return false;

		return true;
	}
}
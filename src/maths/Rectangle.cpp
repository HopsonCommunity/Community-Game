#include "Rectangle.h"

FloatRectangle::FloatRectangle()
	: position(Vec2()), size(Vec2())
{
}

FloatRectangle::FloatRectangle(const Vec2& position, const Vec2& size)
	: position(position), size(size)
{
}

FloatRectangle::FloatRectangle(float x, float y, float width, float height)
	: position(Vec2(x, y)), size(Vec2(width, height))
{
}

bool FloatRectangle::intersects(const FloatRectangle& other) const
{
	return (size > other.position && position < other.size) || (position > other.size && size < other.position);
}

bool FloatRectangle::contains(const Vec2& point) const
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

IntRectangle::IntRectangle(const Vec2i& min, const Vec2i& max)
	: x(min.x)
	, y(min.y)
	, width(max.x)
	, height(max.y)
{
}

bool IntRectangle::intersects(const IntRectangle & other) const
{
	return (size > other.position && position < other.size) || (position > other.size && size < other.position);
}

bool IntRectangle::contains(const Vec2i& point)
{
	return point.x > getMinimumBound().x && point.y > getMinimumBound().y && point.x < getMaximumBound().x && point.y < getMaximumBound().y;
}
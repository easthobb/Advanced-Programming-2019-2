#include "Point.h"

Point::Point(int x, int y): x(x), y(y)
{
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

std::ostream& operator << (std::ostream& os, const Point& point)
{
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

Point& Point::operator = (const Point &point)
{
	x = point.x;
	y = point.y;
	return *this;
}

bool Point::operator == (const Point &point) const
{
	return (x == point.x) && (y == point.y);
}

bool Point::operator != (const Point &point) const
{
	return !((x == point.x) && (y == point.y));
}
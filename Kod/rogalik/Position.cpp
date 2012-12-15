#include "Position.h"

Position::Position(int x, int y, int z)
	: x(x), y(y), z(z)
{
}

void Position::SetX(int x)
{
	this->x = x;
}

void Position::SetY(int y)
{
	this->y = y;
}

void Position::SetZ(int z)
{
	this->z = z;
}

int Position::GetX() const
{ 
	return x;
}

int Position::GetY() const
{ 
	return y;
}

int Position::GetZ() const
{ 
	return z;
}


Position Position::operator +(const Position& b) const
{
	return Position(x + b.x, y+b.y, z+b.z);
}


Position Position::operator -(const Position& b) const
{
	return Position(x - b.x, y-b.y, z-b.z);
}

float Position::distance(const Position& a, const Position& b)
{
	Position dp = a - b;
	return sqrt(static_cast<float>(dp.x*dp.x + dp.y*dp.y + dp.z*dp.z));
}


bool Position::operator ==(const Position& b) const
{
	return ( x == b.x && y == b.y && z == b.z );
}

bool Position::operator !=(const Position& b) const
{
	return ( x != b.x || y != b.y || z != b.z );
}
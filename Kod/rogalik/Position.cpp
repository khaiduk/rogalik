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
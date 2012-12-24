#pragma once
#include <cmath>

/**
 * Po�o�enie w �wiecie gry
 * Po�o�enie reprezentowane jest przez 3 wsp�rz�dne:
 * X i Y wyznaczaj� po�o�enie na danym poziomie,
 * za� Z wyznacza poziom
 */
class Position
{
public:
	Position(int x = 0, int y = 0, int z = 0);
	void SetX(int x);
	void SetY(int y);
	void SetZ(int z);
	int GetX() const;
	int GetY() const;
	int GetZ() const;
	Position operator +(const Position& b) const;
	Position operator -(const Position& b) const;
	bool operator ==(const Position& b) const;
	bool operator !=(const Position& b) const;

	/**
	 * Zwraca odleg�o�� mi�dzy po�o�eniami
	 */
	static float distance(const Position& a, const Position& b);
public:
	int x,y,z;
};


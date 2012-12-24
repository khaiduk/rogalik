#pragma once
#include <cmath>

/**
 * Po³o¿enie w œwiecie gry
 * Po³o¿enie reprezentowane jest przez 3 wspó³rzêdne:
 * X i Y wyznaczaj¹ po³o¿enie na danym poziomie,
 * zaœ Z wyznacza poziom
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
	 * Zwraca odleg³oœæ miêdzy po³o¿eniami
	 */
	static float distance(const Position& a, const Position& b);
public:
	int x,y,z;
};


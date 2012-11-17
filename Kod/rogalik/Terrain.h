#pragma once
#include <vector>
#include "Position.h"
#include "Tile.h"

/**
 * Teren (mapa) gry
 * Teren sk�ada si� z poziom�w (o� Z), sk�adaj�cych si� siatki kafelek (osie XY).
 * Poziomy mo�na traktowa� jako odr�bne podmapy po��czone warpami, ale te� jako
 * trzeci� wsp�rz�dn� mapy.
 */
class Terrain
{
public:
	/**
	 * Tworzy teren
	 */
	Terrain(void);
	~Terrain(void);
	/**
	 * Wy�wietla teren na ekranie z przesuni�ciem o pos kafelek
	 */
	void draw(sf::RenderWindow& rw, Position pos) const;
private:
	std::vector< std::vector< std::vector<Tile> > > map;
	std::vector< std::vector<Tile> > newLevel(int width, int height, int level);
};


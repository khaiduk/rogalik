#pragma once
#include <vector>
#include <iostream>
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
	void draw(sf::RenderWindow& rw, int level, const Position& shift) const;
	/**
	 * Oblicza docelowe przesuni�cie mapy.
	 * Na podstawie po�o�enia gracza oblicza o ile pikseli musi by� przesuni�ty ka�dy element �wiata gry.
	 */
	Position calculateShift(const Position& playerPos) const;
	/**
	 * Pobiera kafelek z danego po�o�enia
	 * Je�li taki kafelek nie istneje rzuca wyj�tek ..
	 */
	Tile getTile(const Position& pos) const;
private:
	std::vector< std::vector< std::vector<Tile> > > map;

	friend class GameBuilder;
};


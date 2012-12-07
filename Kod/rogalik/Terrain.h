#pragma once
#include <vector>
#include <iostream>
#include "Position.h"
#include "Tile.h"

/**
 * Teren (mapa) gry
 * Teren sk³ada siê z poziomów (oœ Z), sk³adaj¹cych siê siatki kafelek (osie XY).
 * Poziomy mo¿na traktowaæ jako odrêbne podmapy po³¹czone warpami, ale te¿ jako
 * trzeci¹ wspó³rzêdn¹ mapy.
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
	 * Wyœwietla teren na ekranie z przesuniêciem o pos kafelek
	 */
	void draw(sf::RenderWindow& rw, int level, const Position& shift) const;
	/**
	 * Oblicza docelowe przesuniêcie mapy.
	 * Na podstawie po³o¿enia gracza oblicza o ile pikseli musi byæ przesuniêty ka¿dy element œwiata gry.
	 */
	Position calculateShift(const Position& playerPos) const;
	/**
	 * Pobiera kafelek z danego po³o¿enia
	 * Jeœli taki kafelek nie istneje rzuca wyj¹tek ..
	 */
	Tile getTile(const Position& pos) const;
private:
	std::vector< std::vector< std::vector<Tile> > > map;

	friend class GameBuilder;
};


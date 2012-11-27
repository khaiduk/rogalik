#pragma once
#include <vector>
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
	void draw(sf::RenderWindow& rw, const Position& pos) const;
	/**
	 * Oblicza docelowe przesuniêcie mapy.
	 */
	Position calculateShift(const Position& p) const;
	/**
	 * Pobiera kafelek z danego po³o¿enia
	 * Jeœli taki kafelek nie istneje rzuca wyj¹tek ..
	 */
	Tile getTile(const Position& pos) const;
private:
	std::vector< std::vector< std::vector<Tile> > > map;
	std::vector< std::vector<Tile> > newLevel(int width, int height, int level);
};


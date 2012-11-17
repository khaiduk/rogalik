#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "ImageRes.h"

/**
 * Pojedynczy kafelek terenu
 * Kafelek posiada wygl¹d (reprezentacja graficzna) oraz w³asnoœci fizyczne
 * (tj. po³o¿enie, mo¿liwoœæ przejœcia, itp.)
 */
class Tile
{
public:
	/**
	 * Tworzy kafelkê o zadanym po³o¿eniu i wygl¹dzie
	 * @param pos po³o¿enie kafelki
	 * @param img identyfikator obrazka
	 */
	Tile(const Position pos, int img = 0);
	/**
	 * Wyœwietla kafelkê na ekranie w zadanym miejscu
	 * @param rw okno rysowania
	 * @param x przesuniêcie wzglêdem pocz¹tku okna
	 * @param y przesuniêcie wzglêdem pocz¹tku okna
	 */
	void draw(sf::RenderWindow& rw, int x, int y) const;
	/**
	 * Ustawia wygl¹d kafelki na img
	 * @param img identyfikator obrazka
	 */
	void setImage(int img);
private:
	Position pos;
	sf::Sprite sprite;

};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Position.h"
#include "Terrain.h"
#include "ImageRes.h"

/**
 * Postac wystêpuj¹ca w swiecie gry, taka jak NPC i wrogowie
 */
class Creature
{
public:
	/**
	 * Tworzy postaæ o zadanym po³o¿eniu i wygl¹dzie
	 */
	Creature(const Position pos = Position(0,0), int img = 0);

	/**
	 * Ustawia wygl¹d postaci
	 */
	void setSprite(int img);

	/**
	 * Rysuje postaæ na ekranie
	 */
	void draw(sf::RenderWindow& rw, const Position& shift) const;

	/**
	 * Zmienia po³o¿enie postaci
	 */
	void setPosition(const Position& pos);

	/**
	 * Pobiera po³o¿enie postaci
	 */
	Position getPosition() const;

	/**
	 * Przemieszcza postaæ zgodnie z mechanik¹ gry
	 */
	void move(const Position& dp, const Terrain& terrain);

	/**
	 * Stara siê wykonaæ ruch w danym kierunku
	 */
	void walk(const Position& dp, const Terrain& terrain);;
protected:
	Position pos;
	Position walkDir;
	Position lastDir;

	sf::Sprite sprite;

	int walkPower;
	int speed;
};


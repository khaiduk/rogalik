#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Position.h"
#include "Terrain.h"
#include "ImageRes.h"

/**
 * Postac wyst�puj�ca w swiecie gry, taka jak NPC i wrogowie
 */
class Creature
{
public:
	/**
	 * Tworzy posta� o zadanym po�o�eniu i wygl�dzie
	 */
	Creature(const Position pos = Position(0,0), int img = 0);

	/**
	 * Ustawia wygl�d postaci
	 */
	void setSprite(int img);

	/**
	 * Rysuje posta� na ekranie
	 */
	void draw(sf::RenderWindow& rw, const Position& shift) const;

	/**
	 * Zmienia po�o�enie postaci
	 */
	void setPosition(const Position& pos);

	/**
	 * Pobiera po�o�enie postaci
	 */
	Position getPosition() const;

	/**
	 * Przemieszcza posta� zgodnie z mechanik� gry
	 */
	void move(const Position& dp, const Terrain& terrain);

	/**
	 * Stara si� wykona� ruch w danym kierunku
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


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Position.h"
#include "Terrain.h"
#include "ImageRes.h"
#include "Item.h"
#include "Dialog.h"

class Player;
class Game;

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

	bool isAlive() const;

	/**
	 * Przemieszcza posta� zgodnie z mechanik� gry
	 */
	void move(const Position& dp, const Terrain& terrain);

	void fight(Creature& creature);

	/**
	 * Stara si� wykona� ruch w danym kierunku
	 */
	void walk(const Position& dp, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game);

	/**
	 * Spos�b zachowania si� postaci
	 */
	enum AI
	{
		IDLE,
		RANDOM_WALK
	};
	/**
	 * Wykonuje krok symulacji
	 */
	void step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game);

	enum Type
	{
		PLAYER,
		DIALOG,
		HOSTILE
	};

	void giveLootToPlayer(Player& player);
	
	friend class GameBuilder;

protected:
	/**
	 * Ustawia pr�dko�� postaci
	 * Warto�� domy�lna to 10,
	 * 20 - posta� 2 razy szybsza
	 * 5 - posta� 2 razy wolniejsza
	 */
	void setSpeed(int speed);

	
	/**
	 * Ustawia spos�b zachowania si� postaci
	 */
	void setAI(const AI ai);
	
	
	void setType(const Type type);

	void addLoot(const Item& item);

	void addDialog(const Dialog& dialog);

protected:
	Position pos;
	Position walkDir;
	Position lastDir;

	sf::Sprite sprite;

	int walkPower;
	int speed;

	AI ai;
	Type type;

	float health;

	std::list<Item> loot;
	Dialog dialog;
};


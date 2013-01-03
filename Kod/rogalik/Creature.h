#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Position.h"
#include "Terrain.h"
#include "ImageRes.h"
#include "Item.h"
#include "Dialog.h"
#include "Trading.h"

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

	/**
	 * Zwraca true gdy posta� jescze �yje
	 */
	bool isAlive() const;

	/**
	 * Przemieszcza posta� zgodnie z mechanik� gry
	 */
	void move(const Position& dp, const Terrain& terrain);

	/**
	 * Wykonanie ataku na postaci
	 * @param creature Posta� na kt�rej jest wykonywany atak
	 */
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
		RANDOM_WALK, // losowe b��dzenie - ci�ko z�apa�
		OFFENSIVE_SLOW, //pod��a tam, gdzie przed chwil� by� gracz
		OFFENSIVE_FAST, //pod��a tam, gdzie teraz jest gracz
		FIGHT_AND_FLEE // po��czenie OFFENSIVE_FAST z RANDOM_WALK - atakuje turami
	};
	/**
	 * Wykonuje krok symulacji
	 * @param dt D�ugo�� kroku czasowego
	 * @param terrain Teren (mapa) w jakim znajduje si� posta�
	 * @param creatures Lista postaci niezale�nych na mapie
	 * @param player Posta� gracza
	 * @param game Obiekt gry
	 */
	void step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game);

	/**
	 * Typ postaci
	 */
	enum Type
	{
		PLAYER,
		DIALOG,
		TRADE,
		HOSTILE
	};

	/**
	 * Oddaje posiadane przedmioty jako �up postaci gracza
	 */
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
	 * Ustawia wsp�czynnik ataku postaci
	 * Warto�� domy�lna to 0.01
	 */
	void setAttack(int attack);
	
	/**
	 * Ustawia wsp�czynnik obrony postaci
	 * Warto�� domy�lna to 0.1
	 */
	void setDefence(int defence);

	/**
	 * Ustawia wsp�czynnik cz�sto�ci atak�w postaci
	 * Warto�� domy�lna to 0.1
	 */
	void setHitrate(int hitrate);

	
	/**
	 * Ustawia spos�b zachowania si� postaci
	 */
	void setAI(const AI ai);
	
	/**
	 * Ustawia typ postaci
	 */
	void setType(const Type type);

	/**
	 * Dodaje przedmiot �upu
	 */
	void addLoot(const Item& item);

	/**
	 * Ustawia obiekt dialogu
	 */
	void addDialog(const Dialog& dialog);

	/**
	 * Ustawia obiekt handlu
	 */
	void addTrade(const Trading& trading);
	
	/**
	 * Zwraca wsp�czynnik ataku postaci
	 */
	virtual float getAttack();

	/**
	 * Zwraca wsp�czynnik obrony postaci
	 */
	virtual float getDefence();

	/**
	 * Regenacja mo�liwo�ci ataku postaci
	 */
	void hitRegen();
protected:
	

	Position pos;
	Position walkDir;
	Position lastDir;

	sf::Sprite sprite;

	int walkPower;
	int speed;
	float fightPower;
	int xp;
	float def;
	float att;
	float hitrate;


	AI ai;
	Type type;

	float health;

	std::list<Item> loot;
	Dialog dialog;
	Trading trading;

	// u�ywane przez AI:
	Position newPos;
	Position cpos;
	bool fightState;
};


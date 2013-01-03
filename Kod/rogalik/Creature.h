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
	 * Zwraca true gdy postaæ jescze ¿yje
	 */
	bool isAlive() const;

	/**
	 * Przemieszcza postaæ zgodnie z mechanik¹ gry
	 */
	void move(const Position& dp, const Terrain& terrain);

	/**
	 * Wykonanie ataku na postaci
	 * @param creature Postaæ na której jest wykonywany atak
	 */
	void fight(Creature& creature);

	/**
	 * Stara siê wykonaæ ruch w danym kierunku
	 */
	void walk(const Position& dp, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game);

	/**
	 * Sposób zachowania siê postaci
	 */
	enum AI
	{
		IDLE,
		RANDOM_WALK, // losowe b³¹dzenie - ciê¿ko z³apaæ
		OFFENSIVE_SLOW, //pod¹¿a tam, gdzie przed chwil¹ by³ gracz
		OFFENSIVE_FAST, //pod¹¿a tam, gdzie teraz jest gracz
		FIGHT_AND_FLEE // po³¹czenie OFFENSIVE_FAST z RANDOM_WALK - atakuje turami
	};
	/**
	 * Wykonuje krok symulacji
	 * @param dt D³ugoœæ kroku czasowego
	 * @param terrain Teren (mapa) w jakim znajduje siê postaæ
	 * @param creatures Lista postaci niezale¿nych na mapie
	 * @param player Postaæ gracza
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
	 * Oddaje posiadane przedmioty jako ³up postaci gracza
	 */
	void giveLootToPlayer(Player& player);
	
	friend class GameBuilder;

protected:
	/**
	 * Ustawia prêdkoœæ postaci
	 * Wartoœæ domyœlna to 10,
	 * 20 - postaæ 2 razy szybsza
	 * 5 - postaæ 2 razy wolniejsza
	 */
	void setSpeed(int speed);
	
	/**
	 * Ustawia wspó³czynnik ataku postaci
	 * Wartoœæ domyœlna to 0.01
	 */
	void setAttack(int attack);
	
	/**
	 * Ustawia wspó³czynnik obrony postaci
	 * Wartoœæ domyœlna to 0.1
	 */
	void setDefence(int defence);

	/**
	 * Ustawia wspó³czynnik czêstoœci ataków postaci
	 * Wartoœæ domyœlna to 0.1
	 */
	void setHitrate(int hitrate);

	
	/**
	 * Ustawia sposób zachowania siê postaci
	 */
	void setAI(const AI ai);
	
	/**
	 * Ustawia typ postaci
	 */
	void setType(const Type type);

	/**
	 * Dodaje przedmiot ³upu
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
	 * Zwraca wspó³czynnik ataku postaci
	 */
	virtual float getAttack();

	/**
	 * Zwraca wspó³czynnik obrony postaci
	 */
	virtual float getDefence();

	/**
	 * Regenacja mo¿liwoœci ataku postaci
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

	// u¿ywane przez AI:
	Position newPos;
	Position cpos;
	bool fightState;
};


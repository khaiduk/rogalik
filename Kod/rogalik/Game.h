#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "Creature.h"
#include "Player.h"
#include "Menu.h"
/**
 * Klasa g³ówna gry.
 */
class Game
{
public:
	Game(void);

	/**
	 * Pobiera wejœcie
	 * @param e Przekazywane zdarzenie
	 */
	void getInput(const sf::Event& e);

	/**
	 * Wykonuje krok symulacji
	 * @param dt D³ugoœæ kroku czasowego
	 */
	void step(float dt);

	/**
	 * Rysuje grê na ekranie
	 * @param rw Obiekt okna na którym bêdzie rysowana gra
	 */
	void draw(sf::RenderWindow& rw);

	/**
	 * Stan gry
	 */
	enum GameState
	{
		INGAME,
		INVENTORY,
		ATRIBUTES,
		GAMEMENU,
		DIALOG,
		TRADE
	};

	/**
	 * Zwraca obecny stan gry
	 */
	GameState getState() const;
	
	/**
	 * Ustawia stan gry na dialog z postaci¹
	 * @param dialog Obiekt dialogu
	 */
	void setDialog(Dialog& dialog);
	
	/**
	 * Ustawia stan gry na handel z postaci¹
	 * @param dialog Obiekt dialogu
	 */
	void setTrade(Trading& trade);
private:
	Terrain terrain;
	Player player;
	std::list<Creature> creatures;
	GameState gameState;
	Menu m;
	Dialog *currentDialog;
	Trading *currentTrade;

	friend class GameBuilder;
};


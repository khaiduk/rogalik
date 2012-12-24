#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "Creature.h"
#include "Player.h"

/**
 * Klasa g³ówna gry.
 */
class Game
{
public:
	Game(void);
	~Game(void);

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
	void draw(sf::RenderWindow& rw) const;

	enum GameState
	{
		INGAME,
		INVENTORY,
		DIALOG
	};

	GameState getState() const;

	void setDialog(Dialog& dialog);
private:
	Terrain terrain;
	Player player;
	std::list<Creature> creatures;
	GameState gameState;

	Dialog *currentDialog;

	friend class GameBuilder;
};


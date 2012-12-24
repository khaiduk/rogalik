#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "Creature.h"
#include "Player.h"

/**
 * Klasa g��wna gry.
 */
class Game
{
public:
	Game(void);

	/**
	 * Pobiera wej�cie
	 * @param e Przekazywane zdarzenie
	 */
	void getInput(const sf::Event& e);

	/**
	 * Wykonuje krok symulacji
	 * @param dt D�ugo�� kroku czasowego
	 */
	void step(float dt);

	/**
	 * Rysuje gr� na ekranie
	 * @param rw Obiekt okna na kt�rym b�dzie rysowana gra
	 */
	void draw(sf::RenderWindow& rw) const;

	/**
	 * Stan gry
	 */
	enum GameState
	{
		INGAME,
		INVENTORY,
		DIALOG
	};

	/**
	 * Zwraca obecny stan gry
	 */
	GameState getState() const;

	/**
	 * Ustawia stan gry na dialog z postaci�
	 * @param dialog Obiekt dialogu
	 */
	void setDialog(Dialog& dialog);
private:
	Terrain terrain;
	Player player;
	std::list<Creature> creatures;
	GameState gameState;

	Dialog *currentDialog;

	friend class GameBuilder;
};


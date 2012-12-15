#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "Player.h"
#include "NPC.h"
#include "Enemy.h"

/**
 * Klasa g��wna gry.
 */
class Game
{
public:
	Game(void);
	~Game(void);

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
private:
	Terrain terrain;
	Player player;
	std::list<NPC> npcs;
	std::list<Enemy> enemies;

	friend class GameBuilder;
};


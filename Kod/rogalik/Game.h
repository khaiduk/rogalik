#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Terrain.h"
#include "Player.h"
#include "NPC.h"

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
	 * @param key Przekazywane zdarzenie klawiatury
	 */
	void getInput(const sf::Event::KeyEvent& key);

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
private:
	Terrain terrain;
	Player player;
	std::list<Creature> npcs;
};


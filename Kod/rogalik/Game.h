#pragma once
#include <SFML/Graphics.hpp>
#include "Terrain.h"

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
	 * @param key Przekazywane zdarzenie klawiatury
	 */
	void getInput(const sf::Event::KeyEvent& key);

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
	Position playerpos; // do wymiany
};


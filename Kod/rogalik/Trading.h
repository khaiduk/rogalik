#pragma once
#include <SFML/Graphics.hpp>

class Player;

/**
 * Dialog handlu postaci gracza z postaci¹ niezale¿n¹
 */
class Trading
{
public:
	Trading(void);
	/**
	 * Rysuje okno (interfejs) handlu z postaci¹
	 * @param rw Obiekt okna na którym bêdzie rysowany interfejs
	 */
	void draw(sf::RenderWindow& rw);

	/**
	 * Pobiera wejœcie
	 * @param e Przekazywane zdarzenie
	 * @param player Postaæ gracza
	 */
	bool getInput(const sf::Event& e, Player& player);
};


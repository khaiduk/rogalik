#pragma once
#include <SFML/Graphics.hpp>

class Player;

/**
 * Dialog handlu postaci gracza z postaci� niezale�n�
 */
class Trading
{
public:
	Trading(void);
	/**
	 * Rysuje okno (interfejs) handlu z postaci�
	 * @param rw Obiekt okna na kt�rym b�dzie rysowany interfejs
	 */
	void draw(sf::RenderWindow& rw);

	/**
	 * Pobiera wej�cie
	 * @param e Przekazywane zdarzenie
	 * @param player Posta� gracza
	 */
	bool getInput(const sf::Event& e, Player& player);
};


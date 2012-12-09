#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
public:
	/**
	** Domyslny konstruktor w ktory wczytujemy obrazki
	**/
	Menu();

	/**
	** Funkcja odpowiadajaca za 'rysowanie' menu @param rw Obiekt okna na kt�rym b�dzie rysowane menu
	**/
	void draw(sf::RenderWindow& rw) const;
private:
	sf::Image tlo,opcje,start,wczytaj,wyjscie;
};
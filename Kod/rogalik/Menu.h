#pragma once
#include <SFML/Graphics.hpp>

/**
 * Menu g³ówne gry
 */
class Menu
{
public:
//	struct node{
	//	sf::Image *wsk;
	//	bool wartosc;
//	};
	/**
	** Domyslny konstruktor w ktory wczytujemy obrazki, definiujemy poczatkowe wartosci zmiennych
	**/
	Menu();
	~Menu();
	/**
	** Funkcja odpowiadajaca za 'rysowanie' menu @param rw Obiekt okna na którym bêdzie rysowane menu
	**/
	void draw(sf::RenderWindow& rw);
	/**
	**	Funkcja ustawiajaca prywatna wartosc klassy
	**/
	void drawMenuGame(sf::RenderWindow& rw);
	void setVar(const bool ws);
	/**
	** Funkcja pobierajaca prywatna wartosc klasy @return var - prywatna zmienna typu bool
	**/
	bool getVar() const;
	/**
	** Funkcja odpowiadajaca za obsluge klawiatury w menu @Param przycisk do obsluzenia
	**/
	void Action(const sf::Event& e);
	void ActionGameMenu(const sf::Event& e);
private:
	sf::Image tlo,opcje,start,wczytaj,wyjscie;
	bool var;
	//node *tab;
	bool *_tab;
	int _indeks;
};
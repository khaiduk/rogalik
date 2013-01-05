#pragma once
#include <SFML/Graphics.hpp>

/**
 * Menu g³ówne gry
 */
class Menu
{
public:
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
	** Funkcja rysujaca menu w grze
	**/
	void drawMenuGame(sf::RenderWindow& rw);
	/**
	**	Funkcja ustawiajaca prywatna wartosc klassy
	**/
	void setOustsideGame(const bool ws);
	/**
	** Funkcja pobierajaca prywatna wartosc klasy @return var - prywatna zmienna typu bool
	**/
	bool isOutsideGame () const;
	/**
	** Funkcja odpowiadajaca za obsluge klawiatury w menu @Param przycisk do obsluzenia
	**/
	void Action(const sf::Event& e);
	/**
	** Funkcja odpowiadajaca za obsluge klawiatury w menu gry @Param przycisk do obsluzenia
	**/
	void ActionGameMenu(const sf::Event& e);
	/**
	** Funkcja odpowiadajaca za wyjscie z gry @return _exit argument typu bool odpowiadajacy za exit
	**/
	bool shouldExit() const;
private:
	sf::Image tlo,opcje,start,wczytaj,wyjscie;
	bool var;
	bool _exit;
	int _indeks;
};
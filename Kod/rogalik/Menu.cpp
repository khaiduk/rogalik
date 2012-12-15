#include "Menu.h"
#include <iostream>
Menu::Menu()
{
	tlo.LoadFromFile("tlo.png");
	start.LoadFromFile("start.png");
	opcje.LoadFromFile("opcje.png");
	wczytaj.LoadFromFile("wczytaj.png");
	wyjscie.LoadFromFile("wyjscie.png");
}
void Menu::draw(sf::RenderWindow& rw) const
{
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	sf::Sprite startH(start,sf::Vector2f(296,240));
	rw.Draw(startH);
	sf::Sprite opcjeH(opcje,sf::Vector2f(292,294));
	rw.Draw(opcjeH);
	sf::Sprite wczytajH(wczytaj,sf::Vector2f(296,349));
	rw.Draw(wczytajH);
	sf::Sprite wyjscieH(wyjscie,sf::Vector2f(294,404));
	rw.Draw(wyjscieH);
}
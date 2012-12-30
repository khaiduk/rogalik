#include "Menu.h"
#include <iostream>
Menu::Menu()
{
	_indeks = 0;
	tlo.LoadFromFile("Images/tlo.png");
	var = true;
}
Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow& rw)
{
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	if(_indeks == 0)
		start.LoadFromFile("Images/start.png");
	else
		start.LoadFromFile("Images/start1.png");
	sf::Sprite startH(start,sf::Vector2f(296,240));
	rw.Draw(startH);
	if(_indeks == 1)
		opcje.LoadFromFile("Images/opcje1.png");
	else
		opcje.LoadFromFile("Images/opcje.png");
	sf::Sprite opcjeH(opcje,sf::Vector2f(292,294));
	rw.Draw(opcjeH);
	if(_indeks == 2)
		wczytaj.LoadFromFile("Images/wczytaj1.png");
	else
		wczytaj.LoadFromFile("Images/wczytaj.png");
	sf::Sprite wczytajH(wczytaj,sf::Vector2f(296,349));
	rw.Draw(wczytajH);
	if(_indeks == 3)
		wyjscie.LoadFromFile("Images/wyjscie1g.png");
	else
		wyjscie.LoadFromFile("Images/wyjscieg.png");
	sf::Sprite wyjscieH(wyjscie,sf::Vector2f(294,404));
	rw.Draw(wyjscieH);
}
void Menu::drawMenuGame(sf::RenderWindow& rw)
{
	static sf::Image wznow,zapisz;
	if(_indeks == 0)
		wznow.LoadFromFile("Images/wznow1.png");
	else
		wznow.LoadFromFile("Images/wznow.png");
	if(_indeks == 1)
		zapisz.LoadFromFile("Images/zapisz1.png");
	else
		zapisz.LoadFromFile("Images/zapisz.png");
	if(_indeks == 2)
		wyjscie.LoadFromFile("Images/wyjscie1.png");
	else
		wyjscie.LoadFromFile("Images/wyjscie.png");
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	sf::Sprite wznowH(wznow,sf::Vector2f(270,210));
	rw.Draw(wznowH);
	sf::Sprite zapiszH(zapisz,sf::Vector2f(275,269));
	rw.Draw(zapiszH);
	sf::Sprite wyjscieH(wyjscie,sf::Vector2f(280,329));
	rw.Draw(wyjscieH);
}
void Menu::setOustsideGame(const bool ws)
{
	var = ws;
}
bool Menu::isOutsideGame () const
{
	return var;
}
void Menu::Action(const sf::Event& e)
{
	if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::N)
	{
		var=false;
	}
	else if (e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::O)
	{
		//opcje
	}
	else if(e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::W)
	{
		//wczytaj
	}
	else if(e.Type == sf::Event::KeyPressed && e.Key.Code ==  sf::Key::Up)
	{
		if(_indeks > 0)
		{
			_indeks--;
		}
	}
	else if(e.Key.Code ==  sf::Key::Down && e.Type == sf::Event::KeyPressed)
	{
		if(_indeks < 3)
			_indeks++;
	}
	else if(e.Key.Code ==  sf::Key::Space && e.Type == sf::Event::KeyPressed)
	{
		for(int i = 0 ; i < 4 ; i++)
			if(_indeks == 0)
				var=false;
			else if (_indeks == 1)
				break; //wczytaj
			else if(_indeks == 2)
				break;//opcje
			else if(_indeks == 3)
				break; //exit
	}
}
void Menu::ActionGameMenu(const sf::Event& e)
{
	if(e.Type == sf::Event::KeyPressed && e.Key.Code ==  sf::Key::Up)
	{
		if(_indeks > 0)
		{
			_indeks--;
		}
	}
	else if(e.Key.Code ==  sf::Key::Down && e.Type == sf::Event::KeyPressed)
	{
		if(_indeks < 2)
			_indeks++;
	}
}
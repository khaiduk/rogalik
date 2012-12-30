#include "Menu.h"
#include <iostream>
int Menu::_indeks = 0;
Menu::Menu()
{
	tab = new node[5];
	_tab = new bool[4];
	_tab[0] = true;
	tlo.LoadFromFile("tlo.png");
	/*start.LoadFromFile("start.png");
	opcje.LoadFromFile("opcje.png");
	wczytaj.LoadFromFile("wczytaj.png");
	wyjscie.LoadFromFile("wyjscie.png");*/
	var = true;

	//tab[0].wsk = &tlo;
	//tab[0].wartosc = false;
}
void Menu::draw(sf::RenderWindow& rw)
{
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	if(_tab[0])
		start.LoadFromFile("ee.png");
	else
		start.LoadFromFile("start.png");
	sf::Sprite startH(start,sf::Vector2f(296,240));
	rw.Draw(startH);
	if(_tab[1])
		opcje.LoadFromFile("ee.png");
	else
		opcje.LoadFromFile("opcje.png");
	sf::Sprite opcjeH(opcje,sf::Vector2f(292,294));
	rw.Draw(opcjeH);
	if(_tab[2])
		wczytaj.LoadFromFile("ee.png");
	else
		wczytaj.LoadFromFile("wczytaj.png");
	sf::Sprite wczytajH(wczytaj,sf::Vector2f(296,349));
	rw.Draw(wczytajH);
	if(_tab[3])
		wyjscie.LoadFromFile("ee.png");
	else
		wyjscie.LoadFromFile("wyjscie.png");
	sf::Sprite wyjscieH(wyjscie,sf::Vector2f(294,404));
	rw.Draw(wyjscieH);
}
void Menu::setVar(const bool ws)
{
	var = ws;
}
bool Menu::getVar() const
{
	return var;
}
void Menu::Action(sf::Key::Code wsk)
{
	if(wsk == sf::Key::N)
	{
		var=false;
	}
	else if (wsk == sf::Key::O)
	{
		//opcje
	}
	else if(wsk == sf::Key::W)
	{
		//wczytaj
	}
	else if(wsk ==  sf::Key::Up)
	{
		//std::cout<< "Strzala w gore"<< std::endl;
		if(_indeks > 0)
		{
			_indeks--;
			for(int i = 0 ; i < 4 ;i++)
				_tab[i] = false;
			_tab[_indeks] = true;
		}
	}
	else if(wsk ==  sf::Key::Down)
	{
		//std::cout << "Strzala w dol"<< std::endl;
		if(_indeks < 4)
			_indeks++;
		for(int i = 0 ; i < 4 ;i++)
				_tab[i] = false;
		_tab[_indeks] = true;
		//std::cout<<_indeks << std::endl;
	}
}
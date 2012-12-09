#include <SFML/Graphics.hpp>
#include "GameBuilder.h"
#include "Game.h"
#include "ImageRes.h"
#include "Menu.h"


int main()
{
	bool x = true;
	float TIME_STEP = 0.03f;

	sf::Clock clock;
	float timeAcc = 0;
	sf::RenderWindow App(sf::VideoMode(ImageRes::WIDTH, ImageRes::HEIGHT), "Rogalik");
	ImageRes::getInstance().loadImages("tiles.png", 8, 0);
	
	GameBuilder gb;
	Menu m;
	gb.generateNewGame();
	Game game = gb.getGame();
	bool var = true;

	while(App.IsOpened())
	{
		sf::Event Event;
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed || Event.Key.Code=='e')
				App.Close();
			else if (Event.Key.Code=='n')
			{
				var = false;
				//create game
			}
			else if (Event.Key.Code=='o')
			{
				//opcje
			}
			else if(Event.Key.Code=='w')
			{
				//wczytaj
			}
		}
		if(var)
		{
			App.Clear();
			m.draw(App);
			App.Display();
		}
		else
		{
			if (Event.Type == sf::Event::KeyPressed)
			{
				game.getInput(Event.Key);
			}
			timeAcc += clock.GetElapsedTime();
			while(timeAcc > TIME_STEP)
			{
				game.step(TIME_STEP);
				timeAcc -= TIME_STEP;
			}
			clock.Reset();

			App.Clear();
			game.draw(App);
		
			App.Display();
		}
	}
    return EXIT_SUCCESS;
}

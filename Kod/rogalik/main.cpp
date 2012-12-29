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
	std::cout << m.getVar() ;
	while(App.IsOpened())
	{
		sf::Event Event;
		if(m.getVar()) while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed || Event.Key.Code=='e' )//|| Event.Key.Code == sf::Key::Escape)
				App.Close();
			else
			{
				m.Action(Event.Key.Code);
			}
		}
		if(m.getVar())
		{
			App.Clear();
			m.draw(App);
			App.Display();
		}
		else
		{
			while(App.GetEvent(Event))
			{
				if(Event.Type == sf::Event::Closed || Event.Key.Code=='e')
				{
					App.Close();
				}
				else if (Event.Type == sf::Event::KeyPressed || Event.Type == sf::Event::KeyReleased)
				{
					game.getInput(Event);
				}
			}

			// czas jest symulowany tylko w czasie rozgrywki - nie w interferjsach takich jak
			//   ekwipunek, dialogi, itp...
			if(game.getState() == Game::INGAME)
			{
				timeAcc += clock.GetElapsedTime();
				while(timeAcc > TIME_STEP)
				{
					game.step(TIME_STEP);
					timeAcc -= TIME_STEP;
				}
				clock.Reset();
			}
			else
			{
				clock.Reset();
			}

			App.Clear();
			game.draw(App);
		
			App.Display();
		}
	}
    return EXIT_SUCCESS;
}

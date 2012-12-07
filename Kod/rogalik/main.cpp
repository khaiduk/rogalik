#include <SFML/Graphics.hpp>
#include "GameBuilder.h"
#include "Game.h"
#include "ImageRes.h"

int main()
{
	bool x = true;
	float TIME_STEP = 0.03f;

	sf::Clock clock;
	float timeAcc = 0;
	sf::RenderWindow App(sf::VideoMode(ImageRes::WIDTH, ImageRes::HEIGHT), "Rogalik");
	ImageRes::getInstance().loadImages("tiles.png", 8, 0);

	GameBuilder gb;
	gb.generateNewGame();
	Game game = gb.getGame();


    while (App.IsOpened())
    {
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();
            else if (Event.Type == sf::Event::KeyPressed)
			{
				game.getInput(Event.Key);
			}
			
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

    return EXIT_SUCCESS;
}

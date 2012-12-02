#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ImageRes.h"

int main()
{
	bool x = true;

	sf::Clock clock;
	float lastTime = clock.GetElapsedTime();
	sf::RenderWindow App(sf::VideoMode(ImageRes::WIDTH, ImageRes::HEIGHT), "Rogalik");
	ImageRes::getInstance().loadImages("tiles.png", 8, 0);
	Game game;


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

		float dt = clock.GetElapsedTime() - lastTime;
		lastTime += dt;

        App.Clear();
		game.draw(App);
		
        App.Display();
    }

    return EXIT_SUCCESS;
}

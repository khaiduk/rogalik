#include <SFML/Graphics.hpp>

int main()
{
	bool x = true;

    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML Basic Window");

    while (App.IsOpened())
    {
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                App.Close();
            else if (Event.Type == sf::Event::KeyPressed)
			{
				if(Event.Key.Code == sf::Key::Up)
				{
					x = !x;
				}
			}
			
        }

        App.Clear();
		if(x)
			App.Draw(sf::Shape::Rectangle(200, 150, 600, 450, sf::Color::Green));
		else
			App.Draw(sf::Shape::Rectangle(200, 150, 600, 450, sf::Color::Red));
		App.Draw(sf::String("Press up arrow"));

        App.Display();
    }

    return EXIT_SUCCESS;
}

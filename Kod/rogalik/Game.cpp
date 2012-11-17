#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::getInput(const sf::Event::KeyEvent& key)
{
	if(key.Code == sf::Key::Up)
	{
		playerpos.move(0,-1);
	}
	else if(key.Code == sf::Key::Down)
	{
		playerpos.move(0,1);
	}
	else if(key.Code == sf::Key::Right)
	{
		playerpos.move(1,0);
	}
	else if(key.Code == sf::Key::Left)
	{
		playerpos.move(-1,0);
	}
}

void Game::step(float dt)
{

}

void Game::draw(sf::RenderWindow& rw) const
{
	terrain.draw(rw, playerpos);
	sf::Sprite playerSprite(ImageRes::getInstance().getImage(1));
	playerSprite.SetPosition(12 * ImageRes::TILESIZE, 10* ImageRes::TILESIZE);
	rw.Draw(playerSprite);
}
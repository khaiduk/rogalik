#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::getInput(const sf::Event& e)
{
	if(	e.Key.Code == sf::Key::Up ||
		e.Key.Code == sf::Key::Down ||
		e.Key.Code == sf::Key::Right ||
		e.Key.Code == sf::Key::Left)
	{
		player.getInput(e);
	}
}

void Game::step(float dt)
{
	player.step(dt, terrain);
	for(std::list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		if(i->getPosition().GetZ() == player.getPosition().GetZ()) // symuluj tylko przeciwników na tym samym poziomie
			i->step(dt, terrain, player);
	}
}

void Game::draw(sf::RenderWindow& rw) const
{
	Position dp;
	dp = terrain.calculateShift(player.getPosition());
	terrain.draw(rw, player.getPosition().GetZ(), dp);
	for(std::list<Creature>::const_iterator i = creatures.begin(); i != creatures.end(); i++)
	{
		if(i->getPosition().GetZ() == player.getPosition().GetZ())
			i->draw(rw, dp);
	}

	for(std::list<Enemy>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
	{
		if(i->getPosition().GetZ() == player.getPosition().GetZ())
			i->draw(rw, dp);
	}

	player.draw(rw, dp);
	player.drawHud(rw);
}
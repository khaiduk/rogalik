#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::getInput(const sf::Event::KeyEvent& key)
{
	Position dp;
	if(key.Code == sf::Key::Up)
	{
		dp.SetY(-1);
	}
	else if(key.Code == sf::Key::Down)
	{
		dp.SetY(1);
	}
	else if(key.Code == sf::Key::Right)
	{
		dp.SetX(1);
	}
	else if(key.Code == sf::Key::Left)
	{
		dp.SetX(-1);
	}

	player.move(dp, terrain);
}

void Game::step(float dt)
{
	player.replenishHealth();
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
	for(std::list<NPC>::const_iterator i = npcs.begin(); i != npcs.end(); i++)
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
#include "Game.h"


Game::Game(void)
{
	player.setPosition(Position(0, 2));
	npcs.push_back( NPC(Position(0,1, 0), ImageRes::DEALER) );
	npcs.push_back( NPC(Position(8,1, 1), ImageRes::DEALER) );
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

}

void Game::draw(sf::RenderWindow& rw) const
{
	Position dp;
	dp = terrain.calculateShift(player.getPosition());
	terrain.draw(rw, player.getPosition().GetZ(), dp);
	for(std::list<Creature>::const_iterator i = npcs.begin(); i != npcs.end(); i++)
	{
		if(i->getPosition().GetZ() == player.getPosition().GetZ())
			i->draw(rw, dp);
	}
	player.draw(rw, dp);
	player.drawHud(rw);
}
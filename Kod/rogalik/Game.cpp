#include "Game.h"


Game::Game(void) : gameState(INGAME), currentDialog(NULL)
{
}

void Game::getInput(const sf::Event& e)
{
	if(gameState == INGAME)
	{
		if(	e.Key.Code == sf::Key::Up ||
			e.Key.Code == sf::Key::Down ||
			e.Key.Code == sf::Key::Right ||
			e.Key.Code == sf::Key::Left)
		{
			player.getInput(e);
		}
		else if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::I) // inventory
		{
			gameState = INVENTORY;
		}
	}
	else if(gameState == INVENTORY)
	{
		if( e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::I ||
			e.Key.Code == sf::Key::Escape)) // wyjscie z inventory
		{
			gameState = INGAME;
		}
	}
	else if(gameState == DIALOG)
	{
		if( e.Type == sf::Event::KeyPressed &&
			e.Key.Code == sf::Key::Escape) // wyjscie z dialogu
		{
			gameState = INGAME;
			currentDialog = NULL;
		}
		else
		{
			if(currentDialog->getInput(e))
			{
				gameState = DIALOG;
			}
			else
			{
				gameState = INGAME;
				currentDialog->resetDialog();
			}
		}
	}
}

void Game::step(float dt)
{
	player.step(dt, terrain, creatures, *this);
	for(std::list<Creature>::iterator i = creatures.begin(); i != creatures.end();)
	{
		if(i->getPosition().GetZ() == player.getPosition().GetZ()) // symuluj tylko postacie na tym samym poziomie
		{
			i->step(dt, terrain, creatures, player, *this);
		}
		if(! i->isAlive() )
		{
			i->giveLootToPlayer(player);
			i = creatures.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Game::draw(sf::RenderWindow& rw) const
{
	if(gameState == INGAME)
	{
		Position dp;
		dp = terrain.calculateShift(player.getPosition());
		terrain.draw(rw, player.getPosition().GetZ(), dp);
		for(std::list<Creature>::const_iterator i = creatures.begin(); i != creatures.end(); i++)
		{
			if(i->getPosition().GetZ() == player.getPosition().GetZ())
				i->draw(rw, dp);
		}

		player.draw(rw, dp);
		player.drawHud(rw);
	}
	else if(gameState == INVENTORY)
	{
		player.drawInventory(rw);
	}
	else if(gameState == DIALOG)
	{
		currentDialog->draw(rw);
	}
}


Game::GameState Game::getState() const
{
	return gameState;
}


void Game::setDialog(Dialog& dialog)
{
	currentDialog = &dialog;
	gameState = DIALOG;
}
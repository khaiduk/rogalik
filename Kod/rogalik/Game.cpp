#include "Game.h"


Game::Game(void) : gameState(INGAME), currentDialog(NULL)
{
}

void Game::getInput(const sf::Event& e)
{
	if(e.Key.Code == sf::Key::Q)
		gameState = GAMEOVER;
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
		else if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::A) // atributes
		{
			gameState = ATRIBUTES;
		}
		else if ( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape)
		{
			m.setOustsideGame(true);
			gameState = GAMEMENU;
		}
	}
	else if(gameState == INVENTORY)
	{
		if( e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::I ||
			e.Key.Code == sf::Key::Escape)) // wyjscie z inventory
		{
			gameState = INGAME;
		}
		else
		{
			player.getInputInventory(e, creatures);
		}
	}
	else if(gameState == ATRIBUTES)
	{
		if( e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::A ||
			e.Key.Code == sf::Key::Escape)) // wyjscie z Atributes
		{
			gameState = INGAME;
		}
		else
		{
			player.getInputAtributes(e);
		}
	}
	else if(gameState == GAMEMENU)
	{
		if( e.Type == sf::Event::KeyPressed && (e.Key.Code == sf::Key::Escape) || m.isOutsideGame() == false) // powrot do gry
		{
			gameState = INGAME;
		}
		else if(m.shouldExit())
		{
			gameState = EXIT;
		}
		else if(e.Type == sf::Event::KeyPressed || e.Type == sf::Event::KeyReleased)
			m.ActionGameMenu(e);
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
			if(currentDialog->getInput(e, player))
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
	else if(gameState == TRADE)
	{
		
		if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape)
		{
			gameState = INGAME;
			currentDialog = NULL;
		}
		else
		{
			if(currentTrade->getInput(e, player))
			{
				gameState = TRADE;
			}
			else
			{
				gameState = INGAME;
			}
		}
	}
	else if(gameState == GAMEOVER || gameState == YOUWIN)
	{
		if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Escape)
		{
			gameState = EXIT;
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
	if(!player.isAlive())
	{
		gameState = GAMEOVER;
	}
	if(player.isWinner())
	{
		gameState = YOUWIN;
	}
}

void Game::draw(sf::RenderWindow& rw)
{
	static bool firstRun = true;
	static sf::Image tlo; //do gameover
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("tlo.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}

	if(gameState == INGAME)
	{
		Position dp;
		dp = terrain.calculateShift(player.getPosition());
		terrain.draw(rw, player.getPosition().GetZ(), dp);
		terrain.drawMinimap(rw, player.getPosition().GetZ());

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
		currentDialog->draw(rw, player);
	}
	else if(gameState == ATRIBUTES)
	{
		player.drawAtributes(rw);
	}
	else if(gameState == GAMEMENU)
	{
		m.drawMenuGame(rw);
	}
	else if(gameState == TRADE)
	{
		currentTrade->draw(rw);
	}
	else if(gameState == GAMEOVER)
	{
		sf::Sprite tloH(tlo);
		rw.Draw(tloH);
		
		sf::String txt(L"Koniec Gry", font, 80);
		txt.SetPosition(180, 50);
		txt.SetColor(sf::Color(20, 18, 160));

		sf::String txt2(L"Naciúnij ESC aby wyjúÊ", font, 30);
		txt2.SetPosition(80, 200);
		txt2.SetColor(sf::Color(20, 18, 160));
		rw.Draw(txt);
		rw.Draw(txt2);
	}
	else if(gameState == YOUWIN)
	{
		sf::Sprite tloH(tlo);
		rw.Draw(tloH);
		
		sf::String txt(L"Wygra≥eú", font, 90);
		txt.SetPosition(180, 50);
		txt.SetColor(sf::Color(20, 18, 160));
		
		sf::String txt1(L"Uda≥o ci siÍ zdobyÊ Rogalik", font, 40);
		txt1.SetPosition(80, 200);
		txt1.SetColor(sf::Color(20, 18, 160));

		sf::String txt2(L"Naciúnij ESC aby wyjúÊ", font, 30);
		txt2.SetPosition(100, 280);
		txt2.SetColor(sf::Color(20, 18, 160));

		rw.Draw(txt);
		rw.Draw(txt1);
		rw.Draw(txt2);
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

void Game::setTrade(Trading& trade)
{
	currentTrade = &trade;
	gameState = TRADE;
}
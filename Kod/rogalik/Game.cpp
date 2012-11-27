#include "Game.h"


Game::Game(void)
{
	playerpos = Position(0, 5);
	someData = "";
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

	try
	{
		Tile newtile = terrain.getTile(playerpos + dp);
		if(newtile.isSolid()) dp = Position(0, 0);
		if(newtile.isWarp())
		{
			playerpos = newtile.getWarp();
			dp = Position(0,0,0);
		}
		someData = newtile.isSolid() ? std::string("solid") : std::string("pass");
	}
	catch(...)
	{
		someData = std::string("noTile");
	}
	playerpos = playerpos + dp;	
}

void Game::step(float dt)
{

}

void Game::draw(sf::RenderWindow& rw) const
{
	terrain.draw(rw, playerpos);
	sf::Sprite playerSprite(ImageRes::getInstance().getImage(ImageRes::HERO));
	playerSprite.SetPosition(12 * ImageRes::TILESIZE, 10* ImageRes::TILESIZE);
	rw.Draw(playerSprite);
	sf::String str(someData);
	rw.Draw(str);
}
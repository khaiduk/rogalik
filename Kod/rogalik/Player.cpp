#include "Player.h"

Player::Player(Position pos) : Creature(pos, ImageRes::HERO), health(0.8), mana(0.60)
{
	hudimg.LoadFromFile("hud.png");
	hbarimg.LoadFromFile("healthbar.png");
	mbarimg.LoadFromFile("manabar.png");
}

void Player::drawHud(sf::RenderWindow& rw) const
{
	sf::Sprite hud(hudimg, sf::Vector2f(0, 350));
	rw.Draw(hud);

	int hbarheight= health * hbarimg.GetHeight();
	sf::Sprite hbar(hbarimg, sf::Vector2f(42, 376 + hbarimg.GetHeight() - hbarheight));
	hbar.SetSubRect(sf::IntRect(0, hbarimg.GetHeight() - hbarheight, hbarimg.GetWidth(), hbarimg.GetHeight()));
	rw.Draw(hbar);

	int mbarheight= mana * mbarimg.GetHeight();
	sf::Sprite mbar(mbarimg, sf::Vector2f(642, 376 + mbarimg.GetHeight() - mbarheight));
	mbar.SetSubRect(sf::IntRect(0, mbarimg.GetHeight() - mbarheight, mbarimg.GetWidth(), mbarimg.GetHeight()));
	rw.Draw(mbar);
}

void Player::replenishHealth()
{
	if(health < 1)
	health += 0.0001;
}


void Player::step(float dt, const Terrain& terrain)
{
	replenishHealth();
	walk(walkDir, terrain);
}

void Player::getInput(const sf::Event& e)
{
	if(e.Type == sf::Event::KeyPressed)
	{
		if(e.Key.Code == sf::Key::Up)
		{
			walkDir.SetY(-1);
		}
		else if(e.Key.Code == sf::Key::Down)
		{
			walkDir.SetY(1);
		}
		else if(e.Key.Code == sf::Key::Right)
		{
			walkDir.SetX(1);
		}
		else if(e.Key.Code == sf::Key::Left)
		{
			walkDir.SetX(-1);
		}
	}
	else if(e.Type == sf::Event::KeyReleased)
	{
		if(e.Key.Code == sf::Key::Up)
		{
			walkDir.SetY(0);
		}
		else if(e.Key.Code == sf::Key::Down)
		{
			walkDir.SetY(0);
		}
		else if(e.Key.Code == sf::Key::Right)
		{
			walkDir.SetX(0);
		}
		else if(e.Key.Code == sf::Key::Left)
		{
			walkDir.SetX(0);
		}
	}
}
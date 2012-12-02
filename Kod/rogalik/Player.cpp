#include "Player.h"

Player::Player(const Position pos) : Creature(pos, ImageRes::HERO), health(1.0), mana(1.0)
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
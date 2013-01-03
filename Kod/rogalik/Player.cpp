#include "Player.h"

Player::Player(Position pos) : Creature(pos, ImageRes::HERO), defLevel(1), attLevel(1), slotWeapon(NULL), slotArmor(NULL)
{
	hudimg.LoadFromFile("hud.png");
	hbarimg.LoadFromFile("healthbar.png");
	setType(PLAYER);
}

void Player::drawHud(sf::RenderWindow& rw) const
{
	sf::Sprite hud(hudimg, sf::Vector2f(0, 350));
	rw.Draw(hud);

	int hbarheight= health * hbarimg.GetHeight();
	sf::Sprite hbar(hbarimg, sf::Vector2f(42, 376 + hbarimg.GetHeight() - hbarheight));
	hbar.SetSubRect(sf::IntRect(0, hbarimg.GetHeight() - hbarheight, hbarimg.GetWidth(), hbarimg.GetHeight()));
	rw.Draw(hbar);
}

void Player::drawInventory(sf::RenderWindow& rw) const
{
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("inv.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}

	sf::Sprite tloH(tlo);
	rw.Draw(tloH);

	float posy = 30.0;
	for(std::list<Item>::const_iterator i = inventory.begin(); i != inventory.end(); i++)
	{
		sf::String t(i->getName(), font, 30.f);
		t.SetColor(sf::Color(20, 18, 160));
		t.SetPosition(20.f, posy);
		rw.Draw(t);
		posy += 30.0;
	}
}
void Player::drawAtributes(sf::RenderWindow& rw) const
{
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("atr.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	
	std::wstringstream ss;
	ss << L"Exp: " << xp << L"\n";
	ss << L"Poziom obrony (+): " << defLevel << L"\n";
	ss << L"Poziom ataku (+): " << attLevel << L"\n";
	sf::String t(ss.str(), font, 30.f);
	t.SetColor(sf::Color(20, 18, 160));
	t.SetPosition(20.f, 20.0);
	rw.Draw(t);
}
void Player::replenishHealth()
{
	if(health < 1)
	health += 0.0001;
}


void Player::step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Game& game)
{
	replenishHealth();
	hitRegen();
	walk(walkDir, terrain, creatures, *this, game);
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

void Player::giveItem(const Item& item)
{
	inventory.push_back(item);
}

float Player::getAttack()
{
	return 0.02 * attLevel;
}

float Player::getDefence()
{
	return 0.2 * defLevel;
}
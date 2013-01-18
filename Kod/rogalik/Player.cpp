#include "Player.h"

Player::Player(Position pos) : Creature(pos, ImageRes::HERO),
	defLevel(1), attLevel(1), selectedAttribute(0),
	coins(100), weapon(-1), armor(-1), selectedItem(0)
{
	hudimg.LoadFromFile("Images/hud.png");
	hbarimg.LoadFromFile("Images/healthbar.png");
	setType(PLAYER);
	Item item = Item(L"name",L"desc",10);
	inventory.push_back(item);
	item = Item(L"Cos",L"Ktos",50);
	inventory.push_back(item);
}

void Player::drawHud(sf::RenderWindow& rw) const
{
	static bool firstRun = true;
	static sf::Font font;
	if(firstRun) 
	{
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}

	sf::Sprite hud(hudimg, sf::Vector2f(0, 350));
	rw.Draw(hud);

	int hbarheight= health * hbarimg.GetHeight();
	sf::Sprite hbar(hbarimg, sf::Vector2f(42, 376 + hbarimg.GetHeight() - hbarheight));
	hbar.SetSubRect(sf::IntRect(0, hbarimg.GetHeight() - hbarheight, hbarimg.GetWidth(), hbarimg.GetHeight()));
	rw.Draw(hbar);

	std::wstring str;
	for(int i=0;i<4;i++)
	{
		if(i<msgList.size())
		str += msgList[i] + L"\n";
	}
	sf::String msgs(str, font, 30);
	msgs.SetColor(sf::Color(120, 10, 10));
	msgs.SetPosition(200, 450);
	rw.Draw(msgs);
}

void Player::drawInventory(sf::RenderWindow& rw) const
{
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun) 
	{
		tlo.LoadFromFile("Images/inv.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}

	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	
	std::stringstream ss;
	ss<<"Masz " << coins << " $";
	sf::String t(ss.str(), font, 30.f);
	t.SetColor(sf::Color(20, 18, 160));
	t.SetPosition(600.f, 30.f);
	rw.Draw(t);

	float posy = 30.0;
	int i = 0;
	for(std::vector<Item>::const_iterator it = inventory.begin(); it != inventory.end(); it++)
	{
		std::wstring name = it->getName();
		if(i == weapon)
		{
			name += L" (uzbrojny - broÒ)";
		}
		if(i == armor)
		{
			name += L" (uzbrojny - zbroja)";
		}
		sf::String t(name, font, 30.f);
		t.SetColor(sf::Color(20, 18, 160));
		if(selectedItem == i)
			t.SetColor(sf::Color(200, 18, 160));
		t.SetPosition(20.f, posy);
		rw.Draw(t);
		posy += 30.0;
		i++;
	}
	if(0 <= selectedItem && selectedItem < inventory.size())
	{
		TextArea desc(inventory[selectedItem].getDesc(), 400, font);
		desc.SetPosition(300, 50);
		rw.Draw(desc);
		Item::Type type = inventory[selectedItem].getProperty();
		if(type == 0)
		{
			TextArea desc1(L"Bron - Atak + " +inventory[selectedItem].getBoost(), 400,font);
			desc1.SetPosition(350,250);
			rw.Draw(desc1);
		}
		else if(type == 1)
		{
			TextArea desc1(L"Zbroja - Obrona + " +inventory[selectedItem].getBoost(), 400,font);
			desc1.SetPosition(350,250);
			rw.Draw(desc1);
		}
		else if(type == 2)
		{
			TextArea desc1(L"Helm - Obrona + " +inventory[selectedItem].getBoost(), 400,font);
			desc1.SetPosition(350,250);
			rw.Draw(desc1);
		}
		else if(type == 3)
		{
			TextArea desc1(L"Mikstura", 460,font);
			desc1.SetPosition(350,250);
			rw.Draw(desc1);
		}

		
	}
}
int Player::InventorySize()const
{
	return inventory.size();
}
void Player::drawAtributes(sf::RenderWindow& rw) const
{
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("Images/tlo.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A•BC∆DE FGHIJKL£MN—O”PRSåTUWYZèØaπbcÊdeÍfghijkl≥mnÒoÛprsútuwyzüøXxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}
	sf::Sprite tloH(tlo);
	rw.Draw(tloH);
	
	std::wstringstream ss;
	if(selectedAttribute == 0)
	{
		ss << L"Exp: " << xp << L"\n";
		ss << L"> Poziom obrony: " << defLevel << L"\n";
		ss << L"Poziom ataku: " << attLevel << L"\n";
	}
	else
	{
		ss << L"Exp: " << xp << L"\n";
		ss << L"Poziom obrony: " << defLevel << L"\n";
		ss << L"> Poziom ataku: " << attLevel << L"\n";
	}
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
	
	if(msgList.size() > 4)
	{
		for(int i=0;i<4;i++)
		{
			msgList[i] = msgList[msgList.size()-4+i];
		}
		msgList.erase(msgList.begin()+4, msgList.end());
	}
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

void Player::getInputInventory(const sf::Event& e, std::list<Creature>& creatures)
{
	if(e.Type == sf::Event::KeyPressed)
	{
		if(e.Key.Code == sf::Key::Up)
		{
			selectedItem--;
			if(selectedItem < 0 )
				selectedItem = inventory.size()-1;
		}
		else if(e.Key.Code == sf::Key::Down)
		{
			selectedItem++;
			if(selectedItem >= inventory.size() )
				selectedItem = 0;
		}
		else if(e.Key.Code == sf::Key::Space)
		{
			if(inventory[selectedItem].getProperty() == Item::WEAPON)
			{
				if(weapon == selectedItem)
					weapon = -1;
				else
					weapon = selectedItem;
			}
			else if(inventory[selectedItem].getProperty() == Item::ARMOR)
			{
				if(armor == selectedItem)
					armor = -1;
				else
					armor = selectedItem;
			}
			else if(inventory[selectedItem].getProperty() == Item::LIFEPOTION)
			{
				health = 1;
				deleteItem(selectedItem);
			}
			else if(inventory[selectedItem].getProperty() == Item::SLEEPDUST)
			{
				for(std::list<Creature>::iterator i = creatures.begin(); i != creatures.end(); i++)
				{
					if(i->isHostile())
						i->setAI(AI::SLEEP);
				}
				deleteItem(selectedItem);
			}
			else if(inventory[selectedItem].getProperty() == Item::MAGICSAND)
			{
				for(std::list<Creature>::iterator i = creatures.begin(); i != creatures.end(); i++)
				{
					if(i->isHostile())
						i->setAI(AI::RANDOM_WALK);
				}
				deleteItem(selectedItem);
			}
		}
	}
}

void Player::getInputAtributes(const sf::Event& e)
{
	if(e.Type == sf::Event::KeyPressed)
	{
		if(e.Key.Code == sf::Key::Up)
		{
			selectedAttribute--;
			if(selectedAttribute < 0 )
				selectedAttribute = 1;
		}
		else if(e.Key.Code == sf::Key::Down)
		{
			selectedAttribute++;
			if(selectedAttribute >= 2 )
				selectedAttribute = 0;
		}
		else if(e.Key.Code == sf::Key::Space)
		{
			if(selectedAttribute == 0) // obrona
			{
				if(xp>0)
				{
					defLevel++;
					xp--;
				}
			}
			else // atak
			{
				if(xp>0)
				{
					attLevel++;
					xp--;
				}
			}
		}
	}
}

void Player::giveItem(const Item& item)
{
	inventory.push_back(item);
	msgList.push_back(std::wstring(L"Zdobywasz: ") + item.getName());
}

void Player::takeItem(const std::wstring& item)
{
	for(std::vector<Item>::const_iterator it = inventory.begin(); it != inventory.end(); it++)
	{
		if(it->getName() == item)
		{
			inventory.erase(it);
			return;
		}
	}
}

void Player::giveMoney(int coins)
{
	this->coins += coins;
	if(coins > 0)
	{
		std::wstringstream ss;
		ss << "Dostajesz " << coins << "$";
		msgList.push_back(ss.str());
	}
}

void Player::takeMoney(int coins)
{
	this->coins -= coins;
}

bool Player::hasItem(const std::wstring& item) const
{
	for(std::vector<Item>::const_iterator it = inventory.begin(); it != inventory.end(); it++)
	{
		if(it->getName() == item)
			return true;
	}
	return false;
}

int Player::hasMoney() const
{
	return coins;
}

float Player::getAttack()
{
	float boost = 0;
	if(weapon != -1)
		boost += inventory[weapon].getPropertyBoost() * 0.1;
	
	return 0.02 * attLevel + boost;
}

float Player::getDefence()
{
	float boost = 0;
	if(armor != -1)
		boost +=  inventory[armor].getPropertyBoost() * 0.1;
	
	return 0.2 * defLevel + boost;
}
void Player::deleteItem(int i)
{
	inventory.erase(inventory.begin() + i);
	if(armor > i)
		armor--;
	if(weapon > i)
		weapon--;
	if(selectedItem >= i && i > 0)
		selectedItem --;
	if(armor == i)
		armor = -1;
	if(weapon == i)
		weapon = -1;
}
const std::vector<Item> &Player::getInventory()const
{
	return inventory;
}

bool Player::isWinner() const
{
	return hasItem(L"Rogalik");
}
#include "Creature.h"
#include "Player.h"
#include "Game.h"

Creature::Creature(const Position pos, int img) : pos(pos), walkDir(0,0), lastDir(0,0),
	walkPower(0), speed(10), fightPower(0), xp(1), att(0.01), def(0.1),
	hitrate(0.1), ai(AI::IDLE), type(Type::DIALOG), health(1), lootMoney(0),
	newPos(pos), cpos(pos), fightState(true)
{
	loot.clear();
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}


void Creature::setSprite(int img)
{
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}

void Creature::draw(sf::RenderWindow& rw, const Position& shift) const
{
	sf::Sprite s(sprite);
	int dx = shift.GetX();
	int dy = shift.GetY();
	s.SetPosition(pos.GetX()*ImageRes::TILESIZE + shift.GetX(), pos.GetY()*ImageRes::TILESIZE + shift.GetY());
	rw.Draw(s);

	if(type == HOSTILE)
	{
		int healthbarw = ImageRes::TILESIZE;
		int healthbarh = 3;
		int healthbarx = pos.GetX()*ImageRes::TILESIZE + shift.GetX();
		int healthbary = pos.GetY()*ImageRes::TILESIZE + shift.GetY();
		int healthbarmid = healthbarw * health;
		sf::Shape healthbarg = sf::Shape::Rectangle(healthbarx, healthbary, healthbarx + healthbarmid, healthbary + healthbarh, sf::Color::Green);
		sf::Shape healthbarr = sf::Shape::Rectangle(healthbarx + healthbarmid, healthbary, healthbarx + healthbarw, healthbary + healthbarh, sf::Color::Red);
		rw.Draw(healthbarr);
		rw.Draw(healthbarg);
	}
}


void Creature::setPosition(const Position& pos)
{
	this->pos = pos;
	newPos = pos;
	cpos = pos;
}

Position Creature::getPosition() const
{
	return pos;
}

bool Creature::isAlive() const
{
	return health > 0;
}

void Creature::move(const Position& dp, const Terrain& terrain)
{
	Tile newtile = terrain.getTile(pos + dp);
	if(newtile.isSolid())
		return;
	else if(newtile.isWarp())
	{
		pos = newtile.getWarp();
	}
	else
	{
		pos = pos + dp;	
	}
}

void Creature::fight(Creature& creature)
{
	if(fightPower >= 0) // mamy doœæ mocy
	{
		float rnd = static_cast<float>(rand()) / RAND_MAX; // 0..1
		creature.health -= rnd * getAttack() / creature.getDefence();
		fightPower -= 1;
		if(! creature.isAlive()) // zabiliœmy dziada
		{
			if(rand() % 5 == 0)
				xp += creature.xp;//dajmy expa
		}
	}
}


void Creature::walk(const Position& dp, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game)
{

	if(lastDir != dp) // gdy zmieniamy kierunek
	{
		walkPower = 0; // zacznij liczyæ od nowa
	}
	lastDir = dp;
	
	if(this == &player) // gdy jestem graczem
	{
		for(std::list<Creature>::iterator i = creatures.begin(); i != creatures.end(); i++)
		{
			if((pos + dp) == i->getPosition())
			{
				if(i->type == Type::DIALOG) // rozmowa
				{
					game.setDialog(i->dialog);
					player.walkDir = Position(0,0);
				}
				else if(i->type == Type::TRADE) // handel
				{
					game.setDialog(i->dialog);
					player.walkDir = Position(0,0);
				}
				else if(i->type == Type::HOSTILE) // atakuj
				{
					//std::cerr << "slash, slash ";
					fight(*i);
				}
				walkPower = 0;
				return;
			}
		}
	}
	else if(type == Type::HOSTILE)
	{
		if((pos + dp) == player.getPosition())
		{
			fight(player);
			walkPower = 0;
			return;
		}
	}

	if(!terrain.tileExist(pos + dp)) // gdy nie ma pozycji docelowej
		return;

	if(type != Type::PLAYER && terrain.getTile(pos + dp).isWarp())
		return; //nie pozwalamy postaciom innym ni¿ gracz przechodziæ miêdzy levelami

	if(dp != Position(0,0)) // gdy mamy ruch
		walkPower += speed;

	int walkTreshold = terrain.getTile(pos + dp).getWalkSpeed();
	if(dp.GetX() != 0 && dp.GetY() != 0) //po przek¹tenej -> sqrt(2)
		walkTreshold *= 1.41;
	if(walkPower > walkTreshold)
	{
		move(dp, terrain);
		walkPower = 0;
	}
}

void Creature::setSpeed(int speed)
{
	this->speed = speed;
}

void Creature::setAttack(float attack)
{
	this->att = attack;
}

void Creature::setDefence(float defence)
{
	this->def = defence;
}

void Creature::setHitrate(int hitrate)
{
	this->hitrate = hitrate;
}

void Creature::setAI(const AI ai)
{
	if(ai == SLEEP)
		this->aiAfterSleep = this->ai;
	this->ai = ai;
}
	
void Creature::step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game)
{
	hitRegen();
	if(ai == AI::IDLE)
	{
		//nic nie rob
	}
	if(ai == AI::SLEEP)
	{
		if(rand()% 500 == 0)
			ai = aiAfterSleep;
	}
	else if(ai == AI::RANDOM_WALK)
	{
		walk(walkDir, terrain, creatures, player, game);
	
		if(newPos == pos || rand() % 30 == 0) // zapobiega blokowanu siê na œcianach
		{
			newPos = Position(rand()%10-5 + cpos.GetX(), rand()%10-5 + cpos.GetY());
		}

		if(pos.GetX() < newPos.GetX())
		{
			walkDir.SetX(1);
		}
		else if(pos.GetX() > newPos.GetX())
		{
			walkDir.SetX(-1);
		}
		else
		{
			walkDir.SetX(0);
		}

		if(pos.GetY() < newPos.GetY())
		{
			walkDir.SetY(1);
		}
		else if(pos.GetY() > newPos.GetY())
		{
			walkDir.SetY(-1);
		}
		else
		{
			walkDir.SetY(0);
		}
	}
	else if(ai == AI::OFFENSIVE_SLOW)
	{
		walk(walkDir, terrain, creatures, player, game);
	
		if(newPos == pos || rand() % 30 == 0) // zapobiega blokowanu siê na œcianach
		{
			newPos = player.pos;
		}

		if(pos.GetX() < newPos.GetX())
		{
			walkDir.SetX(1);
		}
		else if(pos.GetX() > newPos.GetX())
		{
			walkDir.SetX(-1);
		}
		else
		{
			walkDir.SetX(0);
		}

		if(pos.GetY() < newPos.GetY())
		{
			walkDir.SetY(1);
		}
		else if(pos.GetY() > newPos.GetY())
		{
			walkDir.SetY(-1);
		}
		else
		{
			walkDir.SetY(0);
		}
	}
	else if(ai == AI::OFFENSIVE_FAST)
	{
		walk(walkDir, terrain, creatures, player, game);
	
		newPos = player.pos;

		if(pos.GetX() < newPos.GetX())
		{
			walkDir.SetX(1);
		}
		else if(pos.GetX() > newPos.GetX())
		{
			walkDir.SetX(-1);
		}
		else
		{
			walkDir.SetX(0);
		}

		if(pos.GetY() < newPos.GetY())
		{
			walkDir.SetY(1);
		}
		else if(pos.GetY() > newPos.GetY())
		{
			walkDir.SetY(-1);
		}
		else
		{
			walkDir.SetY(0);
		}
	}
	else if(ai == AI::FIGHT_AND_FLEE)
	{

		walk(walkDir, terrain, creatures, player, game);
	
		if(fightState) // fight
		{
			if(Position::distance(pos, player.pos) < 15) //gdy gracz jest blisko
			{
				newPos = player.pos; // w kierunku gracza
				if((pos + walkDir) == player.pos) // gdy ju¿ atakujemy gracza ...
				{
					fightState = (rand() % 5 != 0); //... rozwa¿my zmianê stanu
					cpos = pos; // aktualizacja centrum b³¹dzenia
				}
			}
			else
			{
				newPos = pos; //stój w miejscu
			}
		}
	
		else //flee
		{
			if(newPos == pos || rand() % 30 == 0) //zapobiega blokowanu siê na œcianach
			{
				newPos = Position(rand()%10-5 + cpos.GetX(), rand()%10-5 + cpos.GetY());
				fightState = (rand() % 5 == 0);
			}
		}
		if(pos.GetX() < newPos.GetX())
		{
			walkDir.SetX(1);
		}
		else if(pos.GetX() > newPos.GetX())
		{
			walkDir.SetX(-1);
		}
		else
		{
			walkDir.SetX(0);
		}

		if(pos.GetY() < newPos.GetY())
		{
			walkDir.SetY(1);
		}
		else if(pos.GetY() > newPos.GetY())
		{
			walkDir.SetY(-1);
		}
		else
		{
			walkDir.SetY(0);
		}
	}
	else if(ai == AI::FIGHT)
	{

		walk(walkDir, terrain, creatures, player, game);
	
		if(fightState) // fight
		{
			if(Position::distance(pos, player.pos) < 3) //gdy gracz jest blisko
			{
				newPos = player.pos; // w kierunku gracza
				/*if((pos + walkDir) == player.pos) // gdy ju¿ atakujemy gracza ...
				{
					fightState = (rand() % 5 != 0); //... rozwa¿my zmianê stanu
					cpos = pos; // aktualizacja centrum b³¹dzenia
				}*/
			}
			else
			{
				newPos = pos; //stój w miejscu
			}
		}
		if(pos.GetX() < newPos.GetX())
		{
			walkDir.SetX(1);
		}
		else if(pos.GetX() > newPos.GetX())
		{
			walkDir.SetX(-1);
		}
		else
		{
			walkDir.SetX(0);
		}

		if(pos.GetY() < newPos.GetY())
		{
			walkDir.SetY(1);
		}
		else if(pos.GetY() > newPos.GetY())
		{
			walkDir.SetY(-1);
		}
		else
		{
			walkDir.SetY(0);
		}
	}
	else
	{
		//nic nie rob
	}
}

void Creature::giveLootToPlayer(Player& player)
{
	for(std::list<Item>::iterator i = loot.begin(); i != loot.end(); i++)
	{
		player.giveItem(*i);
	}
	loot.erase(loot.begin(), loot.end());
	player.giveMoney(lootMoney);
}

void Creature::setType(const Type type)
{
	this->type = type;
}

void Creature::addLoot(const Item& item)
{
	loot.push_back(item);
}

void Creature::addLootMoney(int coins)
{
	lootMoney += coins;
}

void Creature::addDialog(const Dialog& dialog)
{
	this->dialog = dialog;
}

void Creature::addTrade(const Trading& trading)
{
	this->trading = trading;
}


float Creature::getAttack()
{
	return att;
}

float Creature::getDefence()
{
	return def;
}

void Creature::hitRegen()
{
	if(fightPower < 0)
	{
		fightPower += hitrate;
	}
}
void Creature::setExp(int xp)
{
	this->xp = xp;
}
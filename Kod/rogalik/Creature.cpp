#include "Creature.h"
#include "Player.h"
#include "Game.h"

Creature::Creature(const Position pos, int img) : pos(pos), walkDir(0,0), lastDir(0,0), walkPower(0), speed(10), ai(AI::IDLE), type(Type::DIALOG), health(1)
{
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
}


void Creature::setPosition(const Position& pos)
{
	this->pos = pos;
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
	creature.health -= 0.1;
	std::cerr << "HP = " << health <<", c.HP= " << creature.health << std::endl;
}


void Creature::walk(const Position& dp, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game)
{

	if(lastDir != dp) // gdy zmieniamy kierunek
	{
		walkPower = 0; // zacznij liczyæ od nowa
	}
	lastDir = dp;

	if(!terrain.tileExist(pos + dp))
		return;

	if(dp != Position(0,0))
		walkPower += speed;

	int walkTreshold = terrain.getTile(pos + dp).getWalkSpeed();
	if(dp.GetX() != 0 && dp.GetY() != 0)
		walkTreshold *= 1.41;
	if(walkPower > walkTreshold)
	{
		bool isDone = false;
		if(!isDone)
		{
			for(std::list<Creature>::iterator i = creatures.begin(); i != creatures.end(); i++)
			{
				if((pos + dp) == i->getPosition())
				{
					walkPower = 0;
					if(this == &player) // gdy jestem graczem
					{
						if(i->type == Type::DIALOG) // rozmowa
						{
							std::cerr << "bla, blabla\n";
							game.setDialog(i->dialog);
							player.walkDir = Position(0,0);
						}
						else if(i->type == Type::HOSTILE) // atakuj
						{
							std::cerr << "slash, slash ";
							fight(*i);
						}
					}
					isDone = true;
					break;
				}
			}
		}
		if(!isDone)
		{
			if((pos + dp) == player.getPosition())
			{
				walkPower = 0;
				if(type == Type::HOSTILE) // gdy jestem wrogiem
				{
					std::cerr << "grrr";
					fight(player);
				}
				isDone = true;
			}
		}
		if(!isDone)
		{
			move(dp, terrain);
			walkPower = 0;
			isDone = true;
		}
	}
}

void Creature::setSpeed(int speed)
{
	this->speed = speed;
}

void Creature::setAI(const AI ai)
{
	this->ai = ai;
}
	
void Creature::step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Player& player, Game& game)
{
	if(ai == AI::IDLE)
	{
		//nic nie rob
	}
	else if(ai == AI::RANDOM_WALK)
	{
		static Position newPos = pos;

		walk(walkDir, terrain, creatures, player, game);
	
		if(newPos == pos)
		{
			newPos = Position(rand()%10+5, rand()%10+5);
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
}

void Creature::setType(const Type type)
{
	this->type = type;
}

void Creature::addLoot(const Item& item)
{
	loot.push_back(item);
}

void Creature::addDialog(const Dialog& dialog)
{
	this->dialog = dialog;
}
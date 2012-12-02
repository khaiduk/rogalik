#include "Creature.h"


Creature::Creature(const Position pos, int img) : pos(pos)
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

void Creature::move(const Position& dp, const Terrain& terrain)
{
	try
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
	catch(...)
	{
		std::cerr << "Nie ma takiego kafelka ";
	}
}
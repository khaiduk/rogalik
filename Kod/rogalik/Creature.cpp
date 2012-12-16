#include "Creature.h"


Creature::Creature(const Position pos, int img) : pos(pos), walkDir(0,0), lastDir(0,0), walkPower(0), speed(10)
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


void Creature::walk(const Position& dp, const Terrain& terrain)
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
		move(dp, terrain);
		walkPower = 0;
	}
}
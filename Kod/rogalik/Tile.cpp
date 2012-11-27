#include "Tile.h"


Tile::Tile(const Position pos, int img) : pos(pos), solid(false), warp(false)
{
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}

void Tile::setImage(int img)
{
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}

void Tile::draw(sf::RenderWindow& rw, int x, int y) const
{
	sf::Sprite s(sprite);
	s.SetPosition(x, y);
	rw.Draw(s);
}

void Tile::setSolid(bool solid)
{
	this->solid = solid;
}

bool Tile::isSolid()
{
	return solid;
}


void Tile::setWarp(const Position& pos)
{
	warp = true;
	warpTo = pos;
}
bool Tile::isWarp()
{
	return warp;
}
Position Tile::getWarp()
{
	return warpTo;
}
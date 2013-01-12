#include "Tile.h"


Tile::Tile(const Position pos, int img) : pos(pos), solid(false), warp(false), walkSpeed(50), imgId(img)
{
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}

void Tile::setImage(int img)
{
	imgId = img;
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
}
Tile & Tile::SetImage(int img)
{
	imgId = img;
	sprite=sf::Sprite(ImageRes::getInstance().getImage(img));
	return *this;
}

void Tile::draw(sf::RenderWindow& rw, int x, int y) const
{
	if(x<0 || y<0 || x > ImageRes::WIDTH || y > ImageRes::HEIGHT )
		return;
	sf::Sprite s(sprite);
	s.SetPosition(x, y);
	rw.Draw(s);
}

void Tile::drawMini(sf::Image& img, int x, int y) const
{
	img.SetPixel(x, y, ImageRes::getInstance().imgColor(imgId));
}

void Tile::setSolid(bool solid)
{
	this->solid = solid;
}
Tile & Tile::SetSolid(bool solid)
{
	this->solid = solid;
	return *this;
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

void Tile::setWalkSpeed(int speed)
{
	walkSpeed = speed;
}
Tile & Tile::SetWalkSpeed(int speed)
{
	walkSpeed = speed;
	return *this;
}
int Tile::getWalkSpeed() const
{
	return walkSpeed;
}
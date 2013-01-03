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

void Tile::draw(sf::RenderWindow& rw, int x, int y) const
{
	if(x<0 || y<0 || x > ImageRes::WIDTH || y > ImageRes::HEIGHT )
		return;
	sf::Sprite s(sprite);
	s.SetPosition(x, y);
	rw.Draw(s);
}

void Tile::drawMini(sf::RenderWindow& rw, int x, int y) const
{
	sf::Shape rect = sf::Shape::Rectangle(x, y, x+1, y+1, ImageRes::getInstance().imgColor(imgId));
	rw.Draw(rect);
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

void Tile::setWalkSpeed(int speed)
{
	walkSpeed = speed;
}

int Tile::getWalkSpeed() const
{
	return walkSpeed;
}
#include "Tile.h"


Tile::Tile(const Position pos, int img) : pos(pos)
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
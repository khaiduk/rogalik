#include "Terrain.h"


Terrain::Terrain(void)
{
	map.reserve(1);
	map.insert(map.begin() + 0, newLevel(50, 50, 0));
	
	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(2);
		}
	}
	
	for(int x=10;x<15;x++)
	{
		for(int y=7;y<10;y++)
		{
			map[0][x][y].setImage(4);
		}
	}
	for(int x=10;x<15;x++)
	{
		for(int y=10;y<13;y++)
		{
			map[0][x][y].setImage(3);
		}
	}
}


Terrain::~Terrain(void)
{
}

void Terrain::draw(sf::RenderWindow& rw, Position pos) const
{
	int level = pos.GetZ();
	int dx = pos.GetX();
	int dy = pos.GetY();
	for(int x=0;x<map[level].size();x++)
	{
		for(int y=0;y<map[level][x].size();y++)
		{
			map[level][x][y].draw(rw, (x-dx)*ImageRes::TILESIZE, (y-dy)*ImageRes::TILESIZE);
		}
	}
}


std::vector< std::vector<Tile> > Terrain::newLevel(int width, int height, int level)
{
	std::vector< std::vector<Tile> > newLevel;
	newLevel.resize(width);
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
			newLevel[x].push_back(Tile(Position(x, y, level)));
	}
	return newLevel;
}
#include "Terrain.h"


Terrain::Terrain(void)
{
}

Terrain::~Terrain(void)
{
}


Position Terrain::calculateShift(const Position& playerPos) const
{
	int shiftx = -playerPos.GetX() + (ImageRes::WIDTH/ImageRes::TILESIZE)/2;
	int shifty = -playerPos.GetY() + (ImageRes::HEIGHT/ImageRes::TILESIZE)/2 - 3;

	// odkomentowac dla braku czarnego t³a poza map¹
	/*
	if(shiftx > 0) shiftx = 0;
	if(shifty > 0) shifty = 0;
	if(shiftx < ImageRes::WIDTH/ImageRes::TILESIZE - static_cast<int>(map[playerPos.GetZ()].size()) ) shiftx = ImageRes::WIDTH/ImageRes::TILESIZE - static_cast<int>(map[playerPos.GetZ()].size());
	if(shifty < ImageRes::HEIGHT/ImageRes::TILESIZE - static_cast<int>(map[playerPos.GetZ()][0].size()) ) shifty = ImageRes::HEIGHT/ImageRes::TILESIZE - static_cast<int>(map[playerPos.GetZ()][0].size());
	//*/
	return Position(shiftx*ImageRes::TILESIZE, shifty*ImageRes::TILESIZE);
}

void Terrain::draw(sf::RenderWindow& rw, int level, const Position& shift) const
{
	int dx = shift.GetX();
	int dy = shift.GetY();
	for(int x=0;x<map[level].size();x++)
	{
		for(int y=0;y<map[level][x].size();y++)
		{
			map[level][x][y].draw(rw, x*ImageRes::TILESIZE + dx, y*ImageRes::TILESIZE + dy);
		}
	}
}

void Terrain::drawMinimap(sf::RenderWindow& rw, int level) const
{
	for(int x=0;x<map[level].size();x++)
	{
		for(int y=0;y<map[level][x].size();y++)
		{
			map[level][x][y].drawMini(rw, x+3, y+3);
		}
	}
}
	
Tile Terrain::getTile(const Position& pos) const
{
	try
	{
		return map.at(pos.GetZ()).at(pos.GetX()).at(pos.GetY());
	}
	catch (std::out_of_range& oor)
	{
		std::string wyjatek = "no such tile";
		throw wyjatek;
	}
}

bool Terrain::tileExist(const Position& pos) const
{
	return  (pos.GetZ() >=0 && pos.GetZ() < map.size()) &&
			(pos.GetX() >=0 && pos.GetX() < map.at(pos.GetZ()).size()) &&
			(pos.GetY() >=0 && pos.GetY() < map.at(pos.GetZ()).at(pos.GetX()).size());
}
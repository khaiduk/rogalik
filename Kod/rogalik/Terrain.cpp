#include "Terrain.h"


Terrain::Terrain(void)
{
	map.reserve(2);// rezerwacja ilosci poziomow

	// Trawka
	map.insert(map.begin() + 0, newLevel(20, 20, 0)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20
	
	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	
	for(int x=10;x<15;x++)
	{
		for(int y=7;y<10;y++)
		{
			map[0][x][y].setImage(ImageRes::WOOD);
			map[0][x][y].setSolid(true); // nie pozwala przejsc przez kafelek o numerze np.4
		}
	}
	for(int x=10;x<15;x++)
	{
		for(int y=10;y<13;y++)
		{
			map[0][x][y].setImage(ImageRes::BRICK);
			map[0][x][y].setSolid(true);
		}
	}
	
	map[0][13][12].setSolid(false);
	map[0][13][12].setImage(ImageRes::EMPTY);
	map[0][13][12].setWarp(Position(0,0,1));

	//Domek
	map.insert(map.begin() + 1, newLevel(50, 30, 1));
	for(int x=0;x<map[1].size();x++)
	{
		for(int y=0;y<map[1][x].size();y++)
		{
			map[1][x][y].setImage(ImageRes::WOOD);
		}
	}
	map[1][1][1].setWarp(Position(13,12,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[1][1][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
}


Terrain::~Terrain(void)
{
}


Position Terrain::calculateShift(const Position& p) const
{
	return p;
}

void Terrain::draw(sf::RenderWindow& rw, const Position& pos) const
{
	int level = pos.GetZ();
	int dx = pos.GetX() - 12;
	int dy = pos.GetY() - 10;
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
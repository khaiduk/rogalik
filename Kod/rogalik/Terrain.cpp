#include "Terrain.h"


Terrain::Terrain(void)
{
	map.reserve(15);// rezerwacja ilosci poziomow
	//*
	//level 1
	map.insert(map.begin() + 0, newLevel(30, 20, 0)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(ImageRes::SAND); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	int x=0;
	srand(time(NULL));
	int y=rand()%17+1;
	map[0][x][y].setImage(ImageRes::ROAD);
	map[0][x][y-1].setImage(ImageRes::ROAD);
	map[0][x][y+1].setImage(ImageRes::ROAD);

	for(int x=0;x<30;x++)
	{

		y+=(rand()%3-1);
		if(y<1)
		{
			y+=(rand()%3+1);
			map[0][x][y].setImage(ImageRes::ROAD);
			map[0][x][y+1].setImage(ImageRes::ROAD);
		}
		if(y>18)
		{
			y+=(rand()%3-1);
			map[0][x][y].setImage(ImageRes::ROAD);
			map[0][x][y-1].setImage(ImageRes::ROAD);
		}
		else
			{map[0][x][y-1].setImage(ImageRes::ROAD);
			map[0][x][y].setImage(ImageRes::ROAD);
			map[0][x][y+1].setImage(ImageRes::ROAD);}
		
		if(x==29)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,8,5));
			}
			
	}
	
	/*/
	// LEVEL 1
	// wioska
	map.insert(map.begin() + 0, newLevel(30, 20, 0)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(ImageRes::SAND); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	//droga
	for(int x=0;x<=8;x++)
		map[0][x][5].setImage(ImageRes::ROAD);
	for(int y=6;y<=13;y++)
		map[0][8][y].setImage(ImageRes::ROAD);
	for(int x=9;x<=17;x++)
		map[0][x][13].setImage(ImageRes::ROAD);
	for(int y=7;y<14;y++)
		map[0][17][y].setImage(ImageRes::ROAD);
	for(int x=18;x<=25;x++)
		map[0][x][7].setImage(ImageRes::ROAD);
	for(int y=8; y<=10;y++)
		map[0][25][y].setImage(ImageRes::ROAD);
	for(int x=26;x<30;x++)
		map[0][x][10].setImage(ImageRes::ROAD);

	map[0][29][10].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[0][29][10].setWarp(Position(0,8,5)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]

	//chata cinkciarza
	for(int x=4;x<=7;x++)
	{
		for(int y=2; y<=4;y++)
		{
			map[0][x][y].setImage(ImageRes::BRICK);
			map[0][x][y].setSolid(true);
		}
	}
	map[0][6][4].setSolid(false);
	map[0][6][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[0][6][4].setWarp(Position(0,1,1)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]

	//wnetrze chaty cinkciarza
	map.insert(map.begin() + 1, newLevel(10, 8, 1));
	for(int x=0;x<map[1].size();x++)
	{
		for(int y=0;y<map[1][x].size();y++)
		{
			map[1][x][y].setImage(ImageRes::WOOD);
		}
	}

		for(int y=3;y<6;y++)
		{
			map[1][6][y].setImage(ImageRes::DESK);
			map[1][6][y].setSolid(true);
		}

	for(int x=4;x<10;x++)
	{
			map[1][x][0].setImage(ImageRes::FURNITURE);
			map[1][x][0].setSolid(true);
	}

	for(int x=2;x<7;x++)
	{
			map[1][x][7].setImage(ImageRes::FURNITURE);
			map[1][x][7].setSolid(true);
	}

		for(int y=3;y<8;y++)
		{
			map[1][9][y].setImage(ImageRes::FURNITURE);
			map[1][9][y].setSolid(true);
		}

	map[1][0][1].setWarp(Position(6,4,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[1][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0


	//chata rzemieslnika
	for(int x=12;x<=15;x++)
	{
		for(int y=14; y<=16;y++)
		{
			map[0][x][y].setImage(ImageRes::WOOD);
			map[0][x][y].setSolid(true);
		}
	}
	map[0][14][14].setSolid(false);
	map[0][14][14].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[0][14][14].setWarp(Position(0,1,2));

	//wnetrze chaty cinkciarza
	map.insert(map.begin() + 2, newLevel(10, 8, 2));
	for(int x=0;x<map[2].size();x++)
	{
		for(int y=0;y<map[2][x].size();y++)
		{
			map[2][x][y].setImage(ImageRes::WALL);
		}
	}

	for(int x=3;x<7;x++)
	{
			map[2][x][3].setImage(ImageRes::DESK);
			map[2][x][3].setSolid(true);
	}

		for(int y=3;y<7;y++)
		{
			map[2][3][y].setImage(ImageRes::DESK);
			map[2][3][y].setSolid(true);
		}

		for(int y=3;y<7;y++)
		{
			map[2][7][y].setImage(ImageRes::DESK);
			map[2][7][y].setSolid(true);
		}

	map[2][0][1].setWarp(Position(14,14,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[2][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata kowala
	for(int x=14;x<=16;x++)
	{
		for(int y=8; y<=10;y++)
		{
			map[0][x][y].setImage(ImageRes::WOOD);
			map[0][x][y].setSolid(true);
		}
	}
	map[0][16][9].setSolid(false);
	map[0][16][9].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[0][16][9].setWarp(Position(0,1,3));
	//wnetrze chaty kowala
	map.insert(map.begin() + 3, newLevel(10, 8, 3));
	for(int x=0;x<map[3].size();x++)
	{
		for(int y=0;y<map[3][x].size();y++)
		{
			map[3][x][y].setImage(ImageRes::DARK_WALL);
		}
	}

	for(int x=3;x<6;x++)
	{
		for(int y=5;y<7;y++)
		{
			map[3][x][y].setImage(ImageRes::DESK);
			map[3][x][y].setSolid(true);
		}
	}

	for(int x = 4; x<=8; x++)
	{
		for(int y=0; y<2;y++)
		{
			map[3][x][y].setImage(ImageRes::FURNITURE);
			map[3][x][y].setSolid(true);
		}
	}
	map[3][0][1].setWarp(Position(16,9,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[3][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata mêdrca
	for(int x=21;x<=24;x++)
	{
		for(int y=4; y<7;y++)
		{
			map[0][x][y].setImage(ImageRes::WOOD);
			map[0][x][y].setSolid(true);
		}
	}
	map[0][23][6].setSolid(false);
	map[0][23][6].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[0][23][6].setWarp(Position(0,1,4));
	
	//wnetrze chaty medrca
	map.insert(map.begin() + 4, newLevel(10, 8, 4));
	for(int x=0;x<map[4].size();x++)
	{
		for(int y=0;y<map[4][x].size();y++)
		{
			map[4][x][y].setImage(ImageRes::STAR);
		}
	}

	map[4][0][1].setWarp(Position(23,6,0));
	map[4][0][1].setImage(ImageRes::EMPTY);
	

	//LEVEL 2
	//las
	map.insert(map.begin() + 5, newLevel(25, 20, 5)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[5].size();x++)
	{
		for(int y=0;y<map[5][x].size();y++)
		{
			map[5][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	//droga
	for(int x=0;x<=10;x++)
		map[5][x][8].setImage(ImageRes::ROAD2);
	for(int y=4;y<=7;y++)
		map[5][10][y].setImage(ImageRes::ROAD2);
	for(int x=11;x<=15;x++)
		map[5][x][4].setImage(ImageRes::ROAD2);
	for(int y=5;y<13;y++)
		map[5][15][y].setImage(ImageRes::ROAD2);
	for(int x=9;x<=15;x++)
		map[5][x][13].setImage(ImageRes::ROAD2);
	for(int y=13; y<=17;y++)
		map[5][9][y].setImage(ImageRes::ROAD2);
	for(int x=10;x<18;x++)
		map[5][x][17].setImage(ImageRes::ROAD2);
	for(int y=7;y<=17;y++)
		map[5][18][y].setImage(ImageRes::ROAD2);
	for(int x=18;x<20;x++)
		map[5][x][7].setImage(ImageRes::ROAD2);
	for(int y=5;y<=9;y++)
		map[5][20][y].setImage(ImageRes::ROAD2);
	for(int x=21;x<24;x++)
		map[5][x][5].setImage(ImageRes::ROAD2);
	for(int x=21;x<24;x++)
		map[5][x][9].setImage(ImageRes::ROAD2);

	map[5][24][5].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[5][24][5].setWarp(Position(0,5,6)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]

	map[5][24][9].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[5][24][9].setWarp(Position(0,3,7)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]

	map[5][5][15].setImage(ImageRes::TREE);
	map[5][3][12].setImage(ImageRes::TREE);
	map[5][7][14].setImage(ImageRes::TREE);
	map[5][6][12].setImage(ImageRes::TREE);

	//wybor drogi 1 (6)
	map.insert(map.begin() + 6, newLevel(15, 10, 6)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[6].size();x++)
	{
		for(int y=0;y<map[6][x].size();y++)
		{
			map[6][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	
	//droga
	for(int x=0;x<7;x++)
		map[6][x][5].setImage(ImageRes::ROAD2);
	for(int y=2;y<=5;y++)
		map[6][7][y].setImage(ImageRes::ROAD2);
	for(int x=8;x<=11;x++)
		map[6][x][2].setImage(ImageRes::ROAD2);
	for(int y=2;y<=4;y++)
		map[6][11][y].setImage(ImageRes::ROAD2);
	for(int x=12;x<=14;x++)
		map[6][x][4].setImage(ImageRes::ROAD2);

	map[6][14][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[6][14][4].setWarp(Position(0,1,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	//wybor drogi 2 (7)
	map.insert(map.begin() + 7, newLevel(15, 10, 7)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[7].size();x++)
	{
		for(int y=0;y<map[7][x].size();y++)
		{
			map[7][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	for(int x=0;x<5;x++)
		map[7][x][3].setImage(ImageRes::ROAD2);
	for(int y=3;y<=6;y++)
		map[7][5][y].setImage(ImageRes::ROAD2);
	for(int x=6;x<=9;x++)
		map[7][x][6].setImage(ImageRes::ROAD2);
	for(int y=2;y<=5;y++)
		map[7][9][y].setImage(ImageRes::ROAD2);
	for(int x=9;x<=11;x++)
		map[7][x][2].setImage(ImageRes::ROAD2);
	for(int y=2;y<=4;y++)
		map[7][11][y].setImage(ImageRes::ROAD2);
	for(int x=12;x<=14;x++)
		map[7][x][4].setImage(ImageRes::ROAD2);

	map[7][14][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[7][14][4].setWarp(Position(0,1,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	
	//LEVEL 3
	//wioska
	map.insert(map.begin() + 8, newLevel(30, 20, 8)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[8].size();x++)
	{
		for(int y=0;y<map[8][x].size();y++)
		{
			map[8][x][y].setImage(ImageRes::STONE); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[8][10][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[8][10][4].setWarp(Position(0,1,12)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	
	//chata rzemieœlnika
	map[8][14][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[8][14][4].setWarp(Position(0,1,9)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	
	//wnetrze chaty rzemieslnika
	map.insert(map.begin() + 9, newLevel(30, 20, 9)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[9].size();x++)
	{
		for(int y=0;y<map[9][x].size();y++)
		{
			map[9][x][y].setImage(ImageRes::WOOD); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[9][14][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[9][14][4].setWarp(Position(0,1,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	
	//chata medrca
	map[8][14][10].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[8][14][10].setWarp(Position(0,1,10)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	//wnetrze chaty mêdrca
	map.insert(map.begin() + 10, newLevel(30, 20, 10)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[10].size();x++)
	{
		for(int y=0;y<map[10][x].size();y++)
		{
			map[10][x][y].setImage(ImageRes::WOOD); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[10][14][10].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[10][14][10].setWarp(Position(0,1,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	
	//bar
	map[8][12][6].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[8][12][6].setWarp(Position(0,1,11)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	//bar
	map.insert(map.begin() + 11, newLevel(30, 20, 11)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[11].size();x++)
	{
		for(int y=0;y<map[11][x].size();y++)
		{
			map[11][x][y].setImage(ImageRes::DARK_WALL); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[11][12][6].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[11][12][6].setWarp(Position(0,1,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	//LEVEL 4
	//góry
	map.insert(map.begin() + 12, newLevel(30, 20, 12)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[12].size();x++)
	{
		for(int y=0;y<map[12][x].size();y++)
		{
			map[12][x][y].setImage(ImageRes::GORY); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[12][2][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[12][2][4].setWarp(Position(0,1,14)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	//chata
	map[12][7][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[12][7][4].setWarp(Position(0,1,13)); 
	
	//wnetrze chaty
	map.insert(map.begin() + 13, newLevel(30, 20, 13)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[13].size();x++)
	{
		for(int y=0;y<map[13][x].size();y++)
		{
			map[13][x][y].setImage(ImageRes::WOOD); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	map[13][7][4].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[13][7][4].setWarp(Position(0,1,12)); 
	
	//LEVEL 5 - ostatni!
	map.insert(map.begin() + 14, newLevel(30, 20, 14)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[14].size();x++)
	{
		for(int y=0;y<map[14][x].size();y++)
		{
			map[14][x][y].setImage(ImageRes::WALL); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}//*/
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
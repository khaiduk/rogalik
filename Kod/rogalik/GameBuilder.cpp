#include "GameBuilder.h"


Game& GameBuilder::getGame()
{
	return game; 
}

std::vector< std::vector<Tile> > GameBuilder::emptyTerrainLevel(int width, int height, int level)
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

void GameBuilder::generateNewGame()
{
	game = Game(); // nowa pusta gra
	std::vector< std::vector< std::vector<Tile> > > &map = game.terrain.map;
	
	map.reserve(20);// rezerwacja ilosci poziomow
	
	//level 1
	//wioska
	map.insert(map.begin() + 0, emptyTerrainLevel(100, 30, 0)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(ImageRes::SAND); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	int powrot_x1;
	int powrot_y1;
	int yp=10+(rand()%3);
	//droga
	//int x=0;
	srand(time(NULL));
	int y=rand()%27+1;
	//int y = y1;
	game.player = Player( Position(0, y) );
	map[0][0][y].setImage(ImageRes::ROAD);
	map[0][0][y-1].setImage(ImageRes::ROAD);
	map[0][0][y+1].setImage(ImageRes::ROAD);
	
	for(int x=1;x<100;x++)
	{
		//y=y1;
		y+=(rand()%3-1);
		
		if(y<1)
		{
			x--;
			continue;
		}

		if(y>28)
		{	
			x--;
			continue;
		}

		else
			{
				map[0][x][y-1].setImage(ImageRes::ROAD);
				map[0][x][y].setImage(ImageRes::ROAD);
				map[0][x][y+1].setImage(ImageRes::ROAD);
			}
		
		if(x==99)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,yp,5));
				powrot_x1=x;
				powrot_y1=y;
			}
			
	}
	//chata cinkciarza
	int i=rand()%95+1;
	int j=rand()%15+1;
	for(int x=i;x<=i+3;x++)
	{
		for(int y=j; y<=j+2;y++)
		{
			if(x==i && y==j+1)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,1,1));
			}
			else
				{
					map[0][x][y].setImage(ImageRes::BRICK);
					map[0][x][y].setSolid(true);
				}
		}

	}
	
	//wnetrze chaty cinkciarza
	map.insert(map.begin() + 1, emptyTerrainLevel(10, 8, 1));
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

	map[1][0][1].setWarp(Position(i,j+1,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[1][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata rzemieslnika
	int r=rand()%95+1;
	int z=rand()%15+1;
	for(int x=r;x<=r+3;x++)
	{
		for(int y=z; y<=z+2;y++)
		{
			if(x==r+1 && y==z+2)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,1,2));
			}
			else
				{
					map[0][x][y].setImage(ImageRes::WOOD);
					map[0][x][y].setSolid(true);
				}
		}

	}
	
	//wnetrze chaty rzemieslnika
	map.insert(map.begin() + 2, emptyTerrainLevel(10, 8, 2));
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
		
		map[2][0][1].setWarp(Position(r+1,z+2,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
		map[2][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata kowala
	int k=rand()%95+1;
	int w=rand()%15+1;
	for(int x=k;x<=k+3;x++)
	{
		for(int y=w; y<=w+2;y++)
		{
			if(x==k+2 && y==w)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,1,3));
			}
			else
				{
					map[0][x][y].setImage(ImageRes::WOOD);
					map[0][x][y].setSolid(true);
				}
		}

	}
	//wnetrze chaty kowala
	map.insert(map.begin() + 3, emptyTerrainLevel(10, 8, 3));
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
	map[3][0][1].setWarp(Position(k+2,w,0)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[3][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata mêdrca
	int m=rand()%95+1;
	int d=rand()%15+1;
	for(int x=m;x<=m+3;x++)
	{
		for(int y=d; y<=d+2;y++)
		{
			if(x==m+3 && y==d)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,1,4));
			}
			else
				{
					map[0][x][y].setImage(ImageRes::WOOD);
					map[0][x][y].setSolid(true);
				}
		}

	}	
	//wnetrze chaty medrca
	map.insert(map.begin() + 4, emptyTerrainLevel(10, 8, 4));
	for(int x=0;x<map[4].size();x++)
	{
		for(int y=0;y<map[4][x].size();y++)
		{
			map[4][x][y].setImage(ImageRes::STAR);
		}
	}

	map[4][0][1].setWarp(Position(m+3,d,0));
	map[4][0][1].setImage(ImageRes::EMPTY);
	
	//LEVEL 2
	//las
	map.insert(map.begin() + 5, emptyTerrainLevel(100, 20, 5)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[5].size();x++)
	{
		for(int y=0;y<map[5][x].size();y++)
		{
			map[5][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}
	
	for(int x=0;x<70;x++)
	{
		int y=10+(rand()%3);

		if(x==0)
		{
			//game.player = Player( Position(x, y, 5) );
			int y=yp;
			//map[5][x][y].setImage(ImageRes::ROAD2);
			map[5][x][y-1].setImage(ImageRes::ROAD2);
			map[5][x][y+1].setImage(ImageRes::ROAD2);
			map[5][x][y].setWarp(Position(powrot_x1,powrot_y1,0));
			map[5][x][y].setImage(ImageRes::EMPTY);
		}
		if(x==69)
		{
			for(int y=5;y<15;y++)
			{
				map[5][x][y].setImage(ImageRes::ROAD2);
				map[5][x+1][y].setImage(ImageRes::ROAD2);
				map[5][x+2][y].setImage(ImageRes::ROAD2);
			}
		}
		else
		{
			map[5][x][y].setImage(ImageRes::ROAD2);
			map[5][x][y-1].setImage(ImageRes::ROAD2);
			map[5][x][y+1].setImage(ImageRes::ROAD2);
		}
	}
	int powrot_x2;
	int powrot_y2;
	for(int x=72;x<100;x++)
	{
		int y= 6+(rand()%3);
		map[5][x][y].setImage(ImageRes::ROAD2);
		map[5][x][y-1].setImage(ImageRes::ROAD2);
		map[5][x][y+1].setImage(ImageRes::ROAD2);

		int yy = 13+(rand()%3);
		map[5][x][yy].setImage(ImageRes::ROAD2);
		map[5][x][yy-1].setImage(ImageRes::ROAD2);
		map[5][x][yy+1].setImage(ImageRes::ROAD2);

		if(x==99)
		{
			map[5][x][y].setImage(ImageRes::EMPTY);
			map[5][x][y].setWarp(Position(0, 8, 6));
			powrot_x1=x;
			powrot_y1=y;
			map[5][x][yy].setImage(ImageRes::EMPTY);
			map[5][x][yy].setWarp(Position(0, 8, 7));
			powrot_x2=x;
			powrot_y2=yy;
		}
	}
	srand(time(NULL));
	for(int i=0; i<200; ++i)
	{
		
		int x=rand()%98;
		//srand(time(NULL));
		int y=rand()%19;
		map[5][x][y].setImage(ImageRes::TREE);
		map[5][x][y].setSolid(true);
	}
	

	//wybor drogi 1 (6)
	map.insert(map.begin() + 6, emptyTerrainLevel(40, 14, 6)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[6].size();x++)
	{
		for(int y=0;y<map[6][x].size();y++)
		{
			map[6][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	for(int x=0;x<40;x++)
	{
		int y=7+(rand()%3);
		map[6][x][y].setImage(ImageRes::ROAD2);
		map[6][x][y-1].setImage(ImageRes::ROAD2);
		map[6][x][y+1].setImage(ImageRes::ROAD2);

		if(x==0)
		{
			map[6][x][y].setWarp(Position(powrot_x1,powrot_y1,5));
			map[6][x][y].setImage(ImageRes::EMPTY);
		}
		if(x==39)
		{
			map[6][x][y].setImage(ImageRes::EMPTY);
			map[6][x][y].setWarp(Position(0, 10, 8));
			powrot_x1=x;
			powrot_y1=y;
		}
	}
	srand(time(NULL));
	for(int i=0; i<100; ++i)
	{
		
		int x=rand()%38;
		int y=rand()%10;
		map[6][x][y].setImage(ImageRes::TREE);
		map[6][x][y].setSolid(true);
	}
	//wybor drogi 2 (7)
	map.insert(map.begin() + 7, emptyTerrainLevel(40, 14, 7)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[7].size();x++)
	{
		for(int y=0;y<map[7][x].size();y++)
		{
			map[7][x][y].setImage(ImageRes::GRASS); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	srand(time(NULL));
	for(int x=0;x<40;x++)
	{
		int y=7+(rand()%3);
		map[7][x][y].setImage(ImageRes::ROAD2);
		map[7][x][y-1].setImage(ImageRes::ROAD2);
		map[7][x][y+1].setImage(ImageRes::ROAD2);

		if(x==0)
		{
			map[7][x][y].setWarp(Position(powrot_x2,powrot_y2,5));
			map[7][x][y].setImage(ImageRes::EMPTY);
		}
		if(x==39)
		{
			map[7][x][y].setImage(ImageRes::EMPTY);
			map[7][x][y].setWarp(Position(0, 10, 8));
			powrot_x2=x;
			powrot_y2=y;
		}
	}
	for(int i=0; i<100; ++i)
	{
		
		int x=rand()%38;
		int y=rand()%10;
		map[7][x][y].setImage(ImageRes::TREE);
		map[7][x][y].setSolid(true);
	}
	
	//LEVEL 3
	//wioska
	map.insert(map.begin() + 8, emptyTerrainLevel(100, 30, 8)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20

	for(int x=0;x<map[8].size();x++)
	{
		for(int y=0;y<map[8][x].size();y++)
		{
			map[8][x][y].setImage(ImageRes::STONE); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	int x=0;
	int yp2=rand()%17+1;
	srand(time(NULL));
	y=rand()%27+1;

	map[8][x][y].setImage(ImageRes::EMPTY);
	map[8][x][y].setWarp(Position(powrot_x1,powrot_y1,6));
	map[8][x][y].setImage(ImageRes::EMPTY);
	map[8][x][y].setWarp(Position(powrot_x2,powrot_y2,7));


	map[8][x][y].setImage(ImageRes::ROAD);
	map[8][x][y-1].setImage(ImageRes::ROAD);
	map[8][x][y+1].setImage(ImageRes::ROAD);
	
	int powrot_x3;
	int powrot_y3;
	for(int x=1;x<100;x++)
	{
		y+=(rand()%3-1);
		
		if(y<1)
		{
			x--;
			continue;
		}
		
		else if(y>28)
		{
			x--;
			continue;
		}
		
		else
			{map[8][x][y-1].setImage(ImageRes::ROAD);
			map[8][x][y].setImage(ImageRes::ROAD);
			map[8][x][y+1].setImage(ImageRes::ROAD);}
		
		if(x==99)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,yp2,12));
				powrot_x3=x;
				powrot_y3=y;
			}
			
	}
	//chata rzemieslnika
	/*int r*/r=rand()%95+1;
	/*int z*/z=rand()%25+1;
	for(int x=r;x<=r+3;x++)
	{
		for(int y=z; y<=z+2;y++)
		{
			if(x==r+1 && y==z+2)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,1,9));
			}
			else
				{
					map[8][x][y].setImage(ImageRes::WOOD);
					map[8][x][y].setSolid(true);
				}
		}
	}
	
	//wnetrze chaty rzemieslnika
	map.insert(map.begin() + 9, emptyTerrainLevel(10, 8, 9));
	for(int x=0;x<map[9].size();x++)
	{
		for(int y=0;y<map[9][x].size();y++)
		{
			map[9][x][y].setImage(ImageRes::WALL);
		}
	}

	for(int x=3;x<7;x++)
	{
			map[9][x][3].setImage(ImageRes::DESK);
			map[9][x][3].setSolid(true);
	}

		for(int y=3;y<7;y++)
		{
			map[9][3][y].setImage(ImageRes::DESK);
			map[9][3][y].setSolid(true);
		}

		for(int y=3;y<7;y++)
		{
			map[9][7][y].setImage(ImageRes::DESK);
			map[9][7][y].setSolid(true);
		}
		
		map[9][0][1].setWarp(Position(r+1,z+2,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
		map[9][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata mêdrca
	/*int m*/m=rand()%95+1;
	/*int d*/d=rand()%25+1;
	for(int x=m;x<=m+3;x++)
	{
		for(int y=d; y<=d+2;y++)
		{
			if(x==m+3 && y==d)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,1,10));
			}
			else
				{
					map[8][x][y].setImage(ImageRes::WOOD);
					map[8][x][y].setSolid(true);
				}
		}

	}
	//wnetrze chaty medrca
	map.insert(map.begin() + 10, emptyTerrainLevel(10, 8, 10));
	for(int x=0;x<map[10].size();x++)
	{
		for(int y=0;y<map[10][x].size();y++)
		{
			map[10][x][y].setImage(ImageRes::STAR);
		}
	}

	map[10][0][1].setWarp(Position(m+3,d,8));
	map[10][0][1].setImage(ImageRes::EMPTY);
	
	//Bar
	int b=rand()%95+1;
	int a=rand()%25+1;
	for(int x=b;x<=b+3;x++)
	{
		for(int y=a; y<=a+2;y++)
		{
			if(x==b+2 && y==a)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,1,11));
			}
			else
				{
					map[8][x][y].setImage(ImageRes::WOOD);
					map[8][x][y].setSolid(true);
				}
		}

	}
	//wnetrze baru
	map.insert(map.begin() + 11, emptyTerrainLevel(10, 8, 11));
	for(int x=0;x<map[11].size();x++)
	{
		for(int y=0;y<map[11][x].size();y++)
		{
			map[11][x][y].setImage(ImageRes::WOOD);
		}
	}

	for(int x=2;x<5;x++)
	{
		map[11][x][4].setImage(ImageRes::DESK);
		map[11][x][4].setSolid(true);

		map[11][x][2].setImage(ImageRes::DESK);
		map[11][x][2].setSolid(true);

		map[11][x][6].setImage(ImageRes::DESK);
		map[11][x][6].setSolid(true);
	}
	for(y=3;y<6;y++)
	{
		map[11][7][y].setImage(ImageRes::DESK);
		map[11][7][y].setSolid(true);
	}
	for(int x = 4; x<=8; x++)
	{
		map[11][x][0].setImage(ImageRes::FURNITURE);
		map[11][x][0].setSolid(true);

		map[11][x][7].setImage(ImageRes::FURNITURE);
		map[11][x][7].setSolid(true);
	}
	map[11][0][1].setWarp(Position(b+2,a,8)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[11][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//LEVEL 4
	//gory
	map.insert(map.begin() + 12, emptyTerrainLevel(100, 20, 12));
	for(int x=0;x<map[12].size();x++)
	{
		for(int y=0;y<map[12][x].size();y++)
		{
			map[12][x][y].setImage(ImageRes::GORY);
		}
	}

	int powrot_x4;
	int powrot_y4;
	x=0;
	int yp3=rand()%17+1;
	srand(time(NULL));
	y=yp2;
	
	map[12][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[12][x][y].setWarp(Position(powrot_x3,powrot_y3,8));
	map[12][x][y-1].setImage(ImageRes::ROAD);
	map[12][x][y+1].setImage(ImageRes::ROAD);
	
	for(int x=1;x<100;x++)
	{		
		y+=(rand()%3-1);
		if(y<1)
		{
			x--;
			continue;
		}
		else if(y>18)
		{
			x--;
			continue;
		}
		else
			{map[12][x][y-1].setImage(ImageRes::ROAD);
			map[12][x][y].setImage(ImageRes::ROAD);
			map[12][x][y+1].setImage(ImageRes::ROAD);}
		
		if(x==99)
			{
				map[12][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[12][x][y].setWarp(Position(0,yp3,8));
				powrot_x4=x;
				powrot_y4=y;
			}	
	}
	
	//chata
	i=rand()%95+1;
	j=rand()%15+1;
	for(int x=i;x<=i+3;x++)
	{
		for(int y=j; y<=j+2;y++)
		{
			if(x==i && y==j+1)
			{
				map[12][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[12][x][y].setWarp(Position(0,1,13));
			}
			else
				{
					map[12][x][y].setImage(ImageRes::BRICK);
					map[12][x][y].setSolid(true);
				}
		}

	}
	
	//wnetrze chaty
	map.insert(map.begin() + 13, emptyTerrainLevel(10, 8, 13));
	for(int x=0;x<map[13].size();x++)
	{
		for(int y=0;y<map[13][x].size();y++)
		{
			map[13][x][y].setImage(ImageRes::WOOD);
		}
	}

		for(int y=3;y<6;y++)
		{
			map[13][6][y].setImage(ImageRes::DESK);
			map[13][6][y].setSolid(true);
		}

	for(int x=4;x<10;x++)
	{
			map[13][x][0].setImage(ImageRes::FURNITURE);
			map[13][x][0].setSolid(true);
	}
	
	for(int x=2;x<7;x++)
	{
			map[13][x][7].setImage(ImageRes::FURNITURE);
			map[13][x][7].setSolid(true);
	}

		for(int y=3;y<8;y++)
		{
			map[13][9][y].setImage(ImageRes::FURNITURE);
			map[13][9][y].setSolid(true);
		}

	map[13][0][1].setWarp(Position(i,j+1,11)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[13][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//LEVEL 5
	/*/wioska
	map.insert(map.begin() + 14, emptyTerrainLevel(100, 20, 14));
	for(int x=0;x<map[14].size();x++)
	{
		for(int y=0;y<map[14][x].size();y++)
		{
			map[14][x][y].setImage(ImageRes::GORY);
		}
	}

	int powrot_x5;
	int powrot_y5;
	x=0;
	srand(time(NULL));
	y=yp3;
	//game.player = Player( Position(0, y) );
	map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[14][x][y].setWarp(Position(powrot_x4,powrot_y4,11));
	map[14][x][y-1].setImage(ImageRes::ROAD);
	map[14][x][y+1].setImage(ImageRes::ROAD);
	
	for(int x=1;x<80;x++)
	{

		y+=(rand()%3-1);
		if(y<1)
		{
			x--;
			continue;
		}
		if(y>18)
		{
			x--;
			continue;
		}
		else
			{map[14][x][y-1].setImage(ImageRes::ROAD);
			map[14][x][y].setImage(ImageRes::ROAD);
			map[14][x][y+1].setImage(ImageRes::ROAD);}
	}
	/*
	//chata cinkciarza
	int i2=rand()%95+1;
	int j2=rand()%15+1;
	for(x=i2;x<=i2+3;x++)
	{
		for(y=j2; y<=j2+2;y++)
		{
			if(x==i2 && y==j2+1)
			{
				map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[14][x][y].setWarp(Position(0,1,16));
			}
			else
				{
					map[14][x][y].setImage(ImageRes::BRICK);
					map[14][x][y].setSolid(true);
				}
		}

	}
	//wnetrze chaty cinkciarza
	map.insert(map.begin() + 16, emptyTerrainLevel(10, 8, 16));
	for(int x=0;x<map[16].size();x++)
	{
		for(int y=0;y<map[16][x].size();y++)
		{
			map[16][x][y].setImage(ImageRes::WOOD);
		}
	}
	
		for(int y=3;y<6;++y)
		{
			map[16][6][y].setImage(ImageRes::DESK);
			map[16][6][y].setSolid(true);
		}
		
	for(int x=4;x<10;x++)
	{
			map[16][x][0].setImage(ImageRes::FURNITURE);
			map[16][x][0].setSolid(true);
	}
	
	for(int x=2;x<7;x++)
	{
			map[16][x][7].setImage(ImageRes::FURNITURE);
			map[16][x][7].setSolid(true);
	}

		for(int y=3;y<8;y++)
		{
			map[16][9][y].setImage(ImageRes::FURNITURE);
			map[16][9][y].setSolid(true);
		}
		
	map[16][0][1].setWarp(Position(i2,j2+1,14)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[16][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata rzemieslnika
	int r2=rand()%95+1;
	int z2=rand()%15+1;
	for(x=r;x<=r+3;x++)
	{
		for(y=z2; y<=z2+2;y++)
		{
			if(x==r2+1 && y==z2+2)
			{
				map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[14][x][y].setWarp(Position(0,1,17));
			}
			else
				{
					map[14][x][y].setImage(ImageRes::WOOD);
					map[14][x][y].setSolid(true);
				}
		}

	}
	
	//wnetrze chaty rzemieslnika
	map.insert(map.begin() + 17, emptyTerrainLevel(10, 8, 17));
	for(int x=0;x<map[17].size();x++)
	{
		for(int y=0;y<map[17][x].size();y++)
		{
			map[17][x][y].setImage(ImageRes::WALL);
		}
	}
	
	for(int x=3;x<7;x++)
	{
			map[17][x][3].setImage(ImageRes::DESK);
			map[17][x][3].setSolid(true);
	}

		for(int y=3;y<7;y++)
		{
			map[17][3][y].setImage(ImageRes::DESK);
			map[17][3][y].setSolid(true);
		}

		for(int y=3;y<7;y++)
		{
			map[17][7][y].setImage(ImageRes::DESK);
			map[17][7][y].setSolid(true);
		}
		
		map[17][0][1].setWarp(Position(r2+1,z2+2,14)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
		map[17][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0

	//chata mêdrca
	int m2=rand()%95+1;
	int d2=rand()%25+1;
	for(x=m2;x<=m2+3;x++)
	{
		for(y=d2; y<=d2+2;y++)
		{
			if(x==m2+3 && y==d2)
			{
				map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[14][x][y].setWarp(Position(0,1,18));
			}
			else
				{
					map[14][x][y].setImage(ImageRes::WOOD);
					map[14][x][y].setSolid(true);
				}
		}

	}	
	//wnetrze chaty medrca
	map.insert(map.begin() + 18, emptyTerrainLevel(10, 8, 18));
	for(int x=0;x<map[18].size();x++)
	{
		for(int y=0;y<map[18][x].size();y++)
		{
			map[18][x][y].setImage(ImageRes::STAR);
		}
	}

	map[18][0][1].setWarp(Position(m2+3,d2,0));
	map[18][0][1].setImage(ImageRes::EMPTY);
	* /
		//budynek finalowy
		if(x==79)
			{
				for(int x=80; x<100; x++)
				{
					for(int y= 4; y<15; y++)
					{
						if(x==80)
						{
							map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
							map[14][x][y].setWarp(Position(0,yp3,15));
							powrot_x5=x;
							powrot_y5=y;
						}

						map[14][x][y].setImage(ImageRes::STAR);
					}
				}
			}
	

	//pomieszczenie finalowe
	map.insert(map.begin() + 15, emptyTerrainLevel(50, 20, 15));
	for(int x=0;x<map[15].size();x++)
	{
		for(int y=0;y<map[15][x].size();y++)
		{
			map[15][x][y].setImage(ImageRes::DARK_WALL);
		}
	}

	x=0;
	y=yp3;
	map[15][x][y].setImage(ImageRes::EMPTY);
	map[15][x][y].setWarp(Position(powrot_x5, powrot_y5, 14));
	map[15][x][y].setImage(ImageRes::ROAD);
	map[15][x][y-1].setImage(ImageRes::ROAD);
	map[15][x][y+1].setImage(ImageRes::ROAD);

	for(int y=0; y<8;y++)
	{
		for(int y=12; y<20; y++)
		{
			for(int x=1; x<25; x++)
			{
				map[15][x][y].setImage(ImageRes::EMPTY);
				map[15][x][y].setSolid(true);
			}
		}
	}
	*/
	//game.player = Player( Position(0, 2) );
	game.npcs.push_back( NPC(Position(0,1, 0), ImageRes::DEALER) );
	game.npcs.push_back( NPC(Position(8,1, 1), ImageRes::DEALER) );// mo¿e by warto by³o jakiœ NPCBuilder 
	game.enemies.push_back( Enemy(Position(10,5, 0)) ); // mo¿e by warto by³o jakiœ EnemyBuilder 


}

//void GameBuilder::loadFromFile() { }
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

	map[0][0][y].setWalkSpeed(30);
	map[0][0][y-1].setWalkSpeed(30);
	map[0][0][y+1].setWalkSpeed(30);
	
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

				map[0][x][y].setWalkSpeed(30);
				map[0][x][y-1].setWalkSpeed(30);
				map[0][x][y+1].setWalkSpeed(30);
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

/************************************************************************************************************/
	//level 1 - rozmowa z cinkciarzem
	Creature cinkciarz = Creature(Position(8,1, 1), ImageRes::DEALER);
	
	Dialog dialog;

	dialog = Dialog();

	dialog.addNode(Dialog::START_DIALOG, L"Witaj w naszych skromny progach wêdrowcze! W czym mogê s³u¿yæ?").
		addOption(L"Chcia³bym coœ kupiæ, ale nie mam pieniêdzy. Liczê na ³askê.", 1).
		addOption(L"Ach wêdrujê, i szukam przygód. Mo¿e coœ mi polecicie?", 2);

	dialog.addNode(1, L"Drogi Panie! Na ³askê w tych czasach?! Musicie pytaæ gdzie indziej.").
		addOption(L". . .", Dialog::END_DIALOG);

	dialog.addNode(2, L"Na terenach niedalekich jest wiele lasów i gór. Jest co ogl¹daæ i gdzie szukaæ zwady z miejscowymi rozbójnikami.").
		addOption(L"O nie! Uciekam st¹d!", Dialog::END_DIALOG).
		addOption(L"A¿ tak o to ³atwo?", 20);

	dialog.addNode(20, L"Ka¿dy chce pokazaæ jak¹ ma si³ê w ³apie! Zw³aszcza m³odzi. Próbuj¹ dostaæ siê do stra¿y Rogalika.").
		addOption(L"A có¿ to?", 200);

	dialog.addNode(200, L"Musicie byæ chyba z bardzo daleka, ¿e o tym nie wiecie. Rz¹dy nad ca³ym terenem sprawuje szlachcic. Mieszka on w najwiêkszej wiosce i jest bardzo potê¿ny w³aœnie dziêki Rogalikowi. Podobno to jakiœ prezent od mnichów czy od dziadków. Kr¹¿¹ ró¿ne historie. Ale oprócz szlachcica i kilku stra¿ników nikt go nie widzia³. Jest tak pilnie strze¿ony!").
		addOption(L"Wasz w³adca musi byæ straszny!", 201).
		addOption(L"Musicie byæ wiêc zadowoleni z tak wielkiego w³adcy.", 202).
		addOption(L"Obi³o mi siê o uszy, ¿e macie strasznego przywódcê...", 201).
		addOption(L"By³em ciekaw jak tu ¿yjecie, pod rz¹dzami szlachcica.", 203);

	dialog.addNode(201, L"Co takiego?! Mamy najlepszego w³adcê na œwiecie! Jak œmiesz wypowiadaæ takie s³owa?!").
		addOption(L"Wybaczcie, mówiê tylko co s³ysza³em...", 2011);
	
	dialog.addNode(2011, L"To Ÿle us³yszeliœcie! Wynoœ siê!").
		addOption(L"[uciekaj]", Dialog::END_DIALOG);

	dialog.addNode(202, L"Och! Nie jest tak piêknie jak mog³oby siê wydawaæ... Ale z³ego s³owa nikt nie powie. Wszyscy siê boj¹").
		addOption(L"Co siê dzieje?", 2021);

	dialog.addNode(2021, L"Lepiej nie zawracaæ siê tym g³owy, zw³aszcza, ¿e zaraz pójdziecie w dalsz¹ podró¿... a i tak za du¿o ju¿ powiedzia³em... Bywajcie zdrów!").
		addOption(L"Bywajcie!", Dialog::END_DIALOG);
	
	dialog.addNode(203, L"Bardzo dobrze! W koñcu nadesz³y czasy, w których cz³owiek czuje siê bezpiecznie.").
		addOption(L"S³ysza³em co innego...", 2031);

	dialog.addNode(2031, L"Musieliœcie Ÿle zrozumieæ, drogi goœciu.").
		addOption(L". . .", Dialog::END_DIALOG);

	cinkciarz.addDialog(dialog);

	cinkciarz.setType(Creature::Type::DIALOG);
	game.creatures.push_back( cinkciarz );

	/************************************************************************************************************/
	//level 1 - rozmowa z rzemieœlnikiem
	Creature rzemieslnik = Creature(Position(8,1, 2), ImageRes::DEALER);
	
	Dialog dialog0;

	dialog0 = Dialog();

	dialog0.addNode(Dialog::START_DIALOG, L"Co Ciê do mnie sprowadza?").
		addOption(L"S³ysza³em, ¿e ³atwo u Was o bójkê. Okradli mnie przed wiosk¹ i niestety nic nie mam do obrony... Nie wiem jak sobie poradziæ.", 3).
		addOption(L"Macie jakieœ narzêdzia do obrony?", 4);

	dialog0.addNode(3, L"Oj dzieciaku! Nie poradzisz sobie w ¿yciu! Musisz byæ bardziej uwa¿ny. Na	pocz¹tek mogê daæ ci drewniany kij, bo jak s¹dzê pieniêdzy te¿ nie masz.").
		addGiveItem(Item(L"kijek", L"kijek")).
		addOption(L"Dziêkujê za pomoc.", 30);
	
	dialog0.addNode(30, L"IdŸ i uwa¿aj na siebie dzieciaku.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog0.addNode(4, L"Takich rzeczy jest u mnie pod dostatkiem. Co was interesuje i w jakiej cenie?").
		addOption(L"Ale ja niestety nie mam pieniêdzy... Okradli mnie.", 40);

	dialog0.addNode(40, L"Za darmo nic ma.").
		addOption(L"A mo¿e coœ starego, ledwo nadaj¹ce siê do u¿ytku?", 401).
		addOption(L"Mo¿e macie coœ zbêdnego? Lub z nadmiarem?", 402);

	dialog0.addNode(401, L"Nie obra¿ajcie mnie! U mnie nic nie jest do wyrzucenia!").
		addOption(L"Przepraszam, nie to mia³em na myœli...", 4010);

	dialog0.addNode(4010, L"Jeszcze musisz siê wiele nauczyæ. £ap kija i ju¿ idŸ.").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	dialog0.addNode(402, L"Hmm myœlê, ¿e mogê pomóc... Proszê, oto drewniany kij.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	rzemieslnik.addDialog(dialog0);

	rzemieslnik.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik );

	/************************************************************************************************************/
	//level 1 - rozmowa z kowalem
	Creature kowal = Creature(Position(8,1, 3), ImageRes::DEALER);
	
	Dialog dialog1;

	dialog1 = Dialog();

	dialog1.addNode(Dialog::START_DIALOG, L"Czego tu szukasz?").
		addOption(L"Chcia³em zobaczyæ czym siê tutaj zajmujecie.", 5).
		addOption(L"Ale¿ jest Pan mi³y!", 6);

	dialog1.addNode(6, L"WyjdŸ, nie mam nastroju do rozmów!").
		addOption(L"[uciekaj]", Dialog::END_DIALOG);
	
	dialog1.addNode(5, L"Jak widaæ - tym czym ma siê zajmowaæ kowal.").
		addOption(L"Widzê, ¿e jesteœcie zmêczeni.", 50);
		//addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog1.addNode(50, L"Tak. Tyle roboty, ¿e dnia nie starcza. Muszê znaleŸæ kogoœ i oddaæ mu klacz.").
		addOption(L"Z chêci¹ j¹ przyjmê.", Dialog::END_DIALOG). //KONIEC
		addOption(L"No tak, mo¿e byæ ciê¿ko. Wygl¹da na star¹ i s³ab¹.", 501);

	dialog1.addNode(501, L"Mo¿e i wygl¹da, ale jest jeszcze pe³na energii.").
		addOption(L"To mo¿e ja j¹ wezmê?", 5010);

	dialog1.addNode(5010, L"Od zaraz!").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	kowal.addDialog(dialog1);

	kowal.setType(Creature::Type::DIALOG);
	game.creatures.push_back( kowal );

	/************************************************************************************************************/
	////level 1 - rozmowa z medrcem
	Creature medrzec = Creature(Position(8,1, 4), ImageRes::DEALER);
	
	Dialog dialog2;

	dialog2 = Dialog();

	dialog2.addNode(Dialog::START_DIALOG, L"Wyczuwam now¹ energiê w mej przestrzeni! Och! Podró¿niku! Czego szukasz w naszych stronach?").
		addOption(L"Nigdy nie mia³em stycznoœci z eliksirami. By³em ciekaw co tu jest...", 7);

	dialog2.addNode(7, L"I pewnie chcia³byœ coœ kupiæ?").
		addOption(L"Niestety nie mam za co...", 71).
		addOption(L"Nie, w³aœciwie to ju¿ wychodzê.", 72);

	dialog2.addNode(71, L"Och! Jakoœ na to zaradzimy. Jako nowy goœæ przyjmij ode mnie prezent - eliksir ¿ycia.").
		addOption(L"A co to?", 711).
		addOption(L"Chyba wiem co to jest.", 712);

	dialog2.addNode(711, L"Kiedy bêdziesz czu³, ¿e tracisz si³y - napij siê.").
		addOption(L". . .",Dialog::END_DIALOG); //KONIEC

	dialog2.addNode(712, L"W takim razie bêdziesz wiedzia³ kiedy tego u¿yæ.").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	dialog2.addNode(72, L"W takim razie do zobaczenia!").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	medrzec.addDialog(dialog2);

	medrzec.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec );

	/************************************************************************************************************/
	////level 2 - rozmowa z pijakiem
	Creature pijak = Creature(Position(8,1, 5), ImageRes::DEALER);
	
	Dialog dialog3;

	dialog3 = Dialog();

	dialog3.addNode(Dialog::START_DIALOG, L"Hej! Przyjacielu! Mo¿e siê dosi¹dziesz?").
		addOption(L"Nie, dziêkujê! Nie bêdê siedzia³ z pijakiem...", 8).
		addOption(L"Przepraszam, ale muszê czym prêdzej dostaæ siê do Waszego Pana.", 9);

	dialog3.addNode(8, L"Phi! Wa¿niak...").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog3.addNode(9, L"Uuu... To jeszcze d³uga droga przed tob¹, towarzyszu.").
		addOption(L"Znasz jakiœ skrót?", 90);

	dialog3.addNode(90, L"Heh... mo¿e i znam. (czkawka)").
		addOption(L"Mo¿e to Ciê zachêci [daj mu monety].",900);

	dialog3.addNode(900, L"Chcesz mnie przekupiæ?! A mo¿e masz coœ do picia? Trochê boli mnie g³owa...").
		addOption(L"Mo¿e wina?", 9001).
		addOption(L"Niestety nie mam nic.",9002).
		addOption(L"Oszala³eœ?! Nie wiem w ogóle po co z Tob¹ rozmawiam. Sam wybiorê drogê. Na pewno trafiê.", Dialog::END_DIALOG);

	dialog3.addNode(9001, L"Ooo...czywiœcie nie odmówiê!").
		addOption(L"Teraz powiesz mi, któr¹ drog¹ mam iœæ?", 90010);

	dialog3.addNode(90010, L"Pewnie! Ale chyba napijesz siê ze mn¹?").
		addOption(L"Jasne...", 90011);
	dialog3.addNode(90011, L"Jeœli wybierzesz drogê na lewo, to bêdziesz musia³ zap³aciæ za jej pzejœcie i jest trochê d³u¿sza, ale za to bez przeszkód. Jeœli jednak pójdziesz na prawo... S³ysza³em o zbójniku, który chodzi z wilkiem i ma doskona³y miecz! Przyda³by Ci siê!").
		addOption(L"Dziêkujê! Bywaj zdrów!", 90012);
	dialog3.addNode(90012, L"Wst¹p jeszcze kiedyœ!").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog3.addNode(9002, L"Uuu to szkoda. Lubiê czasami wypiæ coœ mocniejszego. Lepiej mi siê myœli.").
		addOption(L"Hmm... Moment. Mo¿e wina?", 9001);

	pijak.addDialog(dialog3);

	pijak.setType(Creature::Type::DIALOG);
	game.creatures.push_back( pijak );

	/************************************************************************************************************/
	////level 3 - rozmowa z rzemieslnikiem
	Creature rzemieslnik2 = Creature(Position(8,1, 9), ImageRes::DEALER);
	
	Dialog dialog4;

	dialog4 = Dialog();

	dialog4.addNode(Dialog::START_DIALOG, L"W czym mogê pomóc?").
		addOption(L"Chcia³bym kupiæ zbroje.", 10).
		addOption(L"Tylko siê rozgl¹dam.", 11);

	dialog4.addNode(10, L"A jakieœ konkretne wymagania?").
		addOption(L"Nie wiem. Nie znam siê.", 101).
		addOption(L"Mam niewiele pieniêdzy. Nie wiem na jak¹ mnie staæ.", 102);

	dialog4.addNode(101, L"Mam tego doœæ sporo, rozejrzyj siê, a kiedy coœ znajdziesz - powiedz.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog4.addNode(102, L"Zbroja jest wa¿na. Warto zap³aciæ za ni¹ wiêcej. Wróæ jak ju¿ bêdziesz mia³ wystarczaj¹co du¿o monet.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	rzemieslnik2.addDialog(dialog4);

	rzemieslnik2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik2 );

	/************************************************************************************************************/
	////level 3 - rozmowa z kolesiem
	Creature koles = Creature(Position(8,1, 11), ImageRes::DEALER);
	
	Dialog dialog5;

	dialog5 = Dialog();

	dialog5.addNode(Dialog::START_DIALOG, L"Hej, ty! Ile chcesz za tego konia?").
		addOption(L"Nie jest na sprzeda¿!", 12).
		addOption(L"A ile proponujesz?", 13);

	dialog5.addNode(12, L"No tak, zawsze mo¿na wzi¹æ si³¹ co siê chce!").
		addOption(L"[walcz]", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	dialog5.addNode(13, L"Nie wygl¹da najlepiej, ale i taka by mi siê przyda³a. Hmm 8 monet.").
		addOption(L"Ma³o, chcê 12.", 130).
		addOption(L"Dobrze, jest Twoja", Dialog::END_DIALOG); //KONIEC

	dialog5.addNode(130, L"Mogê daæ 10 i ani monety wiêcej.").
		addOption(L"Dobrze, jest Twoja", Dialog::END_DIALOG). //KONIEC
		addOption(L"W takim razie nic z tego.", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	koles.addDialog(dialog5);

	koles.setType(Creature::Type::DIALOG);
	game.creatures.push_back( koles );

	/************************************************************************************************************/
	////level 3 - rozmowa z medrcem
	Creature medrzec2 = Creature(Position(8,1, 10), ImageRes::DEALER);
	
	Dialog dialog6;

	dialog6 = Dialog();

	dialog6.addNode(Dialog::START_DIALOG, L"Czego szukasz, drogi wêdrowcze?").
		addOption(L"Potrzebujê czegoœ na wzmocnienie.", 14).
		addOption(L"Nic konkretnego.", 15);

	dialog6.addNode(14, L"Hmm dobrym rozwi¹zaniem bêdzie eliksir ¿ycia.").
		addOption(L"W takim razie biorê!", 140);

	dialog6.addNode(140, L"A mo¿e by³byœ zainteresowany czymœ jeszcze?").
		addOption(L"Nie, dziêkujê. Myœlê, ¿e na razie wystarczy.", Dialog::END_DIALOG).
		addOption(L"Macie coœ do zaproponowania?", 1400);

	dialog6.addNode(1400, L"Doskona³y z³oty proszek usypiaj¹cy. Ka¿demu w koñcu siê przydaje.").
		addOption(L"Hmm. Mo¿e innym razem. Dziêkujê!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Skoro tak twierdzicie to mo¿e i mnie siê przyda.",1401);

	dialog6.addNode(1401, L"Z pewnoœci¹.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog6.addNode(15, L"Mo¿e móg³bym coœ zaproponowaæ?").
		addOption(L"Z chêci¹ pos³ucham.", 1400);

	medrzec2.addDialog(dialog6);

	medrzec2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec2 );

	/************************************************************************************************************/
	////level 3 - rozmowa ze stra¿nikiem
	Creature straznik = Creature(Position(8,1, 8), ImageRes::DEALER);
	
	Dialog dialog7;

	dialog7 = Dialog();

	dialog7.addNode(Dialog::START_DIALOG, L"Czego?").
		addOption(L"Czy otworzycie bramy?", 16).
		addOption(L"Wypuœæ mnie! Chcê wyjœæ!", 162);
		
	dialog7.addNode(16, L"To zale¿y jak poprosisz! (œmiech)").
		addOption(L"Mam zap³aciæ?",161).
		addOption(L"Pewnie chcecie pieniêdzy? Otwieranie bramy jest waszym obowi¹zkiem!", 162);

	dialog7.addNode(161, L"Myœlê, ¿e powinno wystarczyæ.").
		addOption(L"[zaplac]", Dialog::END_DIALOG);//KONIEC

	dialog7.addNode(162, L"Mo¿e trochê szacunku! Co?!").
		addOption(L"Niby dlaczego?", 1620);

	dialog7.addNode(1620, L"Szukasz niepotrzebnego problemu, ch³opaczku.").
		addOption(L"Mam zap³aciæ?", 161).
		addOption(L"Ch³opaczku?! Jak œmiesz?!", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	straznik.addDialog(dialog7);

	straznik.setType(Creature::Type::DIALOG);
	game.creatures.push_back( straznik );

	/************************************************************************************************************/
	////level 4 - rozmowa z kolesiem
	Creature koles2 = Creature(Position(8,1, 12), ImageRes::DEALER);
	
	Dialog dialog8;

	dialog8 = Dialog();

	dialog8.addNode(Dialog::START_DIALOG, L"Masz coœ do jedzenia?").
		addOption(L"Nie, nie mam.", Dialog::END_DIALOG).
		addOption(L"Coœ mog³oby siê znaleŸæ.", 17);
		
	dialog8.addNode(17, L"Podzielisz siê?").
		addOption(L"Widzê, ¿e potrzebujesz bardziej ni¿ ja.",171).
		addOption(L"Mogê Ci sprzedaæ. Potrzebujê piniêdzy wiêc ka¿da moneta siê przyda.", 172);

	dialog8.addNode(171, L"Och, jesteœcie tacy mi³osierni. Przyjmijcie w zamian eliksir ¿ycia.").
		addOption(L"[zaplac]", Dialog::END_DIALOG);//KONIEC

	dialog8.addNode(172, L"No dobrze, mam kilka.").
		addOption(L"[zaplac]", Dialog::END_DIALOG); //KONIEC

	koles2.addDialog(dialog8);

	koles2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( koles2 );

	/************************************************************************************************************/
	////level 4 - rozmowa ze zbieraczem narzedzi
	Creature zbieracz = Creature(Position(8,1, 13), ImageRes::DEALER);
	
	Dialog dialog9;

	dialog9 = Dialog();

	dialog9.addNode(Dialog::START_DIALOG, L"Zapraszam w me skromne progi!").
		addOption(L"O przepraszam, nie wiedzia³em, ¿e ktoœ tu mieszka.", 18);
		
	dialog9.addNode(18, L"Nie dziwi mnie to, w takim miejscu.").
		addOption(L"Nie chcê przeszkadzaæ, wszystkiego dobrego!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Czym siê zajmujecie tutaj?", 180);

	dialog9.addNode(180, L"G³ównie to zbieraniem narzêdzi i udoskonalaniem ich.").
		addOption(L"Czyli siê nie nudzicie.", 181);

	dialog9.addNode(181, L"Jeœli macie coœ do sprzeda¿y, to z chêci¹ kupiê.").
		addOption(L"W³aœciwie to nic czego chcia³bym siê pozbyæ.", 1811).
		addOption(L"Hmm... co najwy¿ej ciupagê.",1812);

	dialog9.addNode(1811, L"Szkoda, gdybyœ jednak siê zdecydowa³, wiesz gdzie mnie szukaæ.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	
	dialog9.addNode(1812, L"Biorê! A dok¹d siê wybieracie?").
		addOption(L"Przed siebie szukaæ przygód.", 18121).
		addOption(L"Do Waszego Pana. S³ysza³em ró¿ne historie o nim i jego panowaniu.", 18122);

	dialog9.addNode(18121, L"W takim razie szerokiej drogi").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog9.addNode(18122, L"Ach! B¹dŸ ostro¿ny. W domu szlachcica mieszka podobno straszny potwór. Nie widzia³em na w³asne oczy, ale czasami bywam w wiosce i ludzie gadaj¹. Myœlê, ¿e czegoœ pilnuje.").
		addOption(L"Dziêkujê. Bêdê mia³, jak to mówi¹, oczy dooko³a g³owy.", Dialog::END_DIALOG); //KONIEC

	zbieracz.addDialog(dialog9);

	zbieracz.setType(Creature::Type::DIALOG);
	game.creatures.push_back( zbieracz );

	/************************************************************************************************************/
	////level 5 - rozmowa z rzemieslnikiem
	Creature rzemieslnik3 = Creature(Position(8,1, 17), ImageRes::DEALER);
	
	Dialog dialog10;

	dialog10 = Dialog();

	dialog10.addNode(Dialog::START_DIALOG, L"Co bêdzie?").
		addOption(L"Nic nie chcê.", 19).
		addOption(L"Chcia³bym kupiæ zbroje.", 21);
		
	dialog10.addNode(19, L"To po co przychodzisz?").
		addOption(L"Chcia³em zbrojê, ale tutaj nie widzê nic co by³oby odpowiednie.", 190);

	dialog10.addNode(190, L"Ka¿dy cwany. Jeœli siê jednak zdecydujecie, wiecie gdzie wróciæ. Lepszych nigdzie nei znajdziecie.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog10.addNode(21, L"Nie wygl¹dacie na kogoœ kto ma tyle pieniêdzy.").
		addOption(L"Pozory myl¹.", 211).
		addOption(L"Proszê sobie oszczêdziæ takich komentarzy..",212);

	dialog10.addNode(211, L"Oczywiœcie zaraz znajdê coœ odpowiedniego.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	
	dialog10.addNode(212, L"Ka¿dy cwany. Zaraz znajdê coœ odpowiedniego.").
		addOption(L". . .", Dialog::END_DIALOG);

	rzemieslnik3.addDialog(dialog10);

	rzemieslnik3.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik3 );

	/************************************************************************************************************/
	////level 5 - rozmowa z medrcem
	Creature medrzec3 = Creature(Position(8,1, 18), ImageRes::DEALER);
	
	Dialog dialog11;

	dialog11 = Dialog();

	dialog11.addNode(Dialog::START_DIALOG, L"Co przygotowaæ?").
		addOption(L"Potrzebujê eliksiru ¿ycia.", 22).
		addOption(L"Sam nie wiem czego chcê.", 23);
		
	dialog11.addNode(22, L"Tylko go nie marnuj...").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog11.addNode(23, L"Wróæ kiedy bêdziesz czegoœ potrzebowa³.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	medrzec3.addDialog(dialog11);

	medrzec3.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec3 );

	/************************************************************************************************************/
	////level 5 - rozmowa z cinkcarzem
	Creature cinkciarz2 = Creature(Position(8,1, 16), ImageRes::DEALER);
	
	Dialog dialog12;

	dialog12 = Dialog();

	dialog12.addNode(Dialog::START_DIALOG, L"S³u¿ê uprzejmie!").
		addOption(L"Chcia³bym dostaæ siê do Waszego Pana, niestety nie znam drogi.", 24).
		addOption(L"Gdzie znajdê dom Szlachcica?", 25);
		
	dialog12.addNode(25, L"Przy koñcu wioski.").
		addOption(L"Dziêkujê!", 250);

	dialog12.addNode(250, L"BadŸ ostro¿ny, kiedy tam wejdziesz.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog12.addNode(24, L"Musisz iœæ do koñca wioski. Na pewno rozpoznasz jego dom.").
		addOption(L"Dziêkujê!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Podobno mieszka w nim jakiœ straszny potwór, to prawda?", 240);

	dialog12.addNode(240, L"O tak! Przyda³aby Ci siê jakaœ czarodziejska sztuczka. Wybierz siê do mêdrca. Na pewno coœ wymyœli. Przyda Ci sie pochodnia, któr¹ znajdziesz na pocz¹tku korytarza prowadz¹cego do miejsca gdzie znajduje sie Rogalik.").
		addOption(L"Ale czym j¹ rozpalê?", 2401).
		addOption(L"Zapamiêtam te wskazówki.", Dialog::END_DIALOG);

	dialog12.addNode(2401, L"Mam coœ takiego jak rozpa³ka do ognia.").
		addOption(L"Z chêci¹ kupiê!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Chcesz mnie naci¹gn¹æ!", 2402);

	dialog12.addNode(2402, L"Bêdziesz ¿a³owa³ i jeszcze po ni¹ wrócis!").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	
	dialog12.addNode(212, L"Ka¿dy cwany. Zaraz znajdê coœ odpowiedniego.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	cinkciarz2.addDialog(dialog12);

	cinkciarz2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( cinkciarz2 );

	/************************************************************************************************************/
	////level 5 - rozmowa z medrcem (powrot)
	Creature medrzec4 = Creature(Position(8,1, 18), ImageRes::DEALER);
	
	Dialog dialog13;

	dialog13 = Dialog();

	dialog13.addNode(Dialog::START_DIALOG, L"Widzê, ¿e o czymœ sobie przypomnia³eœ!").
		addOption(L"Potrzebujê jakiejœ <<magicznej sztuczki>>.", 26).
		addOption(L"Wybieram sie do szlachcica. Dowiedzia³em siê, ¿e bêdê potrzebowa³ jakiejœ <<magicznej sztuczki>>. Moglibyœcie mi jakoœ pomóc?", 261);
		
	dialog13.addNode(26, L"Niewiele mi to mówi. Musisz siê bardziej postaraæ.").
		addOption(L"Idê do szlachcica.", 261).
		addOption(L"Nie powinno Was to interesowaæ.",  262);

	dialog13.addNode(262, L"W takim razie nie mogê pomóc.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog13.addNode(261, L"Ach! Do szlachcica. Pewnie zainteresowa³ Ciê Rogalik.").
		addOption(L"Pewnie jak wielu innych.", 2611).
		addOption(L"To ju¿ nie Wasz sprawa.", 2612);


	dialog13.addNode(2611, L"Niech pomyœlê... proponujê kolorowy piasek. O jego w³aœciwoœciach nie mogê mówiæ, ka¿dy na swój sposób wie kiedy i jak go u¿yæ.").
		addOption(L"Mam nadziejê, ¿e i ja siê dowiem.", Dialog::END_DIALOG); //KONIEC

	dialog13.addNode(2612, L"Nie mogê pomóc jeœli nie wiem o co chodzi.").
		addOption(L"Hmm... no dobrze. Zainteresowa³ mnie i to bardzo. Pomo¿ecie?", 2611);

	medrzec4.addDialog(dialog13);

	medrzec4.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec4 );
	/////////////////////////////////////////////////////////////////////////////////

	Creature losowypotwor = Creature(Position(10,5, 0), ImageRes::MONSTER);
	losowypotwor.setSpeed(3); // doœæ wolny
	losowypotwor.setAI(Creature::AI::RANDOM_WALK); // losowo b³¹dzi
	losowypotwor.setType(Creature::Type::HOSTILE); // wrogi
	losowypotwor.addLoot( Item(L"Badyl¹ê", L"Przepotê¿ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor );


}

//void GameBuilder::loadFromFile() { }
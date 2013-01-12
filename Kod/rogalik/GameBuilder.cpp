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
void GameBuilder::buildHouse(std::vector< std::vector< std::vector<Tile> > > &map,int level , int x , int y,bool var)
{
	if(var)
	{
		map[level][x-1][y-2].setImage(ImageRes::ROOF);
		map[level][x-1][y-2].setSolid(true);
		map[level][x][y-2].setImage(ImageRes::ROOF);
		map[level][x][y-2].setSolid(true);
		map[level][x+1][y-2].setImage(ImageRes::ROOF);
		map[level][x+1][y-2].setSolid(true);

		map[level][x-1][y-1].setImage(ImageRes::ROOFN);
		map[level][x-1][y-1].setSolid(true);
		map[level][x][y-1].setImage(ImageRes::ROOFN);
		map[level][x][y-1].setSolid(true);
		map[level][x+1][y-1].setImage(ImageRes::ROOFN);
		map[level][x+1][y-1].setSolid(true);

		map[level][x-1][y].setImage(ImageRes::WINDOW);
		map[level][x-1][y].setSolid(true);
		map[level][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
		map[level][x][y].setWarp(Position(0,1,1));
		map[level][x+1][y].setImage(ImageRes::WINDOW);
		map[level][x+1][y].setSolid(true);
	}
	else
	{
		
		map[level][x-1][y-2].setImage(ImageRes::ROOF2);
		map[level][x-1][y-2].setSolid(true);
		map[level][x][y-2].setImage(ImageRes::ROOF2);
		map[level][x][y-2].setSolid(true);
		map[level][x+1][y-2].setImage(ImageRes::ROOF2);
		map[level][x+1][y-2].setSolid(true);

		map[level][x-1][y-1].setImage(ImageRes::ROOFN2);
		map[level][x-1][y-1].setSolid(true);
		map[level][x][y-1].setImage(ImageRes::ROOFN2);
		map[level][x][y-1].setSolid(true);
		map[level][x+1][y-1].setImage(ImageRes::ROOFN2);
		map[level][x+1][y-1].setSolid(true);

		map[level][x-1][y].setImage(ImageRes::WINDOW2);
		map[level][x-1][y].setSolid(true);
		map[level][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
		map[level][x][y].setWarp(Position(0,1,1));
		map[level][x+1][y].setImage(ImageRes::WINDOW2);
		map[level][x+1][y].setSolid(true);
	}
}
void GameBuilder::buildFurniture(std::vector< std::vector< std::vector<Tile> > > &map,int level , int x , int y)
{
	map[level][x][y-1].setImage(ImageRes::FURN1A);
	map[level][x][y-1].setSolid(true);
	map[level][x][y].setImage(ImageRes::FURN1B);
	map[level][x][y].setSolid(true);
	map[level][x+1][y-1].setImage(ImageRes::FURN2A);
	map[level][x+1][y-1].setSolid(true);
	map[level][x+1][y].setImage(ImageRes::FURN2B);
	map[level][x+1][y].setSolid(true);
}
void GameBuilder::generateNewGame()
{
	game = Game(); // nowa pusta gra
	std::vector< std::vector< std::vector<Tile> > > &map = game.terrain.map;
	
	map.reserve(20);// rezerwacja ilosci poziomow
	//map[0][2][2].setImage(ImageRes::ROOF);
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
	int y=rand()%27+2;
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

		
		//srand(time(NULL));
		if(x%30==0)
		{
			Creature losowypotwor2 = Creature(Position(x,y, 0), ImageRes::MONSTER);
			losowypotwor2.setSpeed(2); // wolny
			losowypotwor2.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			losowypotwor2.setType(Creature::Type::HOSTILE); // wrogi
			losowypotwor2.addLoot( Item(L"Badyl", L"Przepot�ny kostur? Totalnie badyl!").setProperty(Item::WEAPON, 0.05) );
			losowypotwor2.addLootMoney(1);
			game.creatures.push_back( losowypotwor2 );
		}
		//cwaniaczek na koncu wioski 1
		if(x==95)
		{
			Creature cwaniaczek = Creature(Position(x,y, 0), ImageRes::MONSTER);
			cwaniaczek.setSpeed(4); // do�� wolny
			cwaniaczek.setAI(Creature::AI::FIGHT_AND_FLEE); // tam gdzie gracz
			cwaniaczek.setType(Creature::Type::HOSTILE); // wrogi
			cwaniaczek.addLoot( Item(L"Trunek", L"Butelka wina.") );
			cwaniaczek.addLoot(Item(L"Moneta", L"Sakwa monet."));
			cwaniaczek.addLootMoney(10);
			game.creatures.push_back( cwaniaczek );
		}

		if(x==99)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,yp,5));
				powrot_x1=x;
				powrot_y1=y;
			}
			
	}
	buildHouse(map,0,3,3,false);
	//chata cinkciarza
	/*int i=rand()%25+1;
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
	*/
	int i=rand()%25+1;
	int j= 0 ;//=rand()%15+1;
	bool war=true;
	int house_x, house_y;
	house_x = rand()%50+5;
	house_y = rand()%15+3;
	//std::cout << house_x << " " << house_y << std::endl;
	buildHouse(map,0,house_x,house_y);
	buildFurniture(map,0,6,6);
	//while(war)
	///{
	//j=rand()%15+1;
	/*
	if( j<(y-4) || j>(y+2) )
	{
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
					map[0][x][y].setImage(ImageRes::ROOF);
					map[0][x][y].setSolid(true);
				}
			}

		}
		war=false;
	}
	else continue;
	}*/
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
	int r=rand()%25+28;
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
	int k=rand()%20+55;
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
	
	//chata m�drca
	int m=rand()%10+82;
	int d=rand()%15+1;
	for(int x=m;x<=m+3;x++)
	{
		for(int y=d; y<=d+2;y++)
		{
			if(x==m+3 && y==d)
			{
				map[0][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[0][x][y].setWarp(Position(0,0,4));
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

	for(y=3;y<6;y++)
	{
		map[4][7][y].setImage(ImageRes::DARK_WALL);
		map[4][7][y].setSolid(true);

		map[4][5][y].setImage(ImageRes::FURNITURE);
		map[4][5][y].setSolid(true);

		map[4][3][y].setImage(ImageRes::DARK_WALL);
		map[4][3][y].setSolid(true);

		map[4][1][y].setImage(ImageRes::FURNITURE);
		map[4][1][y].setSolid(true);
	}
	map[4][0][0].setWarp(Position(m+3,d,0));
	map[4][0][0].setImage(ImageRes::EMPTY);
	
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
			
			map[5][x][y].setWalkSpeed(30);
			map[5][x][y-1].setWalkSpeed(30);
			map[5][x][y+1].setWalkSpeed(30);
		}
		if(x%30==0)
		{
			Creature las = Creature(Position(x,y, 5), ImageRes::MONSTER);
			las.setSpeed(2); // wolny
			las.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			las.setType(Creature::Type::HOSTILE); // wrogi
			//losowypotwor2.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!").setProperty(Item::WEAPON, 0.05) );
			las.addLootMoney(1);
			game.creatures.push_back( las );
		}
		if(x==69)
		{
			for(int y=5;y<15;y++)
			{
				map[5][x][y].setImage(ImageRes::ROAD2);
				map[5][x+1][y].setImage(ImageRes::ROAD2);
				map[5][x+2][y].setImage(ImageRes::ROAD2);
				
				map[5][x][y].setWalkSpeed(30);
				map[5][x+1][y].setWalkSpeed(30);
				map[5][x+2][y].setWalkSpeed(30);
			}
		}
		else
		{
			map[5][x][y].setImage(ImageRes::ROAD2);
			map[5][x][y-1].setImage(ImageRes::ROAD2);
			map[5][x][y+1].setImage(ImageRes::ROAD2);
			
			map[5][x][y].setWalkSpeed(30);
			map[5][x][y-1].setWalkSpeed(30);
			map[5][x][y+1].setWalkSpeed(30);
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

		map[5][x][y].setWalkSpeed(30);
		map[5][x][y-1].setWalkSpeed(30);
		map[5][x][y+1].setWalkSpeed(30);

		int yy = 13+(rand()%3);
		map[5][x][yy].setImage(ImageRes::ROAD2);
		map[5][x][yy-1].setImage(ImageRes::ROAD2);
		map[5][x][yy+1].setImage(ImageRes::ROAD2);

		map[5][x][yy].setWalkSpeed(30);
		map[5][x][yy-1].setWalkSpeed(30);
		map[5][x][yy+1].setWalkSpeed(30);

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
	//troll
	Creature troll = Creature(Position(1,10+(rand()%3), 5), ImageRes::MONSTER);
	troll.setSpeed(5); // do�� wolny
	troll.setAI(Creature::AI::FIGHT_AND_FLEE); 
	troll.setType(Creature::Type::HOSTILE); // wrogi
	troll.addLoot( Item(L"Czapka", L"Czapka").setProperty(Item::ARMOR, 0.1) );
	game.creatures.push_back( troll );

	srand(time(NULL));
	for(int i=0; i<200; ++i)
	{
		
		int x=rand()%96+2;
		//srand(time(NULL));
		int y=rand()%19;
		map[5][x][y].setImage(ImageRes::TREE);
		map[5][x][y].setSolid(true);
	}
	
	int yp4=rand()%27+1;
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

		map[6][x][y].setWalkSpeed(30);
		map[6][x][y-1].setWalkSpeed(30);
		map[6][x][y+1].setWalkSpeed(30);

		if(x==0)
		{
			map[6][x][y].setWarp(Position(powrot_x1,powrot_y1,5));
			map[6][x][y].setImage(ImageRes::EMPTY);
		}
		if(x%8==0)
		{
			Creature wlesie = Creature(Position(x,y, 6), ImageRes::MONSTER);
			wlesie.setSpeed(2); // wolny
			wlesie.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			wlesie.setType(Creature::Type::HOSTILE); // wrogi
			wlesie.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!").setProperty(Item::WEAPON, 0.05) );
			wlesie.addLootMoney(1);
			game.creatures.push_back( wlesie );
		}
		if(x==39)
		{
			map[6][x][y].setImage(ImageRes::EMPTY);
			map[6][x][y].setWarp(Position(0, yp4, 8));
			powrot_x1=x;
			powrot_y1=y;
		}
	}
	srand(time(NULL));
	for(int i=0; i<100; ++i)
	{
		
		int x=rand()%36+2;
		int y=rand()%7;
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
	int lvl;
	srand(time(NULL));
	for(int x=0;x<40;x++)
	{
		int y=7+(rand()%3);
		map[7][x][y].setImage(ImageRes::ROAD2);
		map[7][x][y-1].setImage(ImageRes::ROAD2);
		map[7][x][y+1].setImage(ImageRes::ROAD2);

		map[7][x][y].setWalkSpeed(30);
		map[7][x][y-1].setWalkSpeed(30);
		map[7][x][y+1].setWalkSpeed(30);

		if(x==0)
		{
			map[7][x][y].setWarp(Position(powrot_x2,powrot_y2,5));
			map[7][x][y].setImage(ImageRes::EMPTY);
		}
		if(x==20)
		{
			Creature rozbojnik = Creature(Position(x,y, 7), ImageRes::MONSTER);
			rozbojnik.setSpeed(5); // wolny
			rozbojnik.setAI(Creature::AI::OFFENSIVE_FAST); // tam gdzie gracz
			rozbojnik.setType(Creature::Type::HOSTILE); // wrogi
			rozbojnik.addLoot( Item(L"Miecz", L"Miecz").setProperty(Item::WEAPON, 0.5) );
			rozbojnik.addLootMoney(10);
			game.creatures.push_back( rozbojnik );
		}
		if(x%10==0)
		{
			Creature wlesie2 = Creature(Position(x,y, 7), ImageRes::MONSTER);
			wlesie2.setSpeed(2); // wolny
			wlesie2.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			wlesie2.setType(Creature::Type::HOSTILE); // wrogi
			wlesie2.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!").setProperty(Item::WEAPON, 0.05) );
			wlesie2.addLootMoney(1);
			game.creatures.push_back( wlesie2 );
		}
		if(x==39)
		{
			map[7][x][y].setImage(ImageRes::EMPTY);
			map[7][x][y].setWarp(Position(0, yp4, 8));
			powrot_x2=x;
			powrot_y2=y;
			lvl =7;
		}
	}
	for(int i=0; i<100; ++i)
	{
		int x=rand()%36+2;
		int y=rand()%7;
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
	//y=rand()%27+1;
	y=yp4;

	map[8][x][y].setImage(ImageRes::EMPTY);
	if(lvl==7)
	map[8][x][y].setWarp(Position(powrot_x2,powrot_y2,7));
	else
	//map[8][x][y].setImage(ImageRes::EMPTY);
	map[8][x][y].setWarp(Position(powrot_x1,powrot_y1,6));
	//map[8][x][y].setImage(ImageRes::EMPTY);
	//map[8][x][y].setWarp(Position(powrot_x2,powrot_y2,7));


	map[8][x][y].setImage(ImageRes::EMPTY);
	map[8][x][y-1].setImage(ImageRes::ROAD);
	map[8][x][y+1].setImage(ImageRes::ROAD);

	map[8][x][y].setWalkSpeed(30);
	map[8][x][y-1].setWalkSpeed(30);
	map[8][x][y+1].setWalkSpeed(30);
	
	int powrot_x3;
	int powrot_y3;
	int postaw, postaw2;
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
		{
			map[8][x][y-1].setImage(ImageRes::ROAD);
			map[8][x][y].setImage(ImageRes::ROAD);
			map[8][x][y+1].setImage(ImageRes::ROAD);

			map[8][x][y].setWalkSpeed(30);
			map[8][x][y-1].setWalkSpeed(30);
			map[8][x][y+1].setWalkSpeed(30);
		}
		if(x%19==0)
		{
			Creature losowypotwor6 = Creature(Position(x,y, 8), ImageRes::MONSTER);
			losowypotwor6.setSpeed(2); // wolny
			losowypotwor6.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			losowypotwor6.setType(Creature::Type::HOSTILE); // wrogi
			//losowypotwor6.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
			game.creatures.push_back( losowypotwor6 );
		}
		if(x==30) postaw=y;
		if(x==98) postaw2=y;
		if(x==99)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,yp2,12));
				powrot_x3=x;
				powrot_y3=y;
			}
			
	}
	//chata rzemieslnika
	/*int r*/r=rand()%25+1;
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
	
	//chata m�drca
	/*int m*/m=rand()%25+28;
	/*int d*/d=rand()%25+1;
	for(int x=m;x<=m+3;x++)
	{
		for(int y=d; y<=d+2;y++)
		{
			if(x==m+3 && y==d)
			{
				map[8][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[8][x][y].setWarp(Position(0,0,10));
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
	for(y=3;y<6;y++)
	{
		map[10][7][y].setImage(ImageRes::DARK_WALL);
		map[10][7][y].setSolid(true);

		map[10][5][y].setImage(ImageRes::FURNITURE);
		map[10][5][y].setSolid(true);

		map[10][3][y].setImage(ImageRes::DARK_WALL);
		map[10][3][y].setSolid(true);

		map[10][1][y].setImage(ImageRes::FURNITURE);
		map[10][1][y].setSolid(true);
	}
	map[10][0][0].setWarp(Position(m+3,d,8));
	map[10][0][0].setImage(ImageRes::EMPTY);
	
	//Bar
	int b=rand()%20+55;
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
	int postaw3;
	map[12][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[12][x][y].setWarp(Position(powrot_x3,powrot_y3,8));
	map[12][x][y-1].setImage(ImageRes::ROAD);
	map[12][x][y+1].setImage(ImageRes::ROAD);

	map[12][x][y].setWalkSpeed(30);
	map[12][x][y-1].setWalkSpeed(30);
	map[12][x][y+1].setWalkSpeed(30);
	
	//troll
	Creature troll2 = Creature(Position(1,y, 12), ImageRes::MONSTER);
	troll2.setSpeed(4); // do�� wolny
	troll2.setAI(Creature::AI::OFFENSIVE_FAST); //tam gdzie gracz
	troll2.setType(Creature::Type::HOSTILE); // wrogi
	//troll2.addLoot( Item(L"Czapka", L"Czapka") );
	game.creatures.push_back( troll2 );
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
		{
			map[12][x][y-1].setImage(ImageRes::ROAD);
			map[12][x][y].setImage(ImageRes::ROAD);
			map[12][x][y+1].setImage(ImageRes::ROAD);

			map[12][x][y].setWalkSpeed(30);
			map[12][x][y-1].setWalkSpeed(30);
			map[12][x][y+1].setWalkSpeed(30);
		}
		if(x%30==0)
		{
			Creature losowypotwor6 = Creature(Position(x,y, 12), ImageRes::MONSTER);
			losowypotwor6.setSpeed(2); // wolny
			losowypotwor6.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
			losowypotwor6.setType(Creature::Type::HOSTILE); // wrogi
			//losowypotwor6.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
			game.creatures.push_back( losowypotwor6 );
		}
		if(x==50)
		{
			Creature goral = Creature(Position(x, y, 12), ImageRes::MONSTER);
			goral.setSpeed(3); // do�� wolny
			goral.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo
			goral.setType(Creature::Type::HOSTILE); // wrogi
			goral.addLoot( Item(L"Ciupaga", L"Ciupaga").setProperty(Item::WEAPON, 0.3) );
			game.creatures.push_back( goral );
		}
		if(x==33) postaw3=y;
		if(x==99)
			{
				map[12][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[12][x][y].setWarp(Position(0,yp3,14));
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

			map[13][3][y].setImage(ImageRes::DESK);
			map[13][3][y].setSolid(true);
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

	map[13][0][1].setWarp(Position(i,j+1,12)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[13][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//LEVEL 5
	//wioska
	map.insert(map.begin() + 14, emptyTerrainLevel(100, 20, 14));
	for(int x=0;x<map[14].size();x++)
	{
		for(int y=0;y<map[14][x].size();y++)
		{
			map[14][x][y].setImage(ImageRes::GRASS);
		}
	}

	int powrot_x5;
	int powrot_y5;
	x=0;
	srand(time(NULL));
	y=yp3;
	//game.player = Player( Position(0, y) );
	map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	map[14][x][y].setWarp(Position(powrot_x4,powrot_y4,12));
	map[14][x][y-1].setImage(ImageRes::ROAD);
	map[14][x][y+1].setImage(ImageRes::ROAD);

	map[14][x][y].setWalkSpeed(30);
	map[14][x][y-1].setWalkSpeed(30);
	map[14][x][y+1].setWalkSpeed(30);
	
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
		{
			map[14][x][y-1].setImage(ImageRes::ROAD);
			map[14][x][y].setImage(ImageRes::ROAD);
			map[14][x][y+1].setImage(ImageRes::ROAD);
		
			map[14][x][y].setWalkSpeed(30);
			map[14][x][y-1].setWalkSpeed(30);
			map[14][x][y+1].setWalkSpeed(30);
		}
		if(x==79)
			{
				x++;

				for(int y=6; y<11;y++)
				{
					if(x==80)
					{
						map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
						map[14][x][y].setWarp(Position(0,yp3,15));
						powrot_x5=x;
						powrot_y5=y;
					}
				}

				for(int y= 4; y<15; y++)
				//for(int x=80; x<100; x++)
				{
					for(int x=81; x<100; x++)
					//for(int y= 4; y<15; y++)
					{
						/*if(x==80)
						{
							map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
							map[14][x][y].setWarp(Position(0,yp3,15));
							powrot_x5=x;
							powrot_y5=y;
						}*/

						map[14][x][y].setImage(ImageRes::GOLD);
						map[14][x][y].setSolid(true);
					}
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
	map[15][x][y].setImage(ImageRes::EMPTY);
	//map[15][x][y-1].setImage(ImageRes::ROAD);
	//map[15][x][y+1].setImage(ImageRes::ROAD);

	for(int y=0; y<8;y++)
	{
		for(int x=1; x<25; x++)
			{
				map[15][x][y].setImage(ImageRes::EMPTY);
				map[15][x][y].setSolid(true);
			}
	}

	for(int y=12; y<20; y++)
	{
		for(int x=1; x<25; x++)
		{
			map[15][x][y].setImage(ImageRes::EMPTY);
			map[15][x][y].setSolid(true);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////
	//chata cinkciarza
	int ii=rand()%23+50;
	int jj=rand()%15+1;
	for(int x=ii;x<=ii+3;x++)
	{
		for(int y=jj; y<=jj+2;y++)
		{
			if(x==ii && y==jj+1)
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
	
	for(int y=3;y<6;y++)
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
		
	map[16][0][1].setWarp(Position(ii,jj+1,14)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
	map[16][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	
	//chata rzemieslnika
	int rr=rand()%20+1;
	int zz=rand()%15+1;
	for(int x=rr;x<=rr+3;x++)
	{
		for(int y=zz; y<=zz+2;y++)
		{
			if(x==rr+1 && y==zz+2)
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
		
		map[17][0][1].setWarp(Position(rr+1,zz+2,14)); //miejsce przejscia z jednego poziomu np. 1 1 1 [z x y] do 13 12 0 [x y z]
		map[17][0][1].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
	
	//chata m�drca
	int mm=rand()%22+23;
	int dd=rand()%15+1;
	for(int x=mm;x<=mm+3;x++)
	{
		for(int y=dd; y<=dd+2;y++)
		{
			if(x==mm+3 && y==dd)
			{
				map[14][x][y].setImage(ImageRes::EMPTY); // miejsce przejscia wyglada wg kafelka o numerze np 0
				map[14][x][y].setWarp(Position(0,0,18));
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
	for(y=3;y<6;y++)
	{
		map[18][7][y].setImage(ImageRes::DARK_WALL);
		map[18][7][y].setSolid(true);

		map[18][5][y].setImage(ImageRes::FURNITURE);
		map[18][5][y].setSolid(true);

		map[18][3][y].setImage(ImageRes::DARK_WALL);
		map[18][3][y].setSolid(true);

		map[18][1][y].setImage(ImageRes::FURNITURE);
		map[18][1][y].setSolid(true);
	}

	map[18][0][0].setWarp(Position(mm+3,dd,14));
	map[18][0][0].setImage(ImageRes::EMPTY);
	

		/*//budynek finalowy - jest juz wyzej
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
			}*/
	
	
	//game.player = Player( Position(0, 2) );
	/////////////////////////////////////////////////////////////////////////////////
	//ENEMY
	/////////////////////////////////////////////////////////////////////////////////
	//poziom 1 - losowe potwory
	/*Creature losowypotwor3 = Creature(Position(45,13, 0), ImageRes::MONSTER);
	losowypotwor3.setSpeed(6); // do�� wolny
	losowypotwor3.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
	losowypotwor3.setType(Creature::Type::HOSTILE); // wrogi
	//losowypotwor3.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor3 );
	/********************************************************************************/
	srand(time(NULL));
	for(int i=0; i<3;i++)
	{
	Creature losowypotwor = Creature(Position(rand()%85+1,rand()%25+1, 0), ImageRes::MONSTER);
	losowypotwor.setSpeed(1+i); // do�� wolny
	losowypotwor.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
	losowypotwor.setType(Creature::Type::HOSTILE); // wrogi
	//losowypotwor.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	losowypotwor.addLootMoney(1);
	game.creatures.push_back( losowypotwor );
	}
	////////////////////////////////////////////////////////////////////////////////////
	//poziom 2 - losowe potwory
	for(int i=0;i<20;i++)
	{
	Creature zbir = Creature(Position(rand()%10+1,rand()%8+4, 6), ImageRes::MONSTER);
	zbir.setSpeed(10); // wolny
	zbir.setAI(Creature::AI::OFFENSIVE_FAST); // losowo b��dzi
	zbir.setType(Creature::Type::HOSTILE); // wrogi
	//zbir.addLoot( Item(L"Czapka", L"Czapka") );
	zbir.addLootMoney(1);
	game.creatures.push_back( zbir );
	}
	/*Creature zbir2 = Creature(Position(0,10, 6), ImageRes::MONSTER);
	zbir2.setSpeed(4); // wolny
	zbir2.setAI(Creature::AI::OFFENSIVE_FAST); // losowo b��dzi
	zbir2.setType(Creature::Type::HOSTILE); // wrogi
	zbir2.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	zbir2.addLootMoney(1);
	game.creatures.push_back( zbir2 );

	Creature zbir3 = Creature(Position(0,6, 6), ImageRes::MONSTER);
	zbir3.setSpeed(4); // wolny
	zbir3.setAI(Creature::AI::OFFENSIVE_FAST); // losowo b��dzi
	zbir3.setType(Creature::Type::HOSTILE); // wrogi
	zbir3.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	zbir3.addLootMoney(1);
	game.creatures.push_back( zbir3 );

	Creature zbir4 = Creature(Position(2,9, 6), ImageRes::MONSTER);
	zbir4.setSpeed(4); // wolny
	zbir4.setAI(Creature::AI::OFFENSIVE_FAST); // losowo b��dzi
	zbir4.setType(Creature::Type::HOSTILE); // wrogi
	//zbir.addLoot( Item(L"Czapka", L"Czapka") );
	zbir4.addLootMoney(1);
	game.creatures.push_back( zbir4 );*/


	////////////////////////////////////////////////////////////////////////////////////
	//poziom 3 - losowe potwory
	/*Creature losowypotwor4 = Creature(Position(35,23, 3), ImageRes::MONSTER);
	losowypotwor4.setSpeed(6); // do�� wolny
	losowypotwor4.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo
	losowypotwor4.setType(Creature::Type::HOSTILE); // wrogi
	losowypotwor4.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor4 );
	/********************************************************************************/
	for(int i=1;i<8;i++)
	{
	Creature losowypotwor5 = Creature(Position(rand()%95+1,rand()%25, 8), ImageRes::MONSTER);
	losowypotwor5.setSpeed(3); // do�� wolny
	losowypotwor5.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo 
	losowypotwor5.setType(Creature::Type::HOSTILE); // wrogi
	if(i%3==0)
	losowypotwor5.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor5 );
	}
	//////////////////////////////////////////////////////////////////////////////////
	//poziom 4 - losowe potwory
	/*Creature losowypotwor7 = Creature(Position(76,20, 12), ImageRes::MONSTER);
	losowypotwor7.setSpeed(4); // wolny
	losowypotwor7.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
	losowypotwor7.setType(Creature::Type::HOSTILE); // wrogi
	//losowypotwor7.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor7 );
	/********************************************************************************/
	for(int i=1;i<10;i++)
	{
	Creature losowypotwor8 = Creature(Position(rand()%85+1,rand()%25, 12), ImageRes::MONSTER);
	losowypotwor8.setSpeed(3); // do�� wolny
	losowypotwor8.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
	losowypotwor8.setType(Creature::Type::HOSTILE); // wrogi
	if(i%2==0)
	losowypotwor8.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor8 );
	}
	////////////////////////////////////////////////////////////////////////////////////
	//poziom 5
	for(int i=1;i<10;i++)
	{
	Creature losowypotwor9 = Creature(Position(rand()%75+1,rand()%20, 14), ImageRes::MONSTER);
	losowypotwor9.setSpeed(3); // do�� wolny
	losowypotwor9.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo b��dzi
	losowypotwor9.setType(Creature::Type::HOSTILE); // wrogi
	if(i%2==0)
	losowypotwor9.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( losowypotwor9 );
	}
	/********************************************************************************/
	//poziom 5 straznicy przed domem
	Creature warta = Creature(Position(79,5, 14), ImageRes::MONSTER);
	warta.setSpeed(2); // do�� wolny
	warta.setAI(Creature::AI::FIGHT_AND_FLEE); // losowo walczy
	warta.setType(Creature::Type::HOSTILE); // wrogi
	//straznik.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( warta );
	for(int i=6;i<=10;i++)
	{
	Creature warta2 = Creature(Position(78,i, 14), ImageRes::MONSTER);
	warta2.setSpeed(3); // do�� wolny
	warta2.setAI(Creature::AI::IDLE); // losowo b��dzi
	warta2.setType(Creature::Type::HOSTILE); // wrogi
	//straznik2.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( warta2 );
	}
	Creature warta3 = Creature(Position(79,11, 14), ImageRes::MONSTER);
	warta3.setSpeed(3); // do�� wolny
	warta3.setAI(Creature::AI::IDLE); // losowo b��dzi
	warta3.setType(Creature::Type::HOSTILE); // wrogi
	//straznik3.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( warta3 );
	/********************************************************************************/
	//straznicy w korytarzu
	for(int i=0;i<5;i++)
	{
	Creature warta4 = Creature(Position(rand()%19+1,rand()%4+8, 15), ImageRes::MONSTER);
	warta4.setSpeed(3); // do�� wolny
	warta4.setAI(Creature::AI::OFFENSIVE_FAST); // losowo b��dzi
	warta4.setType(Creature::Type::HOSTILE); // wrogi
	//straznik4.addLoot( Item(L"Badyl��", L"Przepot�ny kostur? Totalnie badyl!") );
	game.creatures.push_back( warta4 );
	}
	////////////////////////////////////////////////////////////////////////////////////
	//DIALOGI
	//////////////////////////////////////////////////////////////////////////////////

	//level 1 - rozmowa z cinkciarzem
	Creature cinkciarz = Creature(Position(8,1, 1), ImageRes::DEALER);
	
	Dialog dialog;

	dialog = Dialog();

	dialog.addNode(Dialog::START_DIALOG, L"Witaj w naszych skromny progach w�drowcze! W czym mog� s�u�y�?").
		addOption(L"Chcia�bym co� kupi�, ale nie mam pieni�dzy. Licz� na �ask�.", 1).
		addOption(L"Ach w�druj�, i szukam przyg�d. Mo�e co� mi polecicie?", 2);

	dialog.addNode(1, L"Drogi Panie! Na �ask� w tych czasach?! Musicie pyta� gdzie indziej.").
		addOption(L". . .", Dialog::END_DIALOG);

	dialog.addNode(2, L"Na terenach niedalekich jest wiele las�w i g�r. Jest co ogl�da� i gdzie szuka� zwady z miejscowymi rozb�jnikami.").
		addOption(L"O nie! Uciekam st�d!", Dialog::END_DIALOG).
		addOption(L"A� tak o to �atwo?", 20);

	dialog.addNode(20, L"Ka�dy chce pokaza� jak� ma si�� w �apie! Zw�aszcza m�odzi. Pr�buj� dosta� si� do stra�y Rogalika.").
		addOption(L"A c� to?", 200);

	dialog.addNode(200, L"Musicie by� chyba z bardzo daleka, �e o tym nie wiecie. Rz�dy nad ca�ym terenem sprawuje szlachcic. Mieszka on w najwi�kszej wiosce i jest bardzo pot�ny w�a�nie dzi�ki Rogalikowi. Podobno to jaki� prezent od mnich�w czy od dziadk�w. Kr��� r�ne historie. Ale opr�cz szlachcica i kilku stra�nik�w nikt go nie widzia�. Jest tak pilnie strze�ony!").
		addOption(L"Wasz w�adca musi by� straszny!", 201).
		addOption(L"Musicie by� wi�c zadowoleni z tak wielkiego w�adcy.", 202).
		addOption(L"Obi�o mi si� o uszy, �e macie strasznego przyw�dc�...", 201).
		addOption(L"By�em ciekaw jak tu �yjecie, pod rz�dzami szlachcica.", 203);

	dialog.addNode(201, L"Co takiego?! Mamy najlepszego w�adc� na �wiecie! Jak �miesz wypowiada� takie s�owa?!").
		addOption(L"Wybaczcie, m�wi� tylko co s�ysza�em...", 2011);
	
	dialog.addNode(2011, L"To �le us�yszeli�cie! Wyno� si�!").
		addOption(L"[uciekaj]", Dialog::END_DIALOG);

	dialog.addNode(202, L"Och! Nie jest tak pi�knie jak mog�oby si� wydawa�... Ale z�ego s�owa nikt nie powie. Wszyscy si� boj�").
		addOption(L"Co si� dzieje?", 2021);

	dialog.addNode(2021, L"Lepiej nie zawraca� si� tym g�owy, zw�aszcza, �e zaraz p�jdziecie w dalsz� podr�... a i tak za du�o ju� powiedzia�em... Bywajcie zdr�w!").
		addOption(L"Bywajcie!", Dialog::END_DIALOG);
	
	dialog.addNode(203, L"Bardzo dobrze! W ko�cu nadesz�y czasy, w kt�rych cz�owiek czuje si� bezpiecznie.").
		addOption(L"S�ysza�em co innego...", 2031);

	dialog.addNode(2031, L"Musieli�cie �le zrozumie�, drogi go�ciu.").
		addOption(L". . .", Dialog::END_DIALOG);

	cinkciarz.addDialog(dialog);

	cinkciarz.setType(Creature::Type::DIALOG);
	game.creatures.push_back( cinkciarz );

	/************************************************************************************************************/
	//level 1 - rozmowa z rzemie�lnikiem
	Creature rzemieslnik = Creature(Position(6,5, 2), ImageRes::DEALER);
	
	Dialog dialog0;

	dialog0 = Dialog();

	dialog0.addNode(Dialog::START_DIALOG, L"Co Ci� do mnie sprowadza?").
		addOption(L"S�ysza�em, �e �atwo u Was o b�jk�. Okradli mnie przed wiosk� i niestety nic nie mam do obrony... Nie wiem jak sobie poradzi�.", 3).
		addOption(L"Macie jakie� narz�dzia do obrony?", 4);

	dialog0.addNode(3, L"Oj dzieciaku! Nie poradzisz sobie w �yciu! Musisz by� bardziej uwa�ny. Na	pocz�tek mog� da� ci drewniany kij, bo jak s�dz� pieni�dzy te� nie masz.").
		addIfDontHave(Item(L"Kijek", L"kijek").setProperty(Item::WEAPON, 0.3),game.player).
		addOption(L"Dzi�kuj� za pomoc.", 30);
	
	dialog0.addNode(30, L"Id� i uwa�aj na siebie dzieciaku.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog0.addNode(4, L"Takich rzeczy jest u mnie pod dostatkiem. Co was interesuje i w jakiej cenie?").
		addOption(L"Ale ja niestety nie mam pieni�dzy... Okradli mnie.", 40);

	dialog0.addNode(40, L"Za darmo nic ma.").
		addOption(L"A mo�e co� starego, ledwo nadaj�ce si� do u�ytku?", 401).
		addOption(L"Mo�e macie co� zb�dnego? Lub z nadmiarem?", 402);

	dialog0.addNode(401, L"Nie obra�ajcie mnie! U mnie nic nie jest do wyrzucenia!").
		addOption(L"Przepraszam, nie to mia�em na my�li...", 4010);

	dialog0.addNode(4010, L"Jeszcze musisz si� wiele nauczy�. �ap kija i ju� id�.").
		addIfDontHave(Item(L"Kijek", L"kijek").setProperty(Item::WEAPON, 0.3),game.player).
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	dialog0.addNode(402, L"Hmm my�l�, �e mog� pom�c... Prosz�, oto drewniany kij.").
		addIfDontHave(Item(L"Kijek", L"kijek").setProperty(Item::WEAPON, 0.3),game.player).
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	 
	rzemieslnik.addDialog(dialog0);

	rzemieslnik.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik );

	/************************************************************************************************************/
	//level 1 - rozmowa z kowalem
	Creature kowal = Creature(Position(1,1, 0), ImageRes::DEALER);
	Dialog dialog1;

	dialog1 = Dialog();
	int size = game.player.InventorySize()+100;
	dialog1.addNode(Dialog::START_DIALOG, L"Czego tu szukasz?").
		addOption(L"Chcia�em zobaczy� czym si� tutaj zajmujecie.", 5).
		addOption(L"Ale� jest Pan mi�y!", 6).
		addOption(L"Handel", 29);
	dialog1.addNode(29,L"Panie chcesz cos kupic czy sprzedac").
		addOption(L"Kupic",30).
		addOption(L"Sprzedac",31).
		addOption(L"Rozmyslilem sie", Dialog::END_DIALOG);
	dialog1.addNode(31,L"Pokaz Panie co posiadasz").
		showWhatYouGot(game.player).
		addOption(L"Wyjscie ",Dialog::END_DIALOG);
	for(int i = 100 ; i <= size ; i++)
	{
		dialog1.addNode(i,L"Dzieki Panie").
		addTakeItem(game.player,i).
		addOption(L"Wyjscie " , Dialog::END_DIALOG);
	}
	dialog1.addNode(30, L"Zbroje tylko u mnie !!!").
		addOptionIfHasMoney(5, L"Tania zbroja sk�rzana (5 monet)", 301).
        addOptionIfHasMoney(15, L"Zwyk�a zbroja z br�zu (15 monet)", 302).
        addOptionIfHasMoney(25, L"Wytrzyma�a zbroja �elazna (25 monet)", 303).
        addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Dowidzenia !!!", Dialog::END_DIALOG); 
	dialog1.addNode(301,L"Prosz�, oto twoja zborja. Niech ci s�u�y.").
		addGiveItem( Item(L"Zbroja skorzana",L"Tania zbroja").setProperty(Item::ARMOR,0.1)).
		addTakeCoins(5).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog1.addNode(302,L"Prosz�, oto twoja zborja. Niech ci s�u�y.").
		addGiveItem( Item(L"Zbroja z br�zu",L"Zbroja stworzona z br�zu").setProperty(Item::ARMOR,0.3)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog1.addNode(303,L"Prosz�, oto twoja zborja. Niech ci s�u�y.").
		addGiveItem( Item(L"Wytrzyma�a zbroja �elazna",L"Bardzo wytrzyma�a zbroja �elazna").setProperty(Item::ARMOR,0.5)).
		addTakeCoins(25).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog1.addNode(6, L"Wyjd�, nie mam nastroju do rozm�w!").
		addOption(L"[uciekaj]", Dialog::END_DIALOG);
	
	dialog1.addNode(5, L"Jak wida� - tym czym ma si� zajmowa� kowal.").
		addOption(L"Widz�, �e jeste�cie zm�czeni.", 50);
		//addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog1.addNode(50, L"Tak. Tyle roboty, �e dnia nie starcza.").
		addOption(L"W takim razie nie przeszkadzam.", Dialog::END_DIALOG). //KONIEC
		addOption(L"No tak, mo�e by� ci�ko. Jeszcze kiedy jest Pan sam.", 501);

	dialog1.addNode(501, L"Ach, tak. W Ty dok�d si� wybierasz?").
		addOption(L"Id� do domu Szlachcica. S�ysza�em r�ne historie. Zaciekawi�y mnie.", 5010);

	dialog1.addNode(5010, L"Do Szlachcica... �ap podkow�! Przyda Ci si� du�o szcz�cia").
		addGiveItem(Item(L"Podkowa", L"Podkowa").setProperty(Item::DUMB, 0.1)).
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	kowal.addDialog(dialog1);

	kowal.setType(Creature::Type::DIALOG);
	game.creatures.push_back( kowal );

	/************************************************************************************************************/
	////level 1 - rozmowa z medrcem
	Creature medrzec = Creature(Position(5,2, 4), ImageRes::DEALER);
	
	Dialog dialog2;

	dialog2 = Dialog();

	dialog2.addNode(Dialog::START_DIALOG, L"Wyczuwam now� energi� w mej przestrzeni! Och! Podr�niku! Czego szukasz w naszych stronach?").
		addOption(L"Nigdy nie mia�em styczno�ci z eliksirami. By�em ciekaw co tu jest...", 7);

	dialog2.addNode(7, L"I pewnie chcia�by� co� kupi�?").
		addOption(L"Niestety nie mam za co...", 71).
		addOption(L"Nie, w�a�ciwie to ju� wychodz�.", 72);

	dialog2.addNode(71, L"Och! Jako� na to zaradzimy. Jako nowy go�� przyjmij ode mnie prezent - eliksir �ycia.").
		addGiveItem( Item(L"Eliksir �ycia", L"Przywraca pe�ni� si�").setProperty(Item::LIFEPOTION) ).
		addOption(L"A co to?", 711).
		addOption(L"Chyba wiem co to jest.", 712);

	dialog2.addNode(711, L"Kiedy b�dziesz czu�, �e tracisz si�y - napij si�.").
		addOption(L". . .",Dialog::END_DIALOG); //KONIEC

	dialog2.addNode(712, L"W takim razie b�dziesz wiedzia� kiedy tego u�y�.").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	dialog2.addNode(72, L"W takim razie do zobaczenia!").
		addOption(L". . .", Dialog::END_DIALOG);//KONIEC

	medrzec.addDialog(dialog2);

	medrzec.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec );

	/************************************************************************************************************/
	////level 2 - rozmowa z pijakiem
	Creature pijak = Creature(Position(69,10+(rand()%3), 5), ImageRes::DEALER);
	
	Dialog dialog3;

	dialog3 = Dialog();

	dialog3.addNode(Dialog::START_DIALOG, L"Hej! Przyjacielu! Mo�e si� dosi�dziesz?").
		addOption(L"Nie, dzi�kuj�! Nie b�d� siedzia� z pijakiem...", 8).
		addOption(L"Przepraszam, ale musz� czym pr�dzej dosta� si� do Waszego Pana.", 9);

	dialog3.addNode(8, L"Phi! Wa�niak...").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog3.addNode(9, L"Uuu... To jeszcze d�uga droga przed tob�, towarzyszu.").
		addOption(L"Znasz jaki� skr�t?", 90);

	dialog3.addNode(90, L"Heh... mo�e i znam. (czkawka)").
		addOption(L"Zap�ac� Ci.",900);

	dialog3.addNode(900, L"A masz co� do picia? Troch� boli mnie g�owa...").
		addOption(L"Mo�e wina?", 9001).
		addOption(L"Niestety nie mam nic.",9002).
		addOption(L"Oszala�e�?! Nie wiem w og�le po co z Tob� rozmawiam. Sam wybior� drog�. Na pewno trafi�.", Dialog::END_DIALOG);

	dialog3.addNode(9001, L"Ooo...czywi�cie nie odm�wi�!").
		addOption(L"Teraz powiesz mi, kt�r� drog� mam i��?", 90010);

	dialog3.addNode(90010, L"Pewnie! Ale chyba napijesz si� ze mn�?").
		addOption(L"Jasne...", 90011);

	dialog3.addNode(90011, L"Je�li wybierzesz drog� na lewo, to b�dziesz musia� zap�aci� za jej pzej�cie i jest troch� d�u�sza, ale za to bez przeszk�d. Je�li jednak p�jdziesz na prawo... S�ysza�em o zb�jniku, kt�ry chodzi z wilkiem i ma doskona�y miecz! Przyda�by Ci si�!").
		addOption(L"Dzi�kuj�! Bywaj zdr�w!", 90012);
	dialog3.addNode(90012, L"Wst�p jeszcze kiedy�!").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog3.addNode(9002, L"Uuu to szkoda. Lubi� czasami wypi� co� mocniejszego. Lepiej mi si� my�li.").
		addOption(L"Hmm... Moment. Mo�e wina?", 9001);

	pijak.addDialog(dialog3);

	pijak.setType(Creature::Type::DIALOG);
	game.creatures.push_back( pijak );

	/************************************************************************************************************/
	////level 3 - rozmowa z rzemieslnikiem
	Creature rzemieslnik2 = Creature(Position(5,3, 9), ImageRes::DEALER);
	
	Dialog dialog4;

	dialog4 = Dialog();

	dialog4.addNode(Dialog::START_DIALOG, L"W czym mog� pom�c?").
		addOption(L"Szukam odzienia na g�owe.", 10).
		addOption(L"Tylko si� rozgl�dam.", Dialog::END_DIALOG);

	dialog4.addNode(10, L"Nie mog�e� lepiej trafi� , tylko u mnie najlepsze he�my!!!").
		addOption(L"Poka� wa�� co posiadasz.", 101).
		addOption(L"Rozmy�li�em si�.", Dialog::END_DIALOG);

	dialog4.addNode(101, L"Mam tego do�� sporo, rozejrzyj si�, a kiedy co� znajdziesz - powiedz.").
		addOptionIfHasMoney(5, L"Czapka wie�niaka (5 monet)", 102).
        addOptionIfHasMoney(15, L"He�m bojowy (15 monet)", 103).
        addOptionIfHasMoney(25, L"Diadem Zeusa (25 monet)", 104).
        addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Dowidzenia !!!", Dialog::END_DIALOG); 
	dialog4.addNode(102,L"Trzymaj , oto twoj nowy he�m. Zapraszam ponownie !!!").
		addGiveItem( Item(L"Czapka wie�niaka",L"Tanie odzienie").setProperty(Item::HELMET,0.1)).
		addTakeCoins(5).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog4.addNode(103,L"Trzymaj , oto twoj nowy he�m. Zapraszam ponownie !!!").
		addGiveItem( Item(L"He�m bojowy",L"Metalowy solidny he�m").setProperty(Item::HELMET,0.3)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog4.addNode(104,L"Trzymaj , oto twoj nowy he�m. Zapraszam ponownie !!!").
		addGiveItem( Item(L"Didaem Zeusa",L"Wykuty przez samego Hefajstosa").setProperty(Item::HELMET,0.5)).
		addTakeCoins(25).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);

	rzemieslnik2.addDialog(dialog4);

	rzemieslnik2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik2 );

	/************************************************************************************************************/
	////level 3 - rozmowa z kolesiem
	Creature koles = Creature(Position(30,postaw, 8), ImageRes::DEALER);
	
	Dialog dialog5;

	dialog5 = Dialog();

	dialog5.addNode(Dialog::START_DIALOG, L"Hej, ty! Chyba nie jeste� st�d, co?").
		addOption(L"Nie, trafi�em tu przypadkiem!", 12).
		addOption(L"Zgadza si�, powiesz mi jak trafi� do domu Szlachcica?", 13);

	dialog5.addNode(12, L"Hehe! Przypadkiem to mo�esz z�apa� guza!").
		addOption(L"[walcz]", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	dialog5.addNode(13, L"Wszyscy chc� si� czego� dowiedzie�.").
		addOption(L"Czyli si� nie dowiem? Mog� zap�aci�", 130).
		addOption(L"Nie b�d� taki wa�ny", 131); 

	dialog5.addNode(130, L"Nie chc� Twoic pieni�dzy, pewnie kradzione.").
		addOption(L"Nie, to nie. Jako� trafi�.", Dialog::END_DIALOG); //KONIEC
		//addOption(L"", Dialog::END_DIALOG); //KONIEC I POJEDYNEK
	dialog5.addNode(131, L"Zaraz Ci poka�� jaki jestem wa�ny!").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	koles.addDialog(dialog5);

	koles.setType(Creature::Type::DIALOG);
	game.creatures.push_back( koles );

	/************************************************************************************************************/
	////level 3 - rozmowa z medrcem
	Creature medrzec2 = Creature(Position(6,2, 10), ImageRes::DEALER);
	
	Dialog dialog6;

	dialog6 = Dialog();

	dialog6.addNode(Dialog::START_DIALOG, L"Czego szukasz, drogi w�drowcze?").
		addOption(L"Potrzebuj� czego� na wzmocnienie.", 14).
		addOption(L"Nic konkretnego.", 15).
		addOption(L"Panie potrzebuje broni , czy nie wiecie gdzie mo�na j� dosta�?",163);
	dialog6.addNode(163,L"Moje dostawy skonczy�y si� ju� dawno temu , zosta�o tylko to. Rzu� okiem.").
		addOptionIfHasMoney(5, L"Magiczna r�dzka(5 monet)", 102).
        addOptionIfHasMoney(15, L"Bojowy Kij (15 monet)", 103).
        addOptionIfHasMoney(25, L"Magiczny Kij Gandalfa (25 monet)", 104).
		addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Dowidzenia !!!", Dialog::END_DIALOG);
	dialog6.addNode(102,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Magiczna ro�dzka",L"Tania 'magiczna' ro�dzka").setProperty(Item::WEAPON,0.1)).
		addTakeCoins(5).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog6.addNode(103,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Bojowy Kij",L"Nie jeden potw�r nim oberwie").setProperty(Item::WEAPON,0.3)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog6.addNode(104,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Magiczny Kij Gandalfa",L"Sam Sauron sie go obawia").setProperty(Item::WEAPON,0.5)).
		addTakeCoins(25).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);

	dialog6.addNode(14, L"Hmm dobrym rozwi�zaniem b�dzie eliksir �ycia. Zobacz co jeszcze mam.").
		addOptionIfHasMoney(35, L"Kolorowy piasek (20 monet)", 105).
		addOptionIfHasMoney(45, L"Eliksir �yca (15 monet)", 106).
		addOptionIfHasMoney(55, L"Proszek sypiajacy (25 monet)", 107).
		addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Do widzenia!", Dialog::END_DIALOG);
	dialog6.addNode(105,L"Dobry wyb�r panie! Prosze piasek jest Tw�j.").
		addGiveItem( Item(L"Kolorowy piasek",L"Odwraca uwag�.").setProperty(Item::MAGICSAND)).
		addTakeCoins(20).
		addOption(L"W takim razie bior�!", 140);
		//addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog6.addNode(106,L"Dobry wyb�r panie! Prosze eliksir jest Tw�j.").
		addGiveItem( Item(L"Eliksir �ycia",L"B�dziesz mia� wi�cej energii do dzia�ania!").setProperty(Item::LIFEPOTION)).
		addTakeCoins(15).
		//addOption(L"Dziekuje!", Dialog::END_DIALOG);
		addOption(L"W takim razie bior�!", 140);

	dialog6.addNode(107,L"Dobry wyb�r panie! Proszek jest Tw�j.").
		addGiveItem( Item(L"Proszek usypiaj�cy",L"Po nim ka�dy ma \"kolorowe sny\"").setProperty(Item::SLEEPDUST)).
		addTakeCoins(25).
		//addOption(L"Dziekuje!", Dialog::END_DIALOG);
		addOption(L"W takim razie bior�!", 140);

	dialog6.addNode(140, L"A mo�e by�by� zainteresowany czym� jeszcze?").
		addOption(L"Nie, dzi�kuj�. My�l�, �e na razie wystarczy.", Dialog::END_DIALOG).
		addOption(L"Macie co� do zaproponowania?", 1400);

	dialog6.addNode(1400, L"Doskona�y z�oty proszek usypiaj�cy. Ka�demu w ko�cu si� przydaje. Nic nowego nie wyci�gn�. Widzicie co tu mam.").
		addOption(L"Hmm. Mo�e innym razem. Dzi�kuj�!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Skoro tak twierdzicie to mo�e i mnie si� przyda.",1401);

	dialog6.addNode(1401, L"Z pewno�ci�.").
		addOptionIfHasMoney(55, L"Proszek sypiajacy (25 monet)", 107).
		addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Do widzenia!", Dialog::END_DIALOG);

	dialog6.addNode(15, L"Mo�e m�g�bym co� zaproponowa�?").
		addOption(L"Z ch�ci� pos�ucham.", 1400);

	medrzec2.addDialog(dialog6);

	medrzec2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec2 );

	/************************************************************************************************************/
	////level 3 - rozmowa z lud�mi w barze
	Creature klient = Creature(Position(3,3, 11), ImageRes::DEALER);
	Dialog dialog14;
	dialog14 = Dialog();
	dialog14.addNode(Dialog::START_DIALOG, L"To miejsce jest zaj�te!").
		addOption(L". . .", Dialog::END_DIALOG);	
	klient.addDialog(dialog14);
	klient.setType(Creature::Type::DIALOG);
	game.creatures.push_back( klient );
	/**********************************************/
	Creature klient2 = Creature(Position(4,5, 11), ImageRes::DEALER);
	Dialog dialog15;
	dialog15 = Dialog();
	dialog15.addNode(Dialog::START_DIALOG, L"To miejsce jest zaj�te!").
		addOption(L". . .", Dialog::END_DIALOG);
	klient2.addDialog(dialog15);
	klient2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( klient2 );

	/***********************************************/
	Creature barman = Creature(Position(8, 4, 11), ImageRes::DEALER);
	Dialog dialog16;
	dialog16=Dialog();
	dialog16.addNode(Dialog::START_DIALOG, L"Co� poda�?").
		addOption(L"Nie, dzi�kuj�", Dialog::END_DIALOG).
		addOption(L"Piwo.", 111);
	dialog16.addNode(111, L"Ju� si� robi.").
		addGiveItem(Item(L"Piwo", L"Piwo").setProperty(Item::DUMB, 0.1)).
		addOption(L". . .", Dialog::END_DIALOG);
	barman.addDialog(dialog16);
	barman.setType(Creature::Type::DIALOG);
	game.creatures.push_back(barman);

	/************************************************************************************************************/
	////level 3 - rozmowa ze stra�nikiem
	Creature straznik = Creature(Position(98,postaw2, 8), ImageRes::DEALER);
	
	Dialog dialog7;

	dialog7 = Dialog();

	dialog7.addNode(Dialog::START_DIALOG, L"Czego?").
		addOption(L"Czy otworzycie bramy?", 16).
		addOption(L"Wypu�� mnie! Chc� wyj��!", 162);
		
	dialog7.addNode(16, L"To zale�y jak poprosisz! (�miech)").
		addOption(L"Mam zap�aci�?",161).
		addOption(L"Pewnie chcecie pieni�dzy? Otwieranie bramy jest waszym obowi�zkiem!", 162);
		
	dialog7.addNode(161, L"My�l�, �e powinno wystarczy�.").
		addOption(L"[zaplac]", Dialog::END_DIALOG);//KONIEC

	dialog7.addNode(162, L"Mo�e troch� szacunku! Co?!").
		addOption(L"Niby dlaczego?", 1620);

	dialog7.addNode(1620, L"Szukasz niepotrzebnego problemu, ch�opaczku.").
		addOption(L"Mam zap�aci�?", 161).
		addOption(L"Ch�opaczku?! Jak �miesz?!", Dialog::END_DIALOG); //KONIEC I POJEDYNEK

	straznik.addDialog(dialog7);

	straznik.setType(Creature::Type::DIALOG);
	game.creatures.push_back( straznik );

	/************************************************************************************************************/
	////level 4 - rozmowa z kolesiem
	Creature koles2 = Creature(Position(33,postaw3, 12), ImageRes::DEALER);
	
	Dialog dialog8;

	dialog8 = Dialog();

	dialog8.addNode(Dialog::START_DIALOG, L"Masz co� do jedzenia?").
		addOption(L"Nie, nie mam.", Dialog::END_DIALOG).
		addOption(L"Co� mog�oby si� znale��.", 17);
		
	dialog8.addNode(17, L"Podzielisz si�?").
		addOption(L"Widz�, �e potrzebujesz bardziej ni� ja.",171).
		addOption(L"Mog� Ci sprzeda�. Potrzebuj� pini�dzy wi�c ka�da moneta si� przyda.", 172);

	dialog8.addNode(171, L"Och, jeste�cie tacy mi�osierni. Przyjmijcie w zamian eliksir �ycia.").
		addOption(L"[zaplac]", Dialog::END_DIALOG);//KONIEC

	dialog8.addNode(172, L"No dobrze, mam kilka.").
		addOption(L"[zaplac]", Dialog::END_DIALOG); //KONIEC

	koles2.addDialog(dialog8);

	koles2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( koles2 );

	/************************************************************************************************************/
	////level 4 - rozmowa ze zbieraczem narzedzi
	Creature zbieracz = Creature(Position(4,4, 13), ImageRes::DEALER);
	
	Dialog dialog9;

	dialog9 = Dialog();

	dialog9.addNode(Dialog::START_DIALOG, L"Zapraszam w me skromne progi!").
		addOption(L"O przepraszam, nie wiedzia�em, �e kto� tu mieszka.", 18);
		
	dialog9.addNode(18, L"Nie dziwi mnie to, w takim miejscu.").
		addOption(L"Nie chc� przeszkadza�, wszystkiego dobrego!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Czym si� zajmujecie tutaj?", 180);

	dialog9.addNode(180, L"G��wnie to zbieraniem narz�dzi i udoskonalaniem ich.").
		addOption(L"Czyli si� nie nudzicie.", 181);

	dialog9.addNode(181, L"Je�li macie co� do sprzeda�y, to z ch�ci� kupi�.").
		addOption(L"W�a�ciwie to nic czego chcia�bym si� pozby�.", 1811).
		addOption(L"Hmm... co� chyba mam.",1812);

	dialog9.addNode(1811, L"Szkoda, gdyby� jednak si� zdecydowa�, wiesz gdzie mnie szuka�.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	
	dialog9.addNode(1812, L"�wietnie! A dok�d si� wybieracie?").
		addOption(L"Przed siebie szuka� przyg�d.", 18121).
		addOption(L"Do Waszego Pana. S�ysza�em r�ne historie o nim i jego panowaniu.", 18122);

	dialog9.addNode(18121, L"W takim razie szerokiej drogi").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog9.addNode(18122, L"Ach! B�d� ostro�ny. W domu szlachcica mieszka podobno straszny potw�r. Nie widzia�em na w�asne oczy, ale czasami bywam w wiosce i ludzie gadaj�. My�l�, �e czego� pilnuje.").
		addOption(L"Dzi�kuj�. B�d� mia�, jak to m�wi�, oczy dooko�a g�owy.", Dialog::END_DIALOG); //KONIEC

	zbieracz.addDialog(dialog9);

	zbieracz.setType(Creature::Type::DIALOG);
	game.creatures.push_back( zbieracz );

	/************************************************************************************************************/
	////level 5 - rozmowa z rzemieslnikiem
	Creature rzemieslnik3 = Creature(Position(2,6, 17), ImageRes::DEALER);
	
	Dialog dialog10;

	dialog10 = Dialog();

	dialog10.addNode(Dialog::START_DIALOG, L"Co b�dzie?").
		addOption(L"Nic nie chc�.", Dialog::END_DIALOG).
		addOption(L"Chcia�bym kupi� zbroje.", 21);
	dialog10.addNode(21, L"Nie wygl�dacie na kogo� kto ma tyle pieni�dzy.").
		addOption(L"Pozory myl�.", 211).
		addOption(L"Prosz� sobie oszcz�dzi� takich komentarzy..",212);
	dialog10.addNode(211, L"Oczywi�cie zaraz znajd� co� odpowiedniego.").
		addOptionIfHasMoney(5, L"Tania zbroja sk�rzana (5 monet)", 301).
        addOptionIfHasMoney(15, L"Zwyk�a zbroja z br�zu (15 monet)", 302).
        addOptionIfHasMoney(25, L"Wytrzyma�a zbroja �elazna (25 monet)", 303).
		addOptionIfHasMoney(25, L"Kolczuga Bilba(LOTR) (125 monet)", 304).
        addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Dowidzenia !!!", Dialog::END_DIALOG); 
	dialog10.addNode(301,L"Prosz�, oto twoja zbroja. Niech ci s�u�y.").
		addGiveItem( Item(L"Zbroja skorzana",L"Tania zbroja").setProperty(Item::ARMOR,0.1)).
		addTakeCoins(5).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog10.addNode(302,L"Prosz�, oto twoja zbroja. Niech ci s�u�y.").
		addGiveItem( Item(L"Zbroja z br�zu",L"Zbroja stworzona z br�zu").setProperty(Item::ARMOR,0.3)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog10.addNode(303,L"Prosz�, oto twoja zbroja. Niech ci s�u�y.").
		addGiveItem( Item(L"Wytrzyma�a zbroja �elazna",L"Bardzo wytrzyma�a zbroja �elazna").setProperty(Item::ARMOR,0.5)).
		addTakeCoins(25).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog10.addNode(304,L"Zbroja ktora nosil Frodo , prosze !! ").
		addGiveItem( Item(L"Kolczuga Bilba",L"Kultowa kolczuaga").setProperty(Item::ARMOR,0.9)).
		addTakeCoins(125).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	rzemieslnik3.addDialog(dialog10);

	rzemieslnik3.setType(Creature::Type::DIALOG);
	game.creatures.push_back( rzemieslnik3 );

	/************************************************************************************************************/
	////level 5 - rozmowa z medrcem
	Creature medrzec3 = Creature(Position(4,4, 18), ImageRes::DEALER);
	
	Dialog dialog11;

	dialog11 = Dialog();
	
	dialog11.addNode(Dialog::START_DIALOG, L"Co przygotowa�?").
		addOption(L"Potrzebuj� eliksiru �ycia.", 22).
		addOption(L"Sam nie wiem czego chc�.", 23);
		
	dialog11.addNode(22, L"Tylko go nie marnuj...").
		addOption(L"Postaram si�.", 222); //KONIEC

	dialog11.addNode(23, L"Wr�� kiedy b�dziesz czego� potrzebowa�.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog11.addNode(222, L"Mo�e chcesz co� jeszcze?").
		addOption(L"Potrzebuj� jakiej� \"magicznej sztuczki\".", 26).
		addOption(L"Wybieram sie do szlachcica. Du�o s�ysza�em i my�l�, �e przyda�aby mi si� jaka� \"magiczna sztuczka\". Mogliby�cie mi jako� pom�c?", 261);
		
	dialog11.addNode(26, L"Niewiele mi to m�wi. Musisz si� bardziej postara�.").
		addOption(L"Id� do szlachcica.", 261).
		addOption(L"Nie powinno Was to interesowa�.",  262);

	dialog11.addNode(262, L"W takim razie nie mog� pom�c.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog11.addNode(261, L"Ach! Do szlachcica. Pewnie zainteresowa� Ci� Rogalik.").
		addOption(L"Pewnie jak wielu innych.", 2611).
		addOption(L"To ju� nie Wasz sprawa.", 2612);


	dialog11.addNode(2611, L"Niech pomy�l�... niewiele tego mam, wi�c mog� zaproponowa� najwy�ej kolorowy piasek, ale zobacz co tu jeszcze jest i wybierz co�.").
		//dialog11.addNode(163,L"Moje dostawy skonczy�y si� ju� dawno temu , zosta�o tylko to. Rzu� okiem.").
		addOptionIfHasMoney(5, L"Magiczna r�dzka(5 monet)", 102).
        addOptionIfHasMoney(15, L"Bojowy Kij (15 monet)", 103).
        addOptionIfHasMoney(25, L"Magiczny Kij Gandalfa (25 monet)", 104).
		addOptionIfHasMoney(35, L"Kolorowy piasek (20 monet)", 105).
		addOptionIfHasMoney(45, L"Eliksir �yca ( 15 monet)", 106).
		addOptionIfHasNotMoney(5, L"Nie posiadam pieniedzy . Do widzenia!", Dialog::END_DIALOG);
	dialog11.addNode(102,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Magiczna ro�dzka",L"Tania 'magiczna' ro�dzka").setProperty(Item::WEAPON,0.1)).
		addTakeCoins(5).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog11.addNode(103,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Bojowy Kij",L"Nie jeden potw�r nim oberwie").setProperty(Item::WEAPON,0.3)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog11.addNode(104,L"Dobry wyb�r panie! Prosze bro� jest Twoja.").
		addGiveItem( Item(L"Magiczny Kij Gandalfa",L"Sam Sauron sie go obawia").setProperty(Item::WEAPON,0.5)).
		addTakeCoins(25).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog11.addNode(105,L"Dobry wyb�r panie! Prosze piasek jest Tw�j.").
		addGiveItem( Item(L"Kolorowy piasek",L"Odwraca uwag�.").setProperty(Item::MAGICSAND)).
		addTakeCoins(20).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
	dialog11.addNode(106,L"Dobry wyb�r panie! Prosze eliksir jest Tw�j.").
		addGiveItem( Item(L"Eliksir �ycia",L"B�dziesz mia� wi�cej energii do dzia�ania!").setProperty(Item::LIFEPOTION)).
		addTakeCoins(15).
		addOption(L"Dziekuje!", Dialog::END_DIALOG);
		//addOption(L"Mam nadziej�, �e i ja si� dowiem.", Dialog::END_DIALOG); //KONIEC

	dialog11.addNode(2612, L"Nie mog� pom�c je�li nie wiem o co chodzi.").
		addOption(L"Hmm... no dobrze. Zainteresowa� mnie i to bardzo. Pomo�ecie?", 2611);
		
	medrzec3.addDialog(dialog11);

	medrzec3.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec3 );

	/************************************************************************************************************/
	////level 5 - rozmowa z cinkcarzem
	Creature cinkciarz2 = Creature(Position(5,3, 16), ImageRes::DEALER);
	
	Dialog dialog12;

	dialog12 = Dialog();

	dialog12.addNode(Dialog::START_DIALOG, L"S�u�� uprzejmie!").
		addOption(L"Chcia�bym dosta� si� do Waszego Pana, niestety nie znam drogi.", 24).
		addOption(L"Gdzie znajd� dom Szlachcica?", 25);
		
	dialog12.addNode(25, L"Przy ko�cu wioski.").
		addOption(L"Dzi�kuj�!", 250);

	dialog12.addNode(250, L"Bad� ostro�ny, kiedy tam wejdziesz.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog12.addNode(24, L"Musisz i�� do ko�ca wioski. Na pewno rozpoznasz jego dom.").
		addOption(L"Dzi�kuj�!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Podobno mieszka w nim jaki� straszny potw�r, to prawda?", 240);

	dialog12.addNode(240, L"O tak! Przyda�aby Ci si� jaka� czarodziejska sztuczka. Wybierz si� do m�drca. Na pewno co� wymy�li. Przyda Ci sie pochodnia, kt�r� znajdziesz na pocz�tku korytarza prowadz�cego do miejsca gdzie znajduje sie Rogalik.").
		addOption(L"Ale czym j� rozpal�?", 2401).
		addOption(L"Zapami�tam te wskaz�wki.", Dialog::END_DIALOG);

	dialog12.addNode(2401, L"Mam co� takiego jak rozpa�ka do ognia.").
		addOption(L"Z ch�ci� kupi�!", Dialog::END_DIALOG). //KONIEC
		addOption(L"Chcesz mnie naci�gn��!", 2402);

	dialog12.addNode(2402, L"B�dziesz �a�owa� i jeszcze po ni� wr�cis!").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC
	
	dialog12.addNode(212, L"Ka�dy cwany. Zaraz znajd� co� odpowiedniego.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	cinkciarz2.addDialog(dialog12);

	cinkciarz2.setType(Creature::Type::DIALOG);
	game.creatures.push_back( cinkciarz2 );

	/************************************************************************************************************/
	////level 5 - rozmowa z medrcem (powrot)
	/*Creature medrzec4 = Creature(Position(4,4, 18), ImageRes::DEALER);
	
	Dialog dialog13;

	dialog13 = Dialog();

	dialog13.addNode(Dialog::START_DIALOG, L"Widz�, �e o czym� sobie przypomnia�e�!").
		addOption(L"Potrzebuj� jakiej� <<magicznej sztuczki>>.", 26).
		addOption(L"Wybieram sie do szlachcica. Du�o s�ysza�em i my�l�, �e przyda�aby mi si� jaka� <<magiczna sztuczka>>. Mogliby�cie mi jako� pom�c?", 261);
		
	dialog13.addNode(26, L"Niewiele mi to m�wi. Musisz si� bardziej postara�.").
		addOption(L"Id� do szlachcica.", 261).
		addOption(L"Nie powinno Was to interesowa�.",  262);

	dialog13.addNode(262, L"W takim razie nie mog� pom�c.").
		addOption(L". . .", Dialog::END_DIALOG); //KONIEC

	dialog13.addNode(261, L"Ach! Do szlachcica. Pewnie zainteresowa� Ci� Rogalik.").
		addOption(L"Pewnie jak wielu innych.", 2611).
		addOption(L"To ju� nie Wasz sprawa.", 2612);


	dialog13.addNode(2611, L"Niech pomy�l�... proponuj� kolorowy piasek. O jego w�a�ciwo�ciach nie mog� m�wi�, ka�dy na sw�j spos�b wie kiedy i jak go u�y�.").
		addOption(L"Mam nadziej�, �e i ja si� dowiem.", Dialog::END_DIALOG); //KONIEC

	dialog13.addNode(2612, L"Nie mog� pom�c je�li nie wiem o co chodzi.").
		addOption(L"Hmm... no dobrze. Zainteresowa� mnie i to bardzo. Pomo�ecie?", 2611);

	medrzec4.addDialog(dialog13);

	medrzec4.setType(Creature::Type::DIALOG);
	game.creatures.push_back( medrzec4 );*/
}

//void GameBuilder::loadFromFile() { }
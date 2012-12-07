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

	map.reserve(15);
	map.insert(map.begin() + 0, emptyTerrainLevel(30, 20, 0)); // tworze poziom o numerze np. 0 i o wymiarach np. 20x20
	for(int x=0;x<map[0].size();x++)
	{
		for(int y=0;y<map[0][x].size();y++)
		{
			map[0][x][y].setImage(ImageRes::SAND); //pobiera obrazek, z podanego obrazka tiles.png o numerze np.2
		}
	}

	game.player = Player( Position(0, 2) );
	game.npcs.push_back( NPC(Position(0,1, 0), ImageRes::DEALER) );
	game.npcs.push_back( NPC(Position(8,1, 1), ImageRes::DEALER) );// mo¿e by warto by³o jakiœ NPCBuilder 
	game.enemies.push_back( Enemy(Position(10,5, 0)) ); // mo¿e by warto by³o jakiœ EnemyBuilder 
}

//void GameBuilder::loadFromFile() { }
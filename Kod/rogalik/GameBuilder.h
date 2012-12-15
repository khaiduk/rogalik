#pragma once
#include "Game.h"
class GameBuilder
{
private:
	Game game;
	std::vector< std::vector<Tile> > emptyTerrainLevel(int width, int height, int level);
public:
	Game& getGame();
	void generateNewGame();
	//void loadFromFile();
	//void saveGame(const Game&); // tutaj nie jestemn pewien
};

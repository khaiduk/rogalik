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
	/**
	** Funkcja budujaca domek 
	** @param map - mapa na ktorej rysujemy
	** @param level - level na ktorym budujemy
	** @param x - wspolrzedna x wejscia
	** @param y - wspolrzedna y wejscia 
	** @param var - domek o wygl¹dzie spod numeru var
	**/
	void buildHouse(std::vector< std::vector< std::vector<Tile> > > &map,int level , int x , int y,int var,int lvl);
	void buildFurniture(std::vector< std::vector< std::vector<Tile> > > &map,int level , int x , int y);
};


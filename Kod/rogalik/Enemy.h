#pragma once
#include "Creature.h"
#include "Player.h"

class Enemy :public Creature
{
public:
	Enemy(const Position pos = Position(0,0));

	/**
	 * Wykonuje krok symulacji
	 */
	void step(float dt, const Terrain& terrain, Player& player);
};


#pragma once
#include "Creature.h"

/**
 * Postaæ gracza
 */
class Player: public Creature
{
public:
	Player(Position pos = Position(0,0));
	void drawHud(sf::RenderWindow& rw) const;
	void replenishHealth();
private:
	sf::Image hbarimg, mbarimg, hudimg;
	float health;
	float mana;
};


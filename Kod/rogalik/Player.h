#pragma once
#include "Creature.h"

/**
 * Posta� gracza
 */
class Player: public Creature
{
public:
	Player(const Position pos = Position(0,0));
	void drawHud(sf::RenderWindow& rw) const;
private:
	sf::Image hbarimg, mbarimg, hudimg;
	float health;
	float mana;
};


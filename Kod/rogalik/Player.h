#pragma once
#include <list>
#include "Creature.h"

/**
 * Postaæ gracza
 */
class Player: public Creature
{
public:
	Player(Position pos = Position(0,0));
	void drawHud(sf::RenderWindow& rw) const;
	void drawInventory(sf::RenderWindow& rw) const;
	
	void replenishHealth();
	void step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Game& game);
	void getInput(const sf::Event& e);
	void giveItem(const Item& item);

	friend class GameBuilder;
private:
	sf::Image hbarimg, mbarimg, hudimg;
	float mana;

	std::list<Item> inventory;
};


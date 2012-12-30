#pragma once
#include <list>
#include "Creature.h"

/**
 * Postaæ gracza
 */
class Player: public Creature
{
public:
	/**
	 * Tworzy postaæ gracza
	 * @param pos pocz¹tkowe po³o¿enie gracza
	 */
	Player(Position pos = Position(0,0));
	/**
	 * Wyœwielta HUD gracza na ekranie
	 * HUD zawiera podstawowy interfejs z paskiem ¿ycia, paskiem many, minimap¹ itp.
	 * HUD jest wyœwietlany w trakcie normalnej rozgrywki
	 * @param rw Obiekt okna na którym bêdzie rysowany HUD
	 */
	void drawHud(sf::RenderWindow& rw) const;
	/**
	 * Wyœwielta okno ekwipunku gracza na ekranie
	 * @param rw Obiekt okna na którym bêdzie rysowany ekwipunek
	 */
	void drawInventory(sf::RenderWindow& rw) const;
	/**
	 * Wyœwielta okno atrybutow gracza na ekranie
	 * @param rw Obiekt okna na którym bêdzie rysowany ekwipunek
	 */
	void drawAtributes(sf::RenderWindow& rw) const;

	/**
	 * Odnawie ¿ycie gracza
	 */
	void replenishHealth();
	/**
	 * Wykonuje krok symulacji
	 * @param dt D³ugoœæ kroku czasowego
	 * @param terrain Teren (mapa) w jakim znajduje siê postaæ
	 * @param creatures Lista postaci niezale¿nych na mapie
	 * @param game Obiekt gry
	 */
	void step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Game& game);
	
	/**
	 * Pobiera wejœcie
	 * @param e Przekazywane zdarzenie
	 */
	void getInput(const sf::Event& e);
	/**
	 * Daje postaci gracza dany przedmiot
	 * @param item przedmiot dawany postaci
	 */
	void giveItem(const Item& item);

	friend class GameBuilder;
private:
	sf::Image hbarimg, mbarimg, hudimg;
	float mana;

	std::list<Item> inventory;
};


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
	 * Pobiera wejœcie do ekranu ekwipunku
	 * @param e Przekazywane zdarzenie
	 */
	void getInputInventory(const sf::Event& e);

	/**
	 * Pobiera wejœcie do ekranu atrybutów
	 * @param e Przekazywane zdarzenie
	 */
	void getInputAtributes(const sf::Event& e);

	/**
	 * Daje postaci gracza dany przedmiot
	 * @param item przedmiot dawany postaci
	 */
	void giveItem(const Item& item);

	friend class GameBuilder;
private:
	/**
	 * Zwraca wspó³czynnik ataku postaci
	 */
	float getAttack();

	/**
	 * Zwraca wspó³czynnik obrony postaci
	 */
	float getDefence();

	/**
	 * Usuwa przedmiot z ekwipunku
	 */
	void deleteItem(int i);
	sf::Image hbarimg, hudimg;

	int defLevel;
	int attLevel;
	int selectedAttribute;

	std::vector<Item> inventory;
	int weapon;
	int armor;
	int selectedItem;
};


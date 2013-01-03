#pragma once
#include <list>
#include "Creature.h"

/**
 * Posta� gracza
 */
class Player: public Creature
{
public:
	/**
	 * Tworzy posta� gracza
	 * @param pos pocz�tkowe po�o�enie gracza
	 */
	Player(Position pos = Position(0,0));
	/**
	 * Wy�wielta HUD gracza na ekranie
	 * HUD zawiera podstawowy interfejs z paskiem �ycia, paskiem many, minimap� itp.
	 * HUD jest wy�wietlany w trakcie normalnej rozgrywki
	 * @param rw Obiekt okna na kt�rym b�dzie rysowany HUD
	 */
	void drawHud(sf::RenderWindow& rw) const;
	/**
	 * Wy�wielta okno ekwipunku gracza na ekranie
	 * @param rw Obiekt okna na kt�rym b�dzie rysowany ekwipunek
	 */
	void drawInventory(sf::RenderWindow& rw) const;
	/**
	 * Wy�wielta okno atrybutow gracza na ekranie
	 * @param rw Obiekt okna na kt�rym b�dzie rysowany ekwipunek
	 */
	void drawAtributes(sf::RenderWindow& rw) const;

	/**
	 * Odnawie �ycie gracza
	 */
	void replenishHealth();
	/**
	 * Wykonuje krok symulacji
	 * @param dt D�ugo�� kroku czasowego
	 * @param terrain Teren (mapa) w jakim znajduje si� posta�
	 * @param creatures Lista postaci niezale�nych na mapie
	 * @param game Obiekt gry
	 */
	void step(float dt, const Terrain& terrain, std::list<Creature> &creatures, Game& game);
	
	/**
	 * Pobiera wej�cie
	 * @param e Przekazywane zdarzenie
	 */
	void getInput(const sf::Event& e);
	
	/**
	 * Pobiera wej�cie do ekranu ekwipunku
	 * @param e Przekazywane zdarzenie
	 */
	void getInputInventory(const sf::Event& e);

	/**
	 * Pobiera wej�cie do ekranu atrybut�w
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
	 * Zwraca wsp�czynnik ataku postaci
	 */
	float getAttack();

	/**
	 * Zwraca wsp�czynnik obrony postaci
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


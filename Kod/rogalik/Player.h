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
	 * @param cretures lista postaci
	 */
	void getInputInventory(const sf::Event& e, std::list<Creature>& creatures);

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

	/**
	 * Bierze od postaci gracza dany przedmiot
	 * @param item nazwa przedmiotu
	 */
	void takeItem(const std::wstring& item);
	
	/**
	 * Daje postaci gracza monety
	 * @param coins liczba dawanych monet
	 */
	void giveMoney(int coins);

	/**
	 * Bierze od postaci gracza monety
	 * @param coins liczba branych monet
	 */
	void takeMoney(int coins);

	/**
	 * Zwraca true gdy posta� ma przedmiot o zadanej nazwie
	 * @param item nazwa przedmiotu
	 */
	bool hasItem(const std::wstring& item) const;

	/**
	 * Zwraca liczb� monet posiadanych przez posta�
	 */
	int hasMoney() const;
	/**
	** Zwraca ekwipunek posiadany przez gracza
	**/
	const std::vector<Item> & getInventory()const;

	/**
	 * Zwraca true gdy wygrali�my gr�
	 */
	bool isWinner() const;

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
	/**
	** Zwraca wielkosc inventory
	**/
	int InventorySize()const;
	sf::Image hbarimg, hudimg;

	int defLevel;
	int attLevel;
	int selectedAttribute;

	std::vector<Item> inventory;
	int coins;
	int weapon;
	int armor;
	int selectedItem;

	std::vector<std::wstring> msgList;

	friend Dialog;
};


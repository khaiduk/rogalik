#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextArea.h"
#include "Item.h"

class Creature;
class Player;

/**
 * Dialog postaci gracza z postaciami niezale�nymi
 */
class Dialog
{
public:
	/// Identyfikator w�z�a startowego
	static const int START_DIALOG = 0;
	/// Identyfikator pseudow�z�a zako�czenia rozmowy
	static const int END_DIALOG = 0;

	/**
	 * W�ze� dialogu
	 */
	class Node
	{
	public:
		Node(std::wstring msg = L"");

		/**
		 * Dodaje opcj� dialogow�
		 * @param asw Odpowied� postaci gracza
		 * @param id Identyfikator w�z�a docelowego
		 */
		Node& addOption(std::wstring asw, int id);

		/**
		 * Dodaje opcj� dialogow�, widoczn� gdy posta� gracza ma dany przedmiot
		 * @param item Nazwa przedmiotu
		 * @param asw Odpowied� postaci gracza
		 * @param id Identyfikator w�z�a docelowego
		 */
		Node& addOptionIfHas(std::wstring item, std::wstring asw, int id);

		/**
		 * Dodaje opcj� dialogow�, widoczn� gdy posta� gracza nie ma danego przedmiotu
		 * @param item Nazwa przedmiotu
		 * @param asw Odpowied� postaci gracza
		 * @param id Identyfikator w�z�a docelowego
		 */
		Node& addOptionIfHasNot(std::wstring item, std::wstring asw, int id);
		
		/**
		 * Dodaje opcj� dialogow�, widoczn� gdy posta� gracza ma podan� liczb� monet (lub wi�cej)
		 * @param coins liczba monet
		 * @param asw Odpowied� postaci gracza
		 * @param id Identyfikator w�z�a docelowego
		 */
		Node& addOptionIfHasMoney(int coins, std::wstring asw, int id);

		/**
		 * Dodaje opcj� dialogow�, widoczn� gdy posta� gracza nie ma podanej liczby monet
		 * @param coins liczba monet
		 * @param asw Odpowied� postaci gracza
		 * @param id Identyfikator w�z�a docelowego
		 */
		Node& addOptionIfHasNotMoney(int coins, std::wstring asw, int id);

		/**
		 * Zwraca czy dana opcja powinna zosta� pokazana
		 * @param i numer opcji
		 * @param player Posta� gracza
		 */
		bool optionIsShown(int i, const Player& player);

		/**
		 * Dodaje przedmiot dawany postaci gracza po znaleznieniu si� w tym w�le.
		 * @param item Dawany przedmiot
		 */
		Node& addGiveItem(const Item& item);

		/**
		 * Po znalezieniu si� w w�le graczowi �ycie spadnie o 20%
		 */
		Node& addLoseHealth();

		/**
		 * Po znalezieniu si� w w�le graczowi zostan� zabrane monety
		 * @param coins liczba monet do zabrania
		 */
		Node& addTakeCoins(int coins);

		/**
		 * Po znalezieniu si� w w�le graczowi zostanie zabrany przedmiot
		 * @param item nazwa przedmiotu
		 */
		Node& addTakeItem(std::wstring item);

		/**
		** Dodaj item jezeli jeszcze go nie ma
		** @param item przedmiot @param player postac
		**/
		Node& addIfDontHave(const Item& item, const Player& player);
		/**
		** wyswietl inventory
		**/
		Node& showWhatYouGot(const Player& player);
		/**
		** Zabiera item od gracza
		** @param player - gracz
		** @param i  - id/(miejsce w ekwipunku gracza) itemu
		**/
		Node& addTakeItem(Player &player,int i);
		friend class Dialog;
	private:
		std::wstring message;
		std::vector<Item> giveItems;
		bool losehp;
		int takeCoins;
		int giveCoins;
		std::vector<std::wstring> takeItems;


		std::vector<std::wstring> optsAns;
		std::vector<int> optsDest;
		std::vector<std::wstring> optNeedsItem;
		std::vector<std::wstring> optNeedsNoItem;
		std::vector<int> optNeedsMoney;
	};

	Dialog(void);
	~Dialog(void);

	/**
	 * Tworzy nowy w�ze� dialogu
	 * @param id Identyfikator w�z�a
	 * @param msg Wypowied� postaci niezale�nej
	 */
	Node& addNode(int id, std::wstring msg);

	/**
	 * Rysuje okno (interfejs) dialogu postaci
	 * @param rw Obiekt okna na kt�rym b�dzie rysowany dialog
	 */
	void draw(sf::RenderWindow& rw, const Player& player);
	/**
	 * Pobiera wej�cie
	 * @param e Przekazywane zdarzenie
	 * @param player Posta� gracza
	 */
	bool getInput(const sf::Event& e, Player& player);
	/**
	 * Przywraca dialog do stanu pocz�tkowego
	 */
	void resetDialog();

private:
	std::map<int, Node> nodes;

	int currentNode;
	int selectedAns;
};


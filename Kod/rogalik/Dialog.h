#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextArea.h"
#include "Item.h"

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
		 * Dodaje przedmiot dawany postaci gracza po znaleznieniu si� w tym w�le.
		 * @param item Dawany przedmiot
		 */
		Node& addGiveItem(const Item& item);

		friend class Dialog;
	private:
		std::wstring message;
		std::vector<std::wstring> optsAns;
		std::vector<int> optsDest;
		std::vector<Item> giveItems;
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
	void draw(sf::RenderWindow& rw);
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


#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * Dialog postaci gracza z postaciami niezale¿nymi
 */
class Dialog
{
public:
	/// Identyfikator wêz³a startowego
	static const int START_DIALOG = 0;
	/// Identyfikator pseudowêz³a zakoñczenia rozmowy
	static const int END_DIALOG = 0;

	/**
	 * Wêze³ dialogu
	 */
	class Node
	{
	public:
		Node(std::wstring msg = L"");

		/**
		 * Dodaje opcjê dialogow¹
		 * @param asw OdpowiedŸ postaci gracza
		 * @param id Identyfikator wêz³a docelowego
		 */
		Node& addOption(std::wstring asw, int id);

		friend class Dialog;
	private:
		std::wstring message;
		std::vector<std::wstring> optsAns;
		std::vector<int> optsDest;

	};

	Dialog(void);
	~Dialog(void);

	/**
	 * Tworzy nowy wêze³ dialogu
	 * @param id Identyfikator wêz³a
	 * @param msg WypowiedŸ postaci niezale¿nej
	 */
	Node& addNode(int id, std::wstring msg);

	/**
	 * Rysuje okno (interfejs) dialogu postaci
	 * @param rw Obiekt okna na którym bêdzie rysowany dialog
	 */
	void draw(sf::RenderWindow& rw);
	/**
	 * Pobiera wejœcie
	 * @param e Przekazywane zdarzenie
	 */
	bool getInput(const sf::Event& e);
	/**
	 * Przywraca dialog do stanu pocz¹tkowego
	 */
	void resetDialog();

private:
	std::map<int, Node> nodes;

	int currentNode;
	int selectedAns;
};


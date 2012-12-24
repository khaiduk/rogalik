#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

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

		friend class Dialog;
	private:
		std::wstring message;
		std::vector<std::wstring> optsAns;
		std::vector<int> optsDest;

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
	 */
	bool getInput(const sf::Event& e);
	/**
	 * Przywraca dialog do stanu pocz�tkowego
	 */
	void resetDialog();

private:
	std::map<int, Node> nodes;

	int currentNode;
	int selectedAns;
};


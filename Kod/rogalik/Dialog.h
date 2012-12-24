#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Dialog
{
public:
	static const int START_DIALOG = 0;
	static const int END_DIALOG = 0;
	class Node
	{
	public:
		Node(std::wstring msg = L"");
		Node& addOption(std::wstring asw, int id);

		std::wstring message;
		std::vector<std::wstring> optsAns;
		std::vector<int> optsDest;

	};

	Dialog(void);
	~Dialog(void);

	Node& addNode(int id, std::wstring msg);

	void draw(sf::RenderWindow& rw);
	bool getInput(const sf::Event& e);
	void resetDialog();

	std::map<int, Node> nodes;

	int currentNode;
	int selectedAns;
};


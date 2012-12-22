#pragma once
#include <map>
#include <string>
#include <iostream>
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
		std::map<int, std::wstring> opts;

	};

	Dialog(void);
	~Dialog(void);

	Node& addNode(int id, std::wstring msg);

	std::map<int, Node> nodes;
};


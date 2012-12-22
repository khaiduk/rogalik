#include "Dialog.h"

Dialog::Dialog(void)
{
}


Dialog::~Dialog(void)
{
}

Dialog::Node::Node(std::wstring msg)//:message(msg)
{
}

Dialog::Node& Dialog::Node::addOption(std::wstring asw, int id)
{
	opts[id] = asw;
	return *this;
}

Dialog::Node& Dialog::addNode(int id, std::wstring msg)
{
	nodes[id] = Dialog::Node(msg);
	return nodes[id];
}
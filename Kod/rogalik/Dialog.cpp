#include "Dialog.h"
#include "Player.h"

Dialog::Dialog(void): currentNode(START_DIALOG), selectedAns(0)
{
}


Dialog::~Dialog(void)
{
}

Dialog::Node::Node(std::wstring msg):message(msg)
{
}

Dialog::Node& Dialog::Node::addOption(std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	return *this;
}

Dialog::Node& Dialog::Node::addGiveItem(const Item& item)
{
	giveItems.push_back(item);
	return *this;
}

Dialog::Node& Dialog::addNode(int id, std::wstring msg)
{
	nodes[id] = Dialog::Node(msg);
	return nodes[id];
}

void Dialog::draw(sf::RenderWindow& rw)
{
	if(nodes.size() == 0) // nie ma dialogu
		return; // wyjd�
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("tlo.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A�BC�DE�FGHIJKL�MN�O�PRS�TUWYZ��a�bc�de�fghijkl�mn�o�prs�tuwyz��XxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
	}

	sf::Sprite tloH(tlo);
	rw.Draw(tloH);

	TextArea txt(nodes[currentNode].message, 700, font, 30);
	txt.SetPosition(50, 50);
	txt.SetColor(sf::Color(20, 18, 160));
	rw.Draw(txt);
	
	float posy = txt.GetHeight() + 100;
	
	for(int i=0;i<nodes[currentNode].optsAns.size();i++)
	{
		sf::String t(nodes[currentNode].optsAns[i], font, 20.f);
		if(selectedAns == i)
			t.SetColor(sf::Color(120, 18, 60));
		else
			t.SetColor(sf::Color(20, 18, 160));
		t.SetPosition(70.f, posy+40*i);
		rw.Draw(t);
	}
}


bool Dialog::getInput(const sf::Event& e, Player &player)
{
	if(nodes.size() == 0) // nie ma dialogu
		return false; //wyjd�

	if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Down )
	{
		selectedAns++;
		if(selectedAns >= nodes[currentNode].optsAns.size())
			selectedAns = 0;
	}
	else if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Up )
	{
		selectedAns--;
		if(selectedAns < 0 )
			selectedAns = nodes[currentNode].optsAns.size()-1;
	}
	else if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Space )
	{
		if(nodes[currentNode].optsDest[selectedAns] == END_DIALOG)
		{
			resetDialog();
			return false;
		}
		else
		{
			currentNode = nodes[currentNode].optsDest[selectedAns];
			selectedAns = 0;
			for(std::vector<Item>::iterator i = nodes[currentNode].giveItems.begin(); i != nodes[currentNode].giveItems.end(); i++)
			{
				player.giveItem(*i);
			}
			nodes[currentNode].giveItems.erase(nodes[currentNode].giveItems.begin(), nodes[currentNode].giveItems.end());
		}
	}
	return true;
}

void Dialog::resetDialog()
{
	currentNode = START_DIALOG;
	selectedAns = 0;
}
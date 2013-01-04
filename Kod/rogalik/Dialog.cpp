#include "Dialog.h"
#include "Player.h"

Dialog::Dialog(void): currentNode(START_DIALOG), selectedAns(0)
{
}


Dialog::~Dialog(void)
{
}

Dialog::Node::Node(std::wstring msg):message(msg), losehp(false)
{
}

Dialog::Node& Dialog::Node::addOption(std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	optNeedsMoney.push_back(0);
	optNeedsItem.push_back(L"");
	optNeedsNoItem.push_back(L"");
	return *this;
}

Dialog::Node& Dialog::Node::addOptionIfHas(std::wstring item, std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	optNeedsMoney.push_back(0);
	optNeedsItem.push_back(item);
	optNeedsNoItem.push_back(L"");
	return *this;
}

Dialog::Node& Dialog::Node::addOptionIfHasNot(std::wstring item, std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	optNeedsMoney.push_back(0);
	optNeedsItem.push_back(L"");
	optNeedsNoItem.push_back(item);
	return *this;
}

Dialog::Node& Dialog::Node::addOptionIfHasMoney(int coins, std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	optNeedsMoney.push_back(coins);
	optNeedsItem.push_back(L"");
	optNeedsNoItem.push_back(L"");
	return *this;
}

Dialog::Node& Dialog::Node::addOptionIfHasNotMoney(int coins, std::wstring asw, int id)
{
	optsAns.push_back(asw);
	optsDest.push_back(id);
	optNeedsMoney.push_back(-coins);
	optNeedsItem.push_back(L"");
	optNeedsNoItem.push_back(L"");
	return *this;
}

bool Dialog::Node::optionIsShown(int i, const Player& player)
{
	if(!optNeedsItem[i].empty() && !player.hasItem(optNeedsItem[i]))
		return false;
	if(!optNeedsNoItem[i].empty() && player.hasItem(optNeedsNoItem[i]))
		return false;
	if(optNeedsMoney[i] < 0 && player.hasMoney() >= -optNeedsMoney[i])
		return false;
	if(optNeedsMoney[i] > 0 && player.hasMoney() < optNeedsMoney[i])
		return false;
	return true;
}

Dialog::Node& Dialog::Node::addGiveItem(const Item& item)
{
	giveItems.push_back(item);
	return *this;
}

Dialog::Node& Dialog::Node::addLoseHealth()
{
	losehp = true;
	return *this;
}

Dialog::Node& Dialog::Node::addTakeCoins(int coins)
{
	takeCoins += coins;
	return *this;
}

Dialog::Node& Dialog::Node::addTakeItem(std::wstring item)
{
	takeItems.push_back(item);
	return *this;
}

Dialog::Node& Dialog::addNode(int id, std::wstring msg)
{
	nodes[id] = Dialog::Node(msg);
	return nodes[id];
}

void Dialog::draw(sf::RenderWindow& rw, const Player& player)
{
	if(nodes.size() == 0) // nie ma dialogu
		return; // wyjdŸ
	static bool firstRun = true;
	static sf::Image tlo;
	static sf::Font font;
	if(firstRun)
	{
		tlo.LoadFromFile("tlo.png");
		firstRun = false;
		font.LoadFromFile("silesiana.otf", 50,  L"A¥BCÆDEÊFGHIJKL£MNÑOÓPRSŒTUWYZ¯a¹bcædeêfghijkl³mnñoóprsœtuwyzŸ¿XxVvQq0123456789~!@#$%^&*()_-[]\\;',./{}:\"<>?=-+ ");
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
		if(!nodes[currentNode].optionIsShown(i, player))
			continue;

		sf::String t(nodes[currentNode].optsAns[i], font, 20.f);
		if(selectedAns == i)
			t.SetColor(sf::Color(120, 18, 60));
		else
			t.SetColor(sf::Color(20, 18, 160));
		posy += 40;
		t.SetPosition(70.f, posy);
		rw.Draw(t);
	}
}


bool Dialog::getInput(const sf::Event& e, Player &player)
{
	if(nodes.size() == 0) // nie ma dialogu
		return false; //wyjdŸ

	if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Down )
	{
		do
		{
			selectedAns++;
			if(selectedAns >= nodes[currentNode].optsAns.size())
				selectedAns = 0;
		}
		while(!nodes[currentNode].optionIsShown(selectedAns, player));
	}
	else if( e.Type == sf::Event::KeyPressed && e.Key.Code == sf::Key::Up )
	{
		do
		{
			selectedAns--;
			if(selectedAns < 0 )
				selectedAns = nodes[currentNode].optsAns.size()-1;
		}
		while(!nodes[currentNode].optionIsShown(selectedAns, player));
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

			
			for(std::vector<std::wstring>::iterator i = nodes[currentNode].takeItems.begin(); i != nodes[currentNode].takeItems.end(); i++)
			{
				if(player.hasItem(*i))
					player.takeItem(*i);
			}


			if(nodes[currentNode].losehp)
				player.health *= 0.80;

			if(player.hasMoney() > nodes[currentNode].takeCoins)
				player.takeMoney(nodes[currentNode].takeCoins);
			else
				player.takeMoney(player.hasMoney());
		}
	}
	return true;
}

void Dialog::resetDialog()
{
	currentNode = START_DIALOG;
	selectedAns = 0;
}
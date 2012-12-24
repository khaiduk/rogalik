#pragma once
#include <string>
/**
 * Przedmiot wyst�puj�cy w grze
 */
class Item
{
public:
	/**
	 * Tworzy przedmiot
	 * @param name Kr�tka nazwa przedmiotu
	 * @param desc Opis przedmiotu w grze
	 */
	Item(const std::wstring name, const std::wstring desc);

	/**
	 * Zwraca kr�tk� nazw� danego przedmiotu
	 */
	std::wstring getName() const;
private:	
	std::wstring name;
	std::wstring desc;
};


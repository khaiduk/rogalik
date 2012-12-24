#pragma once
#include <string>
/**
 * Przedmiot wystêpuj¹cy w grze
 */
class Item
{
public:
	/**
	 * Tworzy przedmiot
	 * @param name Krótka nazwa przedmiotu
	 * @param desc Opis przedmiotu w grze
	 */
	Item(const std::wstring name, const std::wstring desc);

	/**
	 * Zwraca krótk¹ nazwê danego przedmiotu
	 */
	std::wstring getName() const;
private:	
	std::wstring name;
	std::wstring desc;
};


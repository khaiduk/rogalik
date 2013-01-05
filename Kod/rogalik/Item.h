#pragma once
#include <string>
/**
 * Przedmiot wyst�puj�cy w grze
 */
class Item
{
public:
	enum Type
	{
		WEAPON,
		ARMOR,
		HELMET,
		LIFEPOTION,
		SLEEPDUST,
		MAGICSAND,
		DUMB
	};
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

	/**
	 * Zwraca opis danego przedmiotu
	 */
	std::wstring getDesc() const;

	/**
	 * Ustawia w�asno�� danego przedmiotu
	 * Uwaga - dany przedmiot mo�e mie� tylko jedn� w�asno�� - np. bro� nie mo�e by� jednocze�nie zbroj�
	 * @param type Typ w�asno�ci
	 * @param boost Wielko�� danej w�asno�ci (tylko WEAPON i ARMOR)
	 */
	Item& setProperty(Type type, float boost = 0);
	
	/**
	 * Zwraca w�asno�� danego przedmiotu
	 */
	Type getProperty() const;

	/**
	 * Zwraca wielko�� w�asno�ci danego przedmiotu
	 */
	float getPropertyBoost() const;
private:	
	std::wstring name;
	std::wstring desc;
	Type type;
	float boost;
};


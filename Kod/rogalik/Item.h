#pragma once
#include <string>
/**
 * Przedmiot wystêpuj¹cy w grze
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
	 * @param name Krótka nazwa przedmiotu
	 * @param desc Opis przedmiotu w grze
	 */
	Item(const std::wstring name, const std::wstring desc);
	/**
	** Tworzy przedmiot o zadanej wartosci
	** @param name Krotka nazwa przedmiotu
	** @param desc Opis przedmiout
	** @param wartosc Wartosc przedmiotu
	**/
	Item(const std::wstring name , const std::wstring desc , int wartosc);
	/**
	 * Zwraca krótk¹ nazwê danego przedmiotu
	 */
	std::wstring getName() const;

	/**
	 * Zwraca opis danego przedmiotu
	 */
	std::wstring getDesc() const;
	/**
	** Zwraca wartosc danego przedmiotu
	**/
	int getWartosc() const;
	/**
	** Zwraca wartosc w formacie wstring
	**/
	std::wstring getWartoscString()const;
	/**
	 * Ustawia w³asnoœæ danego przedmiotu
	 * Uwaga - dany przedmiot mo¿e mieæ tylko jedn¹ w³asnoœæ - np. broñ nie mo¿e byæ jednoczeœnie zbroj¹
	 * @param type Typ w³asnoœci
	 * @param boost Wielkoœæ danej w³asnoœci (tylko WEAPON i ARMOR)
	 */
	Item& setProperty(Type type, float boost = 0);
	
	/**
	 * Zwraca w³asnoœæ danego przedmiotu
	 */
	Type getProperty() const;

	/**
	 * Zwraca wielkoœæ w³asnoœci danego przedmiotu
	 */
	float getPropertyBoost() const;
private:	
	std::wstring name;
	std::wstring desc;
	int wartosc;
	Type type;
	float boost;
};


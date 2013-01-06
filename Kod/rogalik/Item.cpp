#include "Item.h"


Item::Item(const std::wstring name, const std::wstring desc) : name(name), desc(desc), type(DUMB), boost(0),wartosc(0)
{
}

std::wstring Item::getName() const
{
	return name;
}
std::wstring Item::getDesc() const
{
	return desc;
}

Item& Item::setProperty(Item::Type type, float boost)
{
	this->type = type;
	this->boost = boost;
	return *this;
}
	
Item::Type Item::getProperty() const
{
	return type;
}

float Item::getPropertyBoost() const
{
	return boost;
}
Item::Item(const std::wstring name , const std::wstring desc , int wartosc):name(name),desc(desc),type(DUMB),boost(0),wartosc(wartosc)
{

}
int Item::getWartosc() const
{
	return wartosc;
}
std::wstring Item::getWartoscString()const
{
	std::wstringstream ss;
	ss << wartosc;
	std::wstring var = ss.str(); 

	return var;
}
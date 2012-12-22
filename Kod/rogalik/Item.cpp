#include "Item.h"


Item::Item(const std::wstring name, const std::wstring desc) : name(name), desc(desc)
{
}

std::wstring Item::getName() const
{
	return name;
}

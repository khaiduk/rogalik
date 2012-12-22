#pragma once
#include <string>
/**
 * Obiekt wyst�puj�cy w grze
 */
class Item
{
public:
	Item(const std::wstring name, const std::wstring desc);

	std::wstring getName() const;
private:	
	std::wstring name;
	std::wstring desc;
};


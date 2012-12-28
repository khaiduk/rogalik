#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

/**
 * Pole tekstowe z mo�liwo�ci� �amania linii tekstu
 * Klasa ta dziedziczy po sf::Drawable, a zatem mo�na j� stosowa� podobnie jak np. sf::String
 */
class TextArea: public sf::Drawable
{
public:
	/**
	 * Tworzy pole tekstowe
	 * @param Text Tre�� pola
	 * @param Width Szeroko�� pola w pikselach
	 * @param CharFont Kr�j pisma
	 * @param Size Wielko�� pisma
	 */
	TextArea(const std::wstring& Text, float Width = 1000, const sf::Font& CharFont = sf::Font::GetDefaultFont(), float Size = 30.f);
	/// Ustawia tekst na podany
    void SetText(const std::wstring& Text);
	/// Ustawia szeroko�� pola (w pikselach)
	void SetWidth(float Width);
	/// Ustawia u�yty kr�j pisma
    void SetFont(const sf::Font& CharFont);
	/// Ustawia rozmiar pisma
    void SetSize(float Size);
	/// Zwraca wysoko�� pola tekstowego
    float GetHeight() const;
protected:
    virtual void Render(sf::RenderTarget& Target) const;
private:
	std::vector<sf::String> Recalc() const;

	float width;
	std::wstring str;
	const sf::Font *font;
	float size;
	sf::Color color;
	bool needRecalc;
};


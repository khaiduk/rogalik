#include "TextArea.h"

TextArea::TextArea(const std::wstring & Text,float Width, const sf::Font& CharFont, float Size):
str(Text), width(Width), font(&CharFont), size(Size), color(0,0,0) { Recalc(); }

void TextArea::SetText(const std::wstring& Text)
{
	str = Text;
}

void TextArea::SetWidth(float Width)
{
	width = Width;
}

void TextArea::SetFont(const sf::Font& CharFont)
{
	font = &CharFont;
}

void TextArea::SetSize(float Size)
{
	size = Size;
}

float TextArea::GetHeight() const
{
	std::vector<sf::String> words = Recalc();
	if(words.size() != 0)
		return words[words.size() - 1].GetRect().Bottom;
	else
		return 0.0;
}

void TextArea::Render(sf::RenderTarget& Target) const
{
	std::vector<sf::String> words = Recalc();
	for(int i=0;i<words.size();i++)
	{
		Target.Draw(words[i]);
	}

}

std::vector<sf::String> TextArea::Recalc() const
{
	std::vector<sf::String> words;
	sf::Vector2f pos = sf::Vector2f(0, 0);

	words.clear();
	
    std::wstring buf;
    std::wstringstream ss(str);
    while (ss >> buf) // dzielimy string na s³owa oddzielone bia³ymi znakami
	{
		sf::String t(buf, *font, size);
		t.SetColor(GetColor());
		t.SetPosition(pos.x, pos.y);

		if(t.GetRect().Right > width)
		{
			pos.y += size;
			pos.x = 0;
			t.SetPosition(pos.x, pos.y);
		}

		pos.x += t.GetRect().GetWidth() + font->GetGlyph(32).Advance * size / static_cast<float>(font->GetCharacterSize());

		words.push_back(t);
	}
	return words;
}
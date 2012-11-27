#pragma once
#include <SFML/Graphics.hpp>
#include "Position.h"
#include "ImageRes.h"

/**
 * Pojedynczy kafelek terenu
 * Kafelek posiada wygl�d (reprezentacja graficzna) oraz w�asno�ci fizyczne
 * (tj. po�o�enie, mo�liwo�� przej�cia, itp.)
 */
class Tile
{
public:
	/**
	 * Tworzy kafelk� o zadanym po�o�eniu i wygl�dzie
	 * @param pos po�o�enie kafelki
	 * @param img identyfikator obrazka
	 */
	Tile(const Position pos, int img = 0);
	/**
	 * Wy�wietla kafelk� na ekranie w zadanym miejscu
	 * @param rw okno rysowania
	 * @param x przesuni�cie wzgl�dem pocz�tku okna
	 * @param y przesuni�cie wzgl�dem pocz�tku okna
	 */
	void draw(sf::RenderWindow& rw, int x, int y) const;
	/**
	 * Ustawia wygl�d kafelki na img
	 * @param img identyfikator obrazka
	 */
	void setImage(int img);
	/**
	 * Ustawia niemo�no�� przej�cia przez kafelek
	 * @param solid czy nie da si� przej��
	 */
	void setSolid(bool solid);
	/**
	 *Zwraca warto�� logiczn� odpowiadaj�c� mo�liwo�ci przejscia przez kafelk�
	 */
	bool isSolid();

	void setWarp(const Position& pos);
	bool isWarp();
	Position getWarp();
private:
	Position pos;
	sf::Sprite sprite;
	bool solid;
	bool warp;
	Position warpTo;

};


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

	/**
	 * Ustawia kafelek jako teleportuj�cy postacie do innego kafelka
	 * @param pos punkt docelowy
	 */
	void setWarp(const Position& pos);

	/**
	 * Zwraca true gdy kafalek jest teleportuj�cy, w przeciwnym wypadku zwraca false
	 */
	bool isWarp();

	/**
	 * Zwraca punkt docelowy kafelka teleportuj�cego
	 */
	Position getWarp();

	/**
	 * Ustawia pr�dko�� poruszania si� po danym kafelku
	 * @param speed pr�dko�� poruszania si� po danym kafelku
	 */
	void setWalkSpeed(int speed);

	/**
	 * Zwraca pr�dko�� poruszania si� po danym kafelku
	 */
	int getWalkSpeed() const;
private:
	Position pos;
	sf::Sprite sprite;
	bool solid;
	bool warp;
	Position warpTo;
	int walkSpeed;

};


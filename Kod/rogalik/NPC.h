#pragma once
#include "Creature.h"

/**
 * Posta� niezale�na (NPC)
 */
class NPC: public Creature
{
public:
	/**
	 * Tworzy posta� o zadanym po�o�eniu i wygl�dzie
	 */
	NPC(const Position pos = Position(0,0), int img = 0);
};


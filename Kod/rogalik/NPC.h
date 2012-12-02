#pragma once
#include "Creature.h"

/**
 * Postaæ niezale¿na (NPC)
 */
class NPC: public Creature
{
public:
	/**
	 * Tworzy postaæ o zadanym po³o¿eniu i wygl¹dzie
	 */
	NPC(const Position pos = Position(0,0), int img = 0);
};


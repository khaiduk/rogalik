#include "Enemy.h"


Enemy::Enemy(const Position pos) : Creature(pos, ImageRes::MONSTER)
{
	speed = 3;
}

void Enemy::step(float dt, const Terrain& terrain, Player& player)
{
	static Position newPos = pos;

	walk(walkDir, terrain);
	
	if(newPos == pos)
	{
		newPos = Position(rand()%10+5, rand()%10+5);
	}

	if(pos.GetX() < newPos.GetX())
	{
		walkDir.SetX(1);
	}
	else if(pos.GetX() > newPos.GetX())
	{
		walkDir.SetX(-1);
	}
	else
	{
		walkDir.SetX(0);
	}

	if(pos.GetY() < newPos.GetY())
	{
		walkDir.SetY(1);
	}
	else if(pos.GetY() > newPos.GetY())
	{
		walkDir.SetY(-1);
	}
	else
	{
		walkDir.SetY(0);
	}
}
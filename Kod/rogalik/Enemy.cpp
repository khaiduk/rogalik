#include "Enemy.h"


Enemy::Enemy(const Position pos) : Creature(pos, ImageRes::MONSTER)
{
}

void Enemy::step(float dt, const Terrain& terrain, Player& player)
{
	static float accdt;
	accdt += dt;
	if(accdt > 0.5)
	{
		// losowe b³¹dzenie
		Position dp = Position(0, 0);
		if(pos.GetX() > 15)
			dp.SetX(-1);
		else if(pos.GetX() < 5)
			dp.SetX(1);
		else if(pos.GetY() > 15)
			dp.SetY(-1);
		else if(pos.GetY() < 5)
			dp.SetY(1);
		else // random direction
		{
			if(rand()%2)
				dp.SetX(rand()%3-1);
			else
				dp.SetY(rand()%3-1);

		}

		if(Position::distance(pos, player.getPosition()) < 5)
		{
			//player.attack(
		}

		move(dp, terrain);
		accdt -= 0.5;
	}
}
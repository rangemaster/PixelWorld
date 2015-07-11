#include "CollisionManager.h"

bool InTheArea(double x1, double w1, double y1, double h1, double x2, double w2, double y2, double h2)
{
	bool result = true;
	double v1, v2, v3, v4;
	v1 = sqrt(pow(x1 - x2, 2));
	v2 = (w1 / 2) + (w2 / 2);
	v3 = sqrt(pow(y1 - y2, 2));
	v4 = (h1 / 2) + (h2 / 2);
	result &= v1 <= v2;
	result &= v3 <= v4;
	return result;
}

/*
* When the player is falling
*/
bool BrickCollisionVertical(LevelBrick* levelPeace, Player* player)
{
	if (InTheArea(levelPeace->getZ(), levelPeace->getW(), levelPeace->getY(), levelPeace->getD(), player->getPosZ(), player->getW(), player->getPosY(), player->getH()))
		return true;
	return false;
}
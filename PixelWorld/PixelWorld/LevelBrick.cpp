#include "LevelBrick.h"

LevelBrick::LevelBrick(double xPos, double yPos, double zPos, double width, double height, double depth)
{
	x = xPos;
	y = yPos;
	z = zPos;
	w = width;
	h = height;
	d = depth;
}
LevelBrick::~LevelBrick(){}

double LevelBrick::getX(void){ return x; }
double LevelBrick::getY(void){ return y; }
double LevelBrick::getZ(void){ return z; }
double LevelBrick::getW(void){ return w; }
double LevelBrick::getH(void){ return h; }
double LevelBrick::getD(void){ return d; }
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
void LevelBrick::setX(double xPos){ x = xPos; };
void LevelBrick::setY(double yPos){ y = yPos; };
void LevelBrick::setZ(double zPos){ z = zPos; };
void LevelBrick::setW(double width){ w = width; };
void LevelBrick::setH(double height){ h = height; };
void LevelBrick::setD(double depth){ d = depth; };
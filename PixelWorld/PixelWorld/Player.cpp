#include "Player.h"
#include <iostream>
#include <iostream>

using namespace std;

Player::Player(double x, double y, double z)
{
	posx = x;
	posy = y;
	posz = z;
	width = PLAYER_WIDTH;
	height = PLAYER_HEIGHT;
	depth = PLAYER_DEPTH;
	vecx = 0;
	vecy = 0;
	vecz = 0;
	setJumping(false);
	setJumpAvailable(true);
}


Player::~Player()
{
}

double Player::getPosX(void){ return posx; }
double Player::getPosY(void){ return posy; }
double Player::getPosZ(void){ return posz; }
double Player::getW(void){ return width; };
double Player::getH(void){ return height; };
double Player::getD(void){ return depth; };
void Player::setPosX(double x){ posx = x; }
void Player::setPosY(double y){ posy = y; }
void Player::setPosZ(double z){ posz = z; }
void Player::setW(double w){ width = w; };
void Player::setH(double h){ height = h; };
void Player::setD(double d){ depth = d; };
double Player::getVecX(void){ return vecx; }
double Player::getVecY(void){ return vecy; }
double Player::getVecZ(void){ return vecz; }
void Player::setVecX(double x){ vecx = x; }
void Player::setVecY(double y){ vecy = y; }
void Player::setVecZ(double z){ vecz = z; }

bool Player::isJumpAvailable(void){ return jumpAvailable; }
bool Player::isJumping(void){ return jumping; }
void Player::setJumpAvailable(bool result){ jumpAvailable = result; }
void Player::setJumping(bool result){ jumping = result; }

void Player::stopFalling()
{
	setJumping(false);
	setJumpAvailable(true);
	setVecY(0);
	cout << "Stop falling" << endl;
}
void Player::startFalling()
{
	setJumping(true);
	setJumpAvailable(false);
	cout << "Start falling" << endl;
}
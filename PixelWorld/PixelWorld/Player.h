#pragma once
#define PLAYER_WIDTH 0.5
#define PLAYER_HEIGHT 0.5
#define PLAYER_DEPTH 0.5

class Player
{
public:
	Player(double posx, double posy, double posz);
	~Player();

	double getPosX(void);
	double getPosY(void);
	double getPosZ(void);
	double getW(void);
	double getH(void);
	double getD(void);
	void setPosX(double x);
	void setPosY(double y);
	void setPosZ(double z);
	void setW(double width);
	void setH(double height);
	void setD(double depth);
	double getVecX(void);
	double getVecY(void);
	double getVecZ(void);
	void setVecX(double x);
	void setVecY(double y);
	void setVecZ(double z);
	bool isJumpAvailable(void);
	bool isJumping(void);
	void setJumpAvailable(bool result);
	void setJumping(bool result);
	void stopFalling(void);
	void startFalling(void);
private:
	double width, height, depth;
	double posx, posy, posz;
	double vecx, vecy, vecz;
	bool jumpAvailable, jumping;
};


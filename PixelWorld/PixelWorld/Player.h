#pragma once
class Player
{
public:
	Player(double posx, double posy, double posz);
	~Player();

	double getPosX(void);
	double getPosY(void);
	double getPosZ(void);
	void setPosX(double x);
	void setPosY(double y);
	void setPosZ(double z);
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
private:
	double posx, posy, posz;
	double vecx, vecy, vecz;
	bool jumpAvailable, jumping;
};


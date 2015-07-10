#define TILE_WIDTH 1
#define TILE_HEIGHT 1
#define TILE_DEPTH 1



class LevelBrick{
public:
	LevelBrick(double xPos, double yPos, double zPos, double width, double height, double depth);
	~LevelBrick();

	double getX(void);
	double getY(void);
	double getZ(void);
	double getW(void);
	double getH(void);
	double getD(void);

private:
	double x, y, z;
	double w, h, d;


};
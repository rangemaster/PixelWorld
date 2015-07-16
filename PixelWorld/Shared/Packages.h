#pragma once

struct Package
{
	int value1 = 0;
	int value2 = 0;
	char string[256];
};
struct Vect3D
{
	double x = 0;
	double y = 0;
	double z = 0;
};
struct Pos3D
{
	double x = 0;
	double y = 0;
	double z = 0;
	Pos3D(double posx, double posy, double posz) {
		x = posx;
		y = posy;
		z = posz;
	}
	Pos3D(){}
};

#define TEST_CHAR_CLIENT 'c'
#define TEST_CHAR_SERVER 's'
#define TEST_STRING_CLIENT "Client"
#define TEST_STRING_SERVER "Server"

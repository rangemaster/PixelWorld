#define JUMPING_VECT_Y 5
#define MAX_GRAVITY_SPEED -0.4
#define GRAVITY 0.02
#define UPDATETIME 1000/60
#define XPOSITION -5

#include "GL\freeglut.h"
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <stdio.h>

#include "LoadingProcessor.h"
#include "LevelBrick.h"
#include "Player.h"
#include "cube.h"
#include "CollisionManager.h"
#include "Client.h"
#include "Launcher.h"

using namespace std;

Launcher launcher;
LoadingProcessor loading;

int width, height;
GLfloat lAmbient[] = { 0.7, 0.7, 0.7, 1.0 };
float cameraAngle;
vector<LevelBrick*> *levelPeaces;
Player *player;
bool p_move_left, p_move_right, p_jump, p_duk;
clock_t pastUpdateTime;
void Reset(void);

void moveRight(){
	for (int i = 0; i < levelPeaces->size(); i++)
		levelPeaces->at(i)->setZ(levelPeaces->at(i)->getZ() - 0.1);
}
void moveLeft(){
	for (int i = 0; i < levelPeaces->size(); i++)
		levelPeaces->at(i)->setZ(levelPeaces->at(i)->getZ() + 0.1);
}
void checkKeys()
{
	if (p_jump)
	{
		p_jump = false;
		player->startFalling();
		player->setVecY(player->getVecY() + (double)JUMPING_VECT_Y / 10);
	}
	if (p_move_left){
		moveLeft();
		for (int i = 0; i < levelPeaces->size(); i++)
			if (!BrickCollisionHorizontal(levelPeaces->at(i), player))
				moveRight();
	}
	else if (p_move_right){
		moveRight();
		for (int i = 0; i < levelPeaces->size(); i++)
			if (!BrickCollisionHorizontal(levelPeaces->at(i), player))
				moveLeft();
	}
}
void updatePlayerPosition()
{
	if (player->isJumping())
	{
		// Gravity
		double speed = player->getVecY() - GRAVITY;
		player->setVecY(speed > MAX_GRAVITY_SPEED ? speed : MAX_GRAVITY_SPEED);
	}
	clock_t currentTime = clock();
	if (pastUpdateTime + UPDATETIME < currentTime)
	{
		pastUpdateTime = currentTime;
		player->setPosX(player->getPosX() + player->getVecX());
		player->setPosY(player->getPosY() + player->getVecY());
		player->setPosZ(player->getPosZ() + player->getVecZ());
		if (player->isJumping())
		{
			for (int i = 0; i < levelPeaces->size(); i++)
			{
				if (BrickCollisionVertical(levelPeaces->at(i), player))
				{
					player->setPosY(levelPeaces->at(i)->getY() + levelPeaces->at(i)->getH());
					player->stopFalling();
					break;
				}
			}
		}

		if (player->getPosY() <= -5)
		{
			player->setVecY(0);
			player->setPosY(1);
			player->setJumpAvailable(true);
			player->setJumping(false);
		}
	}
	//cout << "Player Position: " << player->getPosX() << ", " << player->getPosY() << ", " << player->getPosZ() << endl;
}
void DrawWorld()
{
	//drawCube();
	for (int i = 0; i < levelPeaces->size(); i++)
	{
		LevelBrick brick = *levelPeaces->at(i);
		drawCube(brick.getX(), brick.getY(), brick.getZ(), brick.getW(), brick.getH(), brick.getD());
	}
}
void Display()
{
	glClearColor(0.2, 0.3, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 0.1f, 15.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(7 * cos(0), 2, 7 * sin(0), 0, player->getPosY(), 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	glEnable(GL_DEPTH_TEST);


	DrawWorld();

	drawSpecial(player->getPosX() + player->getD() / 2, player->getPosY(), player->getPosZ(), player->getW(), player->getH(), player->getD());


	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -5, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnd();

	glutSwapBuffers();
}
void Reshape(int glwidth, int glheight)
{
	width = glwidth; height = glheight; glViewport(0, 0, width, height);
}
void KeyHandler(unsigned char key, int x, int y, bool pressed)
{
	switch (key)
	{
	case 'r':
		Reset();
		break;
	case 27:
		exit(0);
		break;
	case 'a':
		p_move_left = pressed;
		break;
	case 'w':
		if (pressed && player->isJumpAvailable())
			p_jump = pressed;
		break;
	case 's':
		p_duk = pressed;
		break;
	case 'd':
		p_move_right = pressed;
		break;
	}
}
void KeyPressed(unsigned char key, int x, int y){ KeyHandler(key, x, y, true); }
void KeyReleased(unsigned char key, int x, int y){ KeyHandler(key, x, y, false); }
void MouseButton(int button, int state, int x, int y){}
void MouseMotion(int x, int y){}
void IdleFunc()
{
	checkKeys();
	updatePlayerPosition();
	glutPostRedisplay();
}

bool GlutInit(int argc, char* argv[])
{
	bool succes = true;
	loading.Loading(0, "Start Glut Init");
	glutInit(&argc, argv);
	loading.Loading(10, "Creating play window");
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Sleep(1000);
	glutCreateWindow("Pixel World");
	loading.Loading(50, "Set up display Function");
	glutDisplayFunc(Display);
	loading.Loading(60, "Set up Reshaper");
	glutReshapeFunc(Reshape);
	loading.Loading(70, "Init Keyboard");
	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	loading.Loading(80, "Init Mouse");
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	loading.Loading(90, "Init Other functions");
	glutIdleFunc(IdleFunc);
	loading.Loading(100, "End Glut Init");
	return succes;
}
bool LauncherInit(void)
{
	bool succes = true;
	loading.Loading(0, "Launcher Init");
	succes &= launcher.Init();
	loading.Loading(20, "Create Connection");
	succes &= launcher.ConnectToServer();
	loading.Loading(60, "Send test character...");
	succes &= launcher.SendTestCharacter(TEST_CHAR_CLIENT);
	loading.Loading((succes ? 60 : -1), (succes ? "Send!" : "Send char Failed!"));
	loading.Loading(70, "Recive test character...");
	succes &= launcher.ReciveTestCharacter();
	loading.Loading((succes ? 70 : -1), (succes ? "Recived!" : "Recive char Failed!"));
	loading.Loading(80, "Send test message...");
	succes &= launcher.SendTestMessage(TEST_STRING_CLIENT);
	loading.Loading((succes ? 80 : -1), (succes ? "Send!" : "Send string Failed!"));
	loading.Loading(90, "Recive test message...");
	succes &= launcher.ReciveTestMessage();
	loading.Loading((succes ? 90 : -1), (succes ? "Recived!" : "Recived string Failed!"));
	succes &= launcher.SendPlayerInfo();
	loading.Loading((succes ? 95 : -1), (succes ? "Send!" : "Send pos Failed!"));
	succes ? loading.Loading(100, "Launcher Init Succes") : loading.Loading(-1, "Launcher Init Failed");
	return succes;
}
void add(LevelBrick *peace){ levelPeaces->push_back(peace); }
void addBrick(double x, double y, double z, double w, double h, double d){ add(new LevelBrick(x, y, z, w, h, d)); }
void addBrick(double y, double z){ addBrick(XPOSITION, y, z, 1, 1, 1); }
bool FieldInit()
{
	bool succes = true;
	loading.Loading(0, "Start Field Init");
	width = 1280;
	height = 720;
	cameraAngle = 0;
	Sleep(100);
	loading.Loading(20, "Creating Johny");
	player = new Player(XPOSITION, 1, 0);
	Sleep(100);
	loading.Loading(40, "Creating World");
	Sleep(100);
	levelPeaces = new vector < LevelBrick* > ;
	addBrick(0, 0);
	addBrick(1, 1);
	addBrick(2, 2);
	addBrick(0, -1);
	addBrick(0, -2);

	loading.Loading(100, "End Field Init");
	return succes;
}
int End()
{
	cout << "Pixel world has been ended" << endl;
	string line;
	getline(cin, line);
	return 0;
}
int main(int argc, char* argv[])
{
	cout << "Pixel world has been started" << endl;
	bool succes = true;
	succes &= LauncherInit();
	succes &= (succes ? FieldInit() : false);
	//succes &= (succes?GlutInit(argc, argv):false);

	Sleep(2000);

	//glutMainLoop();

	return End();
}
void Reset()
{
	FieldInit();
}
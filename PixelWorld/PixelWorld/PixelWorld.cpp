#define JUMPING_VECT_Y 1

#include "GL\freeglut.h"
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <Windows.h>

#include "LoadingProcessor.h"
#include "LevelBrick.h"
#include "Player.h"
#include "cube.h"

using namespace std;

LoadingProcessor loading;

int width, height;
GLfloat lAmbient[] = { 0.7, 0.7, 0.7, 1.0 };
float cameraAngle;
vector<LevelBrick*> *levelPeaces;
Player *player;
bool p_move_left, p_move_right, p_jump, p_duk;
void checkKeys()
{
	if (p_jump)
	{
		cout << "Jump" << endl;
		p_jump = false;
		player->setJumping(true);
		player->setJumpAvailable(false);
		player->setVecY(player->getVecY() + JUMPING_VECT_Y);
	}
}
void updatePlayerPosition()
{
	if (player->isJumping())
	{
		// Gravity
		player->setVecY(player->getVecY() - 0.089);
	}
	player->setPosX(player->getPosX() + player->getVecX());
	player->setPosY(player->getPosY() + player->getVecY());
	player->setPosZ(player->getPosZ() + player->getVecZ());

	if (player->getPosY() <= 1)
	{
		player->setVecY(0);
		player->setPosY(1);
		player->setJumpAvailable(true);
		player->setJumping(false);
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
	gluLookAt(7 * cos(cameraAngle), 5, 7 * sin(cameraAngle), 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	glEnable(GL_DEPTH_TEST);


	DrawWorld();

	drawSpecial(player->getPosX(), player->getPosY(), player->getPosZ(), 0.5, 0.5, 0.5);


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
	::width = glwidth; ::height = glheight; glViewport(0, 0, width, height);
}
void KeyHandler(unsigned char key, int x, int y, bool pressed)
{
	switch (key)
	{
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

void GlutInit(int argc, char* argv[])
{
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
}
void FieldInit()
{
	loading.Loading(0, "Start Field Init");
	Sleep(100);
	loading.Loading(20, "Creating Johny");
	player = new Player(0, 1, 0);
	Sleep(100);
	loading.Loading(40, "Creating World");
	Sleep(100);
	levelPeaces = new vector < LevelBrick* > ;
	levelPeaces->push_back(new LevelBrick(0, 0, 0, 1, 1, 1));
	levelPeaces->push_back(new LevelBrick(0, 1, 1, 1, 1, 1));
	loading.Loading(100, "End Field Init");
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
	FieldInit();
	GlutInit(argc, argv);

	Sleep(2000);

	glutMainLoop();

	return End();
}
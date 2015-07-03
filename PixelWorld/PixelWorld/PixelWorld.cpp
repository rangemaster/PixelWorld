#include "GL\freeglut.h"
#include <iostream>
#include <istream>
#include <string>
#include <Windows.h>

#include "LoadingProcessor.h"

using namespace std;

LoadingProcessor loading;

int width, height;

void Display(){}
void Reshape(int glwidth, int glheight)
{ ::width = glwidth; ::height = glheight; glViewport(0, 0, width, height); }
void KeyPressed(unsigned char key, int x, int y){}
void KeyReleased(unsigned char key, int x, int y){}
void MouseButton(int button, int state, int x, int y){}
void MouseMotion(int x, int y){}
void IdleFunc(){}

void GlutInit(int argc, char* argv[])
{
	loading.Loading(0, "Start Glut Init");
	glutInit(&argc, argv);
	loading.Loading(10, "Creating play window");
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
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

	loading.Loading(20, "Creating Johny");

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

	glutMainLoop();

	return End();
}
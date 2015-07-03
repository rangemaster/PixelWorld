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
void Reshape(int glwidth, int glheight){ ::width = glwidth; ::height = glheight; glViewport(0, 0, width, height); }
void KeyPressed(unsigned char key, int x, int y){}
void KeyReleased(unsigned char key, int x, int y){}
void MouseButton(int button, int state, int x, int y){}
void MouseMotion(int x, int y){}
void IdleFunc(){}

void GlutInit(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Pixel World");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);
}
void FieldInit()
{
	cout << "Start Field Init" << endl;
	loading.SetPercentage(10);
	loading.PrintPercentage();
	loading.SetPercentage(50);
	loading.PrintPercentage();
	loading.SetPercentage(100);
	loading.PrintPercentage();

	cout << "End Field Init" << endl;
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
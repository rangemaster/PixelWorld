#include "Launcher.h"


Launcher::Launcher()
{
}


Launcher::~Launcher()
{
}
bool Launcher::Init()
{
	return true;
}
bool Launcher::ConnectToServer()
{
	cout << "Settings up connection" << endl;
	if (client.Connect("127.0.0.1", 8000) == 1)
	{
		cout << "Connection Failed" << endl;
		return false;
	}
	return true;
}

void Launcher::Draw(void){}
void Launcher::ButtonPressed(int ButtonIndex){}

bool Launcher::SendTestMessage(void)
{
	return false;
}
bool Launcher::ReciveTestMessage(void)
{
	return false;
}
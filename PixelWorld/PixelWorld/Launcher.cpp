#include "Launcher.h"

string testText = "Test Text For The Server";

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

bool Launcher::SendTestCharacter(char c)
{
	try{
		int len = 1;
		if (client.Send(&c, len, 0) == -1)
			return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
bool Launcher::ReciveTestCharacter(void)
{
	try
	{
		int len = 1;
		char c;
		if (client.Recive(&c, len, 0) == -1)
			return false;
		if (c == TEST_CHAR_SERVER)
			return true;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
bool Launcher::SendTestMessage(string c)
{
	string text = TEST_STRING_CLIENT;
	int textlength = text.length();
	char buf = (char)(textlength);
	if (client.Send(&buf, 1, 0) == -1)
		return false;
	//cout << "len to buf -> " << textlength << " = " << buf << endl;
	for (int i = 0; i < textlength; i++)
	{
		buf = text[i];
		if (client.Send(&buf, 1, 0) == -1)
			return false;
	}
	//cout << "Send: [" << text << "]" << endl;
	return true;
}
bool Launcher::ReciveTestMessage(void)
{
	string text = "";
	char buf;
	int len = 0;
	if (client.Recive(&buf, 1, 0) == -1)
		return false;
	len = (int)(buf);
	//cout << "Buf to len -> " << buf << " = " << len << endl;
	for (int i = 0; i < len; i++)
	{
		if (client.Recive(&buf, 1, 0) == -1)
			return false;
		text += buf;
	}
	//cout << "Message: [" << text << "]" << endl;
	if (text == TEST_STRING_SERVER)
		return true;
	return false;
}
bool Launcher::SendPlayerInfo(void)
{
	bool succes = true;
	Pos3D pos(1.12345, 2.23456, 3.34567);
	Vect3D vect(4.4, 5.5, 6.6);
	succes &= client.SendPosition(pos);
	succes &= client.SendVector(vect);
	return succes;
}
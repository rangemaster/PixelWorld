#include "Server.h"
Server::Server()
{
}
Server::~Server()
{
}
void Print(string message){ cout << message << endl; }

int Server::StartServer(int Port)
{
	Print("Start Server\n");
	int err = 0;
	WSAStartup(MAKEWORD(2, 2), &Data);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		Sleep(4000);
		exit(0);
		return 0;
	}
	i_sock.sin_family = AF_INET;
	i_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	i_sock.sin_port = htons(Port);
	Print("Wating for client trying to connect");
	err = bind(sock, (LPSOCKADDR)&i_sock, sizeof(i_sock));
	if (err != 0)
	{
		Print("NO SOCKET");
		return 0;
	}
	err = listen(sock, 2);
	if (err == SOCKET_ERROR)
	{
		Print("SOCKET ERROR");
		return 0;
	}
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (clients < 4)
			{
				int so2len = sizeof(i_sock2);
				sock2[clients] = accept(sock, (sockaddr *)&i_sock2, &so2len);
				if (sock2[clients] == INVALID_SOCKET)
				{
					Print("INVALID SOCKET");
					return 0;
				}
				std::stringstream ss;
				ss << "a client has joined the server(IP: " << i_sock2.sin_addr.s_addr << ")";
				Print(ss.str());
				bool succes = true;
				ss = std::stringstream();
				succes &= ReciveTestChar(clients);
				ss << (succes ? "[Succes]" : "[Failed]");
				succes &= SendTestChar(clients);
				ss << (succes ? "[Succes]" : "[Failed]");
				succes &= ReciveTestMessage(clients);
				ss << (succes ? "[Succes]" : "[Failed]");
				succes &= SendTestMessage(clients);
				ss << (succes ? "[Succes]" : "[Failed]");
				Print(ss.str());
				Pos3D pos;
				Vect3D vect;
				succes &= RecivePosition(clients, pos);
				succes &= ReciveVector(clients, vect);
				ss = std::stringstream();
				ss << "Pos: " << pos.x << ", " << pos.y << ", " << pos.z << endl;
				ss << "Vect: " << vect.x << ", " << vect.y << ", " << vect.z;
				Print(ss.str());
				clients++;
				continue;
			}
			else
			{
				break;
			}
		}
	}
	return 1;
}

bool Server::ReciveTestChar(int clientIndex)
{
	char buf;
	int len = 1;
	if (Recive(&buf, len, clientIndex) == -1)
		return false;
	if (buf != TEST_CHAR_CLIENT)
		return false;
	return true;
}
bool Server::SendTestChar(int clientIndex)
{
	char buf = TEST_CHAR_SERVER;
	if (Send(&buf, 1, clientIndex) == -1)
		return false;
	return true;
}
bool Server::ReciveTestMessage(int clientIndex)
{
	string text = "";
	char buf;
	int len = 0;
	if (Recive(&buf, 1, clientIndex) == -1)
		return false;
	len = (int)(buf);
	//cout << "Buf to len -> " << buf << " = " << len << endl;
	for (int i = 0; i < len; i++)
	{
		if (Recive(&buf, 1, clientIndex) == -1)
			return false;
		text += buf;
	}
	//cout << "Message: [" << text << "]" << endl;
	if (text == TEST_STRING_CLIENT)
		return true;
	return false;
}
bool Server::SendTestMessage(int clientIndex)
{
	string text = TEST_STRING_SERVER;
	int textlength = text.length();
	char buf = (char)(textlength);
	if (Send(&buf, 1, clientIndex) == -1)
		return false;
	//cout << "len to buf -> " << textlength << " = " << buf << endl;
	for (int i = 0; i < textlength; i++)
	{
		buf = text[i];
		if (Send(&buf, 1, clientIndex) == -1)
			return false;
	}
	//cout << "Send: [" << text << "]" << endl;
	return true;
}

int Server::Send(char *Buf, int len, int Client)
{
	int slen;
	slen = send(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		return -1;
	}
	return slen;
}
int Server::Recive(char *Buf, int len, int Client)
{
	int slen;
	slen = recv(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		return -1;
	}
	return slen;
}
void Server::SendPackage(void){}
void Server::RecivePackage(void)
{
	Package package;
	int value = Recive((char *)&package, sizeof(package), 0);
	cout << "Value: " << value << endl;
	cout << "Value 1: " << package.value1 << endl;
	cout << "Value 2: " << package.value2 << endl;
}
void Server::SendPackages()
{
	for (int i = 0; i < 4; i++)
	{
		Package package;
		Send((char *)&package, sizeof(package), i);
	}
}
void Server::RecivePackages()
{
	for (int i = 0; i < 4; i++)
	{
		Package package;
		int value = Recive((char *)&package, sizeof(package), i);
		cout << "Value: " << value << endl;
		cout << "Value 1: " << package.value1 << endl;
		cout << "Value 2: " << package.value2 << endl;
		cout << "Tekst: ";
		for (int k = 0; k < 4; k++)
			cout << package.string[k];
		cout << endl;
	}
}
bool Server::RecivePosition(int clientIndex, Pos3D &pos)
{
	return Recive3D(clientIndex, pos.x, pos.y, pos.z);
}
bool Server::ReciveVector(int clientIndex, Vect3D &vect)
{
	return Recive3D(clientIndex, vect.x, vect.y, vect.z);
}
bool Server::Recive3D(int clientIndex, double &x, double &y, double &z)
{
	char buf11, buf12, buf21, buf22, buf31, buf32;
	Recive(&buf11, 1, clientIndex);
	//Recive(&buf12, 1, clientIndex);
	Recive(&buf21, 1, clientIndex);
	//Recive(&buf22, 1, clientIndex);
	Recive(&buf31, 1, clientIndex);
	//Recive(&buf32, 1, clientIndex);
	x = (int)(buf11);
	y = (int)(buf21);
	z = (int)(buf31);
	return false;
}

int Server::EndSocket()
{
	closesocket(sock);
	WSACleanup();
	return 1;
}
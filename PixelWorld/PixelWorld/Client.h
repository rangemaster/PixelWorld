#ifndef Client_H
#define Client_H

#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <winsock.h>
#include <stdio.h>
#include "Packages.h"

using namespace std;

class Client
{
public:
	Client();
	~Client();
	int Connect(char *IP, int Port);
	int Send(char *Buf, int len, int Client);
	int Recive(char *Buf, int len, int Client);
	int SendPackage(Package *package);
	int RecivePackage(Package *package);
private:
	SOCKET sock;
	SOCKADDR_IN i_sock;
	WSADATA Data;
};
#endif
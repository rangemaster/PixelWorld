#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <stdio.h>
#include "Packages.h"

class Client
{
public:
	Client();
	~Client();
	int Connect(char *IP, int Port);
	int Send(char *Buf, int len, int Client);
	int Recive(char *Buf, int len, int Client);
	int SendPackage(MyPacket*);
	int RecivePackage(MyPacket*);
private:
	SOCKET sock;
	SOCKADDR_IN i_sock;
	WSADATA Data;
};


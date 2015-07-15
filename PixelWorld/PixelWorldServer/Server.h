#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include "Packages.h"

using namespace std;

class Server
{
public:
	Server();
	~Server();
	int StartServer(int Port);
	int Send(char *Buf, int len, int Client);
	int Recive(char *Buf, int len, int Client);
	bool ReciveTestChar(void);
	bool SendTestChar(void);
	bool ReciveTestMessage(void);
	bool SendTestMessage(void);
	void SendPackage(void);
	void RecivePackage(void);
	void SendPackages(void);
	void RecivePackages(void);
	int EndSocket();
private:
	SOCKET sock;
	SOCKET sock2[200];
	SOCKADDR_IN i_sock;
	SOCKADDR_IN i_sock2;
	WSADATA Data;
	int clients = 0;
};


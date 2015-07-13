#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <stdio.h>

class Server
{
public:
	Server();
	~Server();
	int StartServer(int Port);
	int Send(char *Buf, int len, int Client);
	int Recive(char *Buf, int len, int Client);
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


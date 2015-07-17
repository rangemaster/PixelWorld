#include "Client.h"

#include <iostream>
#include <string>
using namespace std;

Client::Client()
{
}


Client::~Client()
{
}
int Client::Connect(char *IP, int Port)
{
	WSAStartup(MAKEWORD(2, 2), &Data);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		return 1;
	}
	i_sock.sin_family = AF_INET;
	i_sock.sin_addr.s_addr = inet_addr(IP);
	i_sock.sin_port = htons(Port);
	int ss = connect(sock, (struct sockaddr *)&i_sock, sizeof(i_sock));
	if (ss != 0)
	{
		printf("Cannot connect\n");
		return 1;
	}
	printf("Succefully connected\n");
	return 0;
}

int Client::Send(char *Buf, int len, int Client)
{
	int slen = 0;
	slen = send(sock, Buf, len, Client);
	if (slen < 0)
	{
		return -1;
	}
	return slen;
}
int Client::Recive(char *Buf, int len, int Client)
{
	int slen = 0;
	slen = recv(sock, Buf, len, Client);
	if (slen < 0)
	{
		return -1;
	}
	return slen;
}
int Client::SendPackage(Package *package)
{
	return Send((char *)&package, sizeof(package), 1);
}
int Client::RecivePackage(Package *package)
{
	return Recive((char *)&package, sizeof(package), 1);
}
bool Client::SendPosition(Pos3D pos)
{
	return Send3D(pos.x, pos.y, pos.z);
}
bool Client::SendVector(Vect3D vect)
{
	return Send3D(vect.x, vect.y, vect.z);
}
bool Client::Send3D(double x, double y, double z)
{
	int value11, value12, value21, value22, value31, value32;
	char buf11, buf12, buf21, buf22, buf31, buf32;
	value11 = (int)(x);
	value12 = (int)(((double)x - (double)value11) * 100);
	value21 = (int)(y);
	value22 = (int)(((double)y - (double)value21) * 100);
	value31 = (int)(z);
	value32 = (int)(((double)z - (double)value31) * 100);
	buf11 = (char)(value11);
	buf12 = (char)(value12);
	buf21 = (char)(value21);
	buf22 = (char)(value22);
	buf31 = (char)(value31);
	buf32 = (char)(value32);
	if (Send(&buf11, 1, 0) == -1)
		return false;
	if (Send(&buf12, 1, 0) == -1)
		return false;
	if (Send(&buf21, 1, 0) == -1)
		return false;
	if (Send(&buf22, 1, 0) == -1)
		return false;
	if (Send(&buf31, 1, 0) == -1)
		return false;
	if (Send(&buf32, 1, 0) == -1)
		return false;
	return true;
}
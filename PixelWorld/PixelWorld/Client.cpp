#include "Client.h"


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
	int slen=0;
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
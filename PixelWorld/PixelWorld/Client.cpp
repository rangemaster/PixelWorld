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
		printf("Cannot connect");
		return 0;
	}
	printf("Succefully connected");
	return 1;
}

int Client::Send(char *Buf, int len, int Client)
{
	int slen;
	slen = send(sock, Buf, len, 0);
	if (slen < 0)
	{
		printf("cannot send data");
		return 1;
	}
	return slen;
}
int Client::Recive(char *Buf, int len, int Client)
{
	int slen;
	slen = recv(sock, Buf, len, 0);
	if (slen < 0)
	{
		printf("cannot recive data");
		return 1;
	}
	return slen;
}
int Client::SendPackage(MyPacket *package)
{
	return Send((char *)&package, sizeof(package), 1);
}
int Client::RecivePackage(MyPacket *package)
{
	return Recive((char *)&package, sizeof(package), 1);
}
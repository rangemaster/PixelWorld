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
				ss << "a client has joined the server(IP: " << i_sock2.sin_addr.s_addr << ")" << endl;
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


int Server::Send(char *Buf, int len, int Client)
{
	int slen;
	slen = send(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot send data !");
		return 1;
	}
	return slen;
}
int Server::Recive(char *Buf, int len, int Client)
{
	int slen;
	slen = recv(sock2[Client], Buf, len, 0);
	if (slen < 0)
	{
		printf("Cannot send data !");
		return 1;
	}
	return slen;
}
void Server::SendPackages()
{
	for (int i = 0; i < 4; i++)
	{
		MyPacket packet;
		Send((char *)&packet, sizeof(packet), i);
	}
}
void Server::RecivePackages()
{
	for (int i = 0; i < 4; i++)
	{
		MyPacket packet;
		Recive((char *)&packet, sizeof(packet), i);
	}
}

int Server::EndSocket()
{
	closesocket(sock);
	WSACleanup();
	return 1;
}
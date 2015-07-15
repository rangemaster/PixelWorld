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
				bool succes = true;
				succes &= ReciveTestChar();
				Print(succes ? "Char Recived Succesfully" : "Char Recived Unsuccesfully");
				succes &= SendTestChar();
				Print(succes ? "Char Send Succesfully" : "Char Send Unsuccesfully");
				succes &= ReciveTestMessage();
				Print(succes ? "String Recived Succesfully" : "String Recived Unsuccesfully");
				succes &= SendTestMessage();
				Print(succes ? "String Send Succesfully" : "String Send Unsuccesfully");
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

bool Server::ReciveTestChar(void)
{
	char buf;
	int len = 1;
	if (Recive(&buf, len, 0) == -1)
		return false;
	if (buf != TEST_CHAR_CLIENT)
		return false;
	return true;
}
bool Server::SendTestChar(void)
{
	char buf = TEST_CHAR_SERVER;
	if (Send(&buf, 1, 0) == -1)
		return false;
	return true;
}
bool Server::ReciveTestMessage(void)
{
	string text = "";
	char buf;
	int len = 0;
	if (Recive(&buf, 1, 0) == -1)
		return false;
	len = (int)(buf);
	//cout << "Buf to len -> " << buf << " = " << len << endl;
	for (int i = 0; i < len; i++)
	{
		if (Recive(&buf, 1, 0) == -1)
			return false;
		text += buf;
	}
	//cout << "Message: [" << text << "]" << endl;
	if (text == TEST_STRING_CLIENT)
		return true;
	return false;
}
bool Server::SendTestMessage(void)
{
	string text = TEST_STRING_SERVER;
	int textlength = text.length();
	char buf = (char)(textlength);
	if (Send(&buf, 1, 0) == -1)
		return false;
	//cout << "len to buf -> " << textlength << " = " << buf << endl;
	for (int i = 0; i < textlength; i++)
	{
		buf = text[i];
		if (Send(&buf, 1, 0) == -1)
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
			cout << package.mystring[k];
		cout << endl;
	}
}

int Server::EndSocket()
{
	closesocket(sock);
	WSACleanup();
	return 1;
}
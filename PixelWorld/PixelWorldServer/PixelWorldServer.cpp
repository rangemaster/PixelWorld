
#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>

#include "Server.h"


using namespace std;
Server server;

void initNetwork()
{
	server.StartServer(8000);
}
void init()
{
	cout << "Init" << endl;
	initNetwork();
}
int main()
{
	cout << "Server Started" << endl;
	init();

}
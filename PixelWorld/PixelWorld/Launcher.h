#pragma once
#include <iostream>
#include <string>
#include "Client.h"
#include "LoadingProcessor.h"

using namespace std;

class Launcher
{
public:
	Launcher();
	~Launcher();
	bool Init(void);
	bool ConnectToServer();
	void Draw(void);
	void ButtonPressed(int ButtonIndex);
	bool SendTestMessage(void);
	bool ReciveTestMessage(void);
private:
	Client client;
	//void Start(void);

};


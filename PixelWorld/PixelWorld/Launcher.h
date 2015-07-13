#pragma once
#include "Client.h"

class Launcher
{
public:
	Launcher();
	~Launcher();
	void Init(void);
	int ConnectToServer(void);
	void Draw(void);
	void ButtonPressed(int ButtonIndex);
private:
	Client client;
	void Start(void);

};


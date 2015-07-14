#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class LoadingProcessor{
public:
	LoadingProcessor(void);
	~LoadingProcessor(void);
	void IncIndex(void);
	void SetIndex(int value);
	void SetPercentage(int value);
	void PrintPercentage(void);
	void Loading(int percentage, std::string feedback);
private:
	int percentage, index;
	void Message(string message, int color);
};
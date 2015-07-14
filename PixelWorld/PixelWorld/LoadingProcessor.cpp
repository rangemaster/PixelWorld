#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include "LoadingProcessor.h"


using namespace std;


LoadingProcessor::LoadingProcessor()
{
	percentage = 0;
	index = 0;
}
LoadingProcessor::~LoadingProcessor()
{

}
void LoadingProcessor::IncIndex(){ index = ++index % 3; }
void LoadingProcessor::SetIndex(int value){ index = 0; }
void LoadingProcessor::SetPercentage(int value){ percentage = value; }

void LoadingProcessor::PrintPercentage()
{
	cout << "Loading" << (index == 0 ? ".  " : index == 1 ? ".. " : "...") << std::setw(5) << percentage << "%" << endl;
	IncIndex();
}
void LoadingProcessor::Loading(int percentage, std::string feedback)
{
	int color = 7;
	std::stringstream ss;
	if (percentage >= 100)
	{
		color = 2;
		cout << "Loading" << (index == 0 ? ".  " : index == 1 ? ".. " : "...") << std::setw(5) << percentage << "%" << std::setw(30) << feedback;
	}
	else if (percentage <= -1)
	{
		color = 4;
		ss << "Loading Failed --- " << feedback ;
	}
	else
	{
		ss << "Loading" << (index == 0 ? ".  " : index == 1 ? ".. " : "...") << std::setw(5) << percentage << "%" << std::setw(30) << feedback;
	}
	Message(ss.str(), color);
	IncIndex();
}
void LoadingProcessor::Message(string message, int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << message << endl;
	SetConsoleTextAttribute(hConsole, 7);
}
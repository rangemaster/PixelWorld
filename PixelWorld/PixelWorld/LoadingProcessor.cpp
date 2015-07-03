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
	if (percentage >= 100)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);
		cout << "Loading" << (index == 0 ? ".  " : index == 1 ? ".. " : "...") << std::setw(5) << percentage << "%" << std::setw(30) << feedback << endl;
		SetConsoleTextAttribute(hConsole, 7);
	}
	else
		cout << "Loading" << (index == 0 ? ".  " : index == 1 ? ".. " : "...") << std::setw(5) << percentage << "%" << std::setw(30) << feedback << endl;
	IncIndex();
}
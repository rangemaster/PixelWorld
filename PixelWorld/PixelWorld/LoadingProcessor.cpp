#include <iostream>
#include <string>
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
void LoadingProcessor::SetPercentage(int value)
{
	percentage = value;
}
void LoadingProcessor::PrintPercentage()
{
	cout << "Loading" << (index == 0 ? "." : index == 1 ? ".." : "...") << percentage << "%" << endl;
	index = index++ % 3;
}
void LoadingProcessor::Loading(int percentage, std::string feedback)
{

}
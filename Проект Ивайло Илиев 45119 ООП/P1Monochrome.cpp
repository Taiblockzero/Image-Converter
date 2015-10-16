#include"P1Monochrome.h"


P1Monochrome::P1Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P1Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P1Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P1");
	drawHistogram(colors, "P1");
}
#include"P2Monochrome.h"


P2Monochrome::P2Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P2Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P2Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P2");
	drawHistogram(colors, "P2");
}
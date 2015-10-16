#include"P6Monochrome.h"


P6Monochrome::P6Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P6Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P6Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P6");
	drawHistogram(colors, "P6");
}
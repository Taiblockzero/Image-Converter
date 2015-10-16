#include"P5Monochrome.h"

P5Monochrome::P5Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P5Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P5Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P5");
	drawHistogram(colors, "P5");
}
#include"P3Monochrome.h"


P3Monochrome::P3Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P3Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P3Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P3");
	drawHistogram(colors, "P3");
}
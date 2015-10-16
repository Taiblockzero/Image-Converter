#include"P4Monochrome.h"


P4Monochrome::P4Monochrome(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P4Monochrome::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P4Monochrome::createHistogram()
{
	int* colors = readPixelsIntoArray("P4");
	drawHistogram(colors, "P4");
}
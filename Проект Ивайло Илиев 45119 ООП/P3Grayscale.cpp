#include"P3Grayscale.h"


P3Grayscale::P3Grayscale(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P3Grayscale::convertToMonochrome()
{
	fstream image(fileName);
	skipHeader(image);

	int amountOfPixelsInImage = 0;
	int num;
	for (; false == image.eof(); amountOfPixelsInImage++)
	{
		image >> num;
		image >> num;
		image >> num;
	}

	image.clear();
	image.seekg(0);
	skipHeader(image);

	int numToCheck;
	int* blackAndWhitePixelValues = new int[amountOfPixelsInImage];

	for (int i = 0; i < amountOfPixelsInImage; i++)
	{
		image >> numToCheck;
		image >> numToCheck;
		image >> numToCheck;
		if (numToCheck <= maxValue / 2)
			blackAndWhitePixelValues[i] = 0;
		else
			blackAndWhitePixelValues[i] = maxValue;
	}

	image.close();

	ifstream imageOriginal(fileName);
	ofstream imageCopy(fileCopyName);

	copyHeader(imageCopy, imageOriginal);

	imageOriginal.close();

	for (int i = 0; i < amountOfPixelsInImage; i++)
	{
		imageCopy << blackAndWhitePixelValues[i] << ' '; //R
		imageCopy << blackAndWhitePixelValues[i] << ' '; //G
		imageCopy << blackAndWhitePixelValues[i] << ' '; //B
	}
	imageCopy.close();
	delete[] blackAndWhitePixelValues;
}

void P3Grayscale::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P3Grayscale::createHistogram()
{
	int* colors = readPixelsIntoArray("P3");
	drawHistogram(colors, "P3");
}
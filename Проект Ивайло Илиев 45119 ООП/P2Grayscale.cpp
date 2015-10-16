#include"P2Grayscale.h"


P2Grayscale::P2Grayscale(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P2Grayscale::convertToMonochrome()
{
	fstream image(fileName);
	skipHeader(image);

	int amountOfPixelsInImage = 0;
	int num;
	for (; false == image.eof(); amountOfPixelsInImage++)
	{
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
		imageCopy << blackAndWhitePixelValues[i] << ' ';
	}
	imageCopy.close();
	delete[] blackAndWhitePixelValues;
}

void P2Grayscale::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P2Grayscale::createHistogram()
{
	int* colors = readPixelsIntoArray("P2");
	drawHistogram(colors, "P2");
}
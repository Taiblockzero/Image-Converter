#include"P5Grayscale.h"


P5Grayscale::P5Grayscale(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}

void P5Grayscale::convertToMonochrome()
{
	fstream image(fileName, ios::binary | ios::in | ios::out);
	if (!image)
	{
		cout << "error opening image in convertToMonochrome" << endl;
		return;
	}
	skipHeader(image);

	int amountOfPixelsInImage = 0;
	unsigned char num[1];
	unsigned char* numP = &num[0];

	for (; false == image.eof(); amountOfPixelsInImage++)
	{
		image.read((char*)numP, 1);
	}

	image.clear();
	image.seekg(0);
	skipHeader(image);

	unsigned char numToCheck[1];
	unsigned char* numToCheckPointer = &numToCheck[0];
	unsigned char* blackAndWhitePixelValues;
	try
	{
		blackAndWhitePixelValues = new unsigned char[amountOfPixelsInImage];
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
		return;
	}
	

	for (int i = 0; i < amountOfPixelsInImage; i++)
	{
		image.read((char*)numToCheckPointer, 1);
		if (numToCheck[0] <= maxValue / 2)
			blackAndWhitePixelValues[i] = 0;
		else
			blackAndWhitePixelValues[i] = maxValue;
	}

	image.close();

	ifstream imageOriginal(fileName, ios::binary);
	ofstream imageCopy(fileCopyName, ios::binary);

	copyHeader(imageCopy, imageOriginal);

	imageOriginal.close();

	imageCopy.write((char*)blackAndWhitePixelValues, amountOfPixelsInImage);
	imageCopy.close();
	delete[] blackAndWhitePixelValues;
}

void P5Grayscale::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P5Grayscale::createHistogram()
{
	int* colors = readPixelsIntoArray("P5");
	drawHistogram(colors, "P5");
}
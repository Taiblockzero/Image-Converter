#include"P6Colorful.h"


P6Colorful::P6Colorful(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}
P6Colorful::~P6Colorful(){}
void P6Colorful::convertToGrayscale()
{
	if (fileCopyName == NULL)
	{
		cout << "you must use setCopyName() before using convertToGrayscale()!" << endl;
		return;
	}

	setWidthAndHeight();
	
	fstream image(fileName, ios::binary | ios::in | ios::out);
	if (!image)
	{
		cout << "error in opening image 1" << endl;
	}
	skipHeaderInBinary(image);
	

	int amountOfPixelsInImage = 0;
	unsigned char num[2];
	unsigned char* numP = &num[0];
	for (; false == image.eof(); amountOfPixelsInImage++)
	{
		image.read((char*)numP, 1);
		image.read((char*)numP, 1);
		image.read((char*)numP, 1);
	}
	amountOfPixelsInImage--;

	image.clear();
	image.seekg(0);
	skipHeaderInBinary(image);

	unsigned char numbersToCheck[4];
	unsigned char* numbersToCheckPointer = &numbersToCheck[0];
	unsigned char* grayPixelValues;
	try
	{
		grayPixelValues = new unsigned char[amountOfPixelsInImage];
	}
	catch (exception& e)
	{
		cout << "Standard exception: " << e.what() << endl;
		return;
	}
	for (int i = 0, average; i < amountOfPixelsInImage; i++)
	{
		image.read((char*)numbersToCheckPointer, 3);

		average = (numbersToCheck[0] + numbersToCheck[1] + numbersToCheck[2]) / 3;
		grayPixelValues[i] = average;
	}

	image.close();

	ifstream imageOriginal(fileName, ios::binary);
	if (!imageOriginal)
	{
		cout << "error opening image 2" << endl;
	}
	ofstream imageCopy(fileCopyName, ios::binary | ios::out);
	if (!imageCopy)
	{
		cout << "error opening image 3" << endl;
	}
	copyHeaderInBinary(imageCopy, imageOriginal);

	imageOriginal.close();




	unsigned char* grayPixelValuesCopy = grayPixelValues;
	for (int i = 0; i < amountOfPixelsInImage; i++, grayPixelValuesCopy++)
	{
		imageCopy.write((char*)grayPixelValuesCopy, 1); //R
		imageCopy.write((char*)grayPixelValuesCopy, 1); //G
		imageCopy.write((char*)grayPixelValuesCopy, 1); //B
	}
	imageCopy.close();
	delete[] grayPixelValues;
}
void P6Colorful::convertToMonochrome()
{
	convertToGrayscale();
	fstream image(fileCopyName, ios::binary | ios::in | ios::out);
	skipHeaderInBinary(image);

	int amountOfPixelsInImage = 0;
	unsigned char num[1];
	unsigned char* numP = &num[0];

	for (; false == image.eof(); amountOfPixelsInImage++)
	{
		image.read((char*)numP, 1);
		image.read((char*)numP, 1);
		image.read((char*)numP, 1);
	}
	amountOfPixelsInImage--;


	image.clear();
	image.seekg(0);
	skipHeaderInBinary(image);

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
		image.read((char*)numToCheckPointer, 1);
		image.read((char*)numToCheckPointer, 1);
		if (numToCheck[0] <= maxValue / 2)
			blackAndWhitePixelValues[i] = 0;
		else
			blackAndWhitePixelValues[i] = maxValue;
	}
	int positionAfterMaxValue = getPositionAfterHeader(image);
	image.seekp(positionAfterMaxValue);

	unsigned char* blackAndWhitePixelValuesPointer = &blackAndWhitePixelValues[0];
	for (int i = 0; i < amountOfPixelsInImage; i++, blackAndWhitePixelValuesPointer++)
	{
		image.write((char*)blackAndWhitePixelValuesPointer, 1);
		image.write((char*)blackAndWhitePixelValuesPointer, 1);
		image.write((char*)blackAndWhitePixelValuesPointer, 1);
	}
	image.close();
	delete[] blackAndWhitePixelValues;
}

void P6Colorful::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P6Colorful::createHistogram()
{
	int* colors = readPixelsIntoArray("P6");
	drawHistogram(colors, "P6");
}
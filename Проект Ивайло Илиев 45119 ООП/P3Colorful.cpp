#include"P3Colorful.h"



P3Colorful::P3Colorful(char* fileName, char* command, int maxValue)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	this->maxValue = maxValue;
	this->coefficient = 255 / maxValue;
}
P3Colorful::~P3Colorful(){}
void P3Colorful::convertToGrayscale()
{
	if (fileCopyName == NULL)
	{
		cout << "you must use setCopyName() before using convertToGrayscale()!" << endl;
		return;
	}

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
	amountOfPixelsInImage--;
	image.clear();
	image.seekg(0);
	skipHeader(image);

	int numToCheck1, numToCheck2, numToCheck3;
	int* grayPixelValues = new int[amountOfPixelsInImage];

	for (int i = 0, average; i < amountOfPixelsInImage; i++)
	{
		image >> numToCheck1;
		image >> numToCheck2;
		image >> numToCheck3;

		average = (numToCheck1 + numToCheck2 + numToCheck3) / 3;
		grayPixelValues[i] = average;
	}

	image.close();

	ifstream imageOriginal(fileName);
	ofstream imageCopy(fileCopyName);
	copyHeader(imageCopy, imageOriginal);

	imageOriginal.close();

	for (int i = 0; i < amountOfPixelsInImage; i++)
	{
		imageCopy << grayPixelValues[i] << ' '; //R
		imageCopy << grayPixelValues[i] << ' '; //G
		imageCopy << grayPixelValues[i] << ' '; //B
	}



	imageCopy.close();
	delete[] grayPixelValues;
}
void P3Colorful::convertToMonochrome()
{
	convertToGrayscale();
	fstream image(fileCopyName);
	if (!image)
	{
		cout << "error in opening image for convertToMonochrome()" << endl;
		return;
	}
	skipHeader(image);

	int amountOfPixelsInImage = 0;
	int num;
	for (; false == image.eof(); amountOfPixelsInImage++)
	{
		image >> num;
		image >> num;
		image >> num;
	}
	amountOfPixelsInImage--;

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

	int positionAfterMaxValue = getPositionAfterHeader(image);
	image.seekp(positionAfterMaxValue);


	for (int i = 0; i < amountOfPixelsInImage; i++)
	{
		image << blackAndWhitePixelValues[i] << ' '; //R
		image << blackAndWhitePixelValues[i] << ' '; //G
		image << blackAndWhitePixelValues[i] << ' '; //B
	}
	image.close();
	delete[] blackAndWhitePixelValues;
}

void P3Colorful::setCopyName()
{
	::setCopyName(fileName, fileCopyName, command);
}

void P3Colorful::createHistogram()
{
	int* colors = readPixelsIntoArray("P3");
	drawHistogram(colors, "P3");
}
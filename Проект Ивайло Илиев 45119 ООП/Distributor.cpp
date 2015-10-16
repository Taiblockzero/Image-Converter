#include"Distributor.h"
#include<iostream>
#include<fstream>

#include"ImageType.h"
#include"P3Colorful.h"
#include"P3Grayscale.h"
#include"P3Monochrome.h"
#include"P6Colorful.h"
#include"P6Grayscale.h"
#include"P6Monochrome.h"
#include"P2Grayscale.h"
#include"P2Monochrome.h"
#include"P5Grayscale.h"
#include"P5Monochrome.h"
#include"P1Monochrome.h"
#include"P4Monochrome.h"



Distributor::Distributor(char* fileName, char* command)
{
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);

	this->command = new char[strlen(command) + 1];
	strcpy(this->command, command);

	imageType = NULL;
	maxValue = 0;

	setHeader();
	setMaxValue();
	setImageType();
}
Distributor::~Distributor()
{
	delete[] fileName;
	delete[] command;
	delete[] imageType;
}
void Distributor::setHeader()
{
	ifstream image(fileName);
	if (!image)
	{
		cout << "error opening image for setHeader()" << endl;
		return;
	}
	image.get(header, 3);
	image.close();
}
void Distributor::setImageType()
{
	if (NULL == header)
	{
		cout << "You must use setHeader before using setImageType!!!" << endl;
		return;
	}
	if (0 == strcmp(header, "P3"))
	{
		if (true == isP3ImageMonochrome())
		{
			delete[] imageType;
			imageType = new char[strlen("P3Monochrome") + 1];
			strcpy(imageType, "P3Monochrome");
		}
		else if (true == isP3ImageGrayscale())
		{
			delete[] imageType;
			imageType = new char[strlen("P3Grayscale") + 1];
			strcpy(imageType, "P3Grayscale");
		}
		else //ostava da e P3Colorful 
		{
			delete[] imageType;
			imageType = new char[strlen("P3Colorful") + 1];
			strcpy(imageType, "P3Colorful");


		}
	}
	else if (0 == strcmp(header, "P6"))
	{
		if (true == isP6ImageMonochrome())
		{
			delete[] imageType;
			imageType = new char[strlen("P6Monochrome") + 1];
			strcpy(imageType, "P6Monochrome");
		}
		else if (true == isP6ImageGrayscale())
		{
			delete[] imageType;
			imageType = new char[strlen("P6Grayscale") + 1];
			strcpy(imageType, "P6Grayscale");
		}
		else //Ostava da e P6Colorful
		{
			delete[] imageType;
			imageType = new char[strlen("P6Colorful") + 1];
			strcpy(imageType, "P6Colorful");
		}

	}
	else if (0 == strcmp(header, "P2"))
	{
		if (true == isP2ImageMonochrome())
		{
			delete[] imageType;
			imageType = new char[strlen("P2Monochrome") + 1];
			strcpy(imageType, "P2Monochrome");
		}
		else //Ostava da e P2Grayscale
		{
			delete[] imageType;
			imageType = new char[strlen("P2Grayscale") + 1];
			strcpy(imageType, "P2Grayscale");
		}
	}
	else if (0 == strcmp(header, "P5"))
	{
		if (true == isP5ImageMonochrome())
		{
			delete[] imageType;
			imageType = new char[strlen("P5Monochrome") + 1];
			strcpy(imageType, "P5Monochrome");
		}
		else //Ostava da e P5Grayscale
		{
			delete[] imageType;
			imageType = new char[strlen("P5Grayscale") + 1];
			strcpy(imageType, "P5Grayscale");
		}
	}
	else if (0 == strcmp(header, "P1"))
	{
		delete[] imageType;
		imageType = new char[strlen("P1Monochrome") + 1];
		strcpy(imageType, "P1Monochrome");
	}
	else if (0 == strcmp(header, "P4"))
	{
		delete[] imageType;
		imageType = new char[strlen("P4Monochrome") + 1];
		strcpy(imageType, "P4Monochrome");
	}
}
void Distributor::passFileNameAndCommandToProperClass()
{
	if (0 == strcmp(imageType, "P3Monochrome"))
	{
		P3Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}
	else if (0 == strcmp(imageType, "P3Grayscale"))
	{
		P3Grayscale image(fileName, command, maxValue);
		if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P3Colorful"))
	{
		P3Colorful image(fileName, command, maxValue);
		if (0 == strcmp(command, "--grayscale"))
		{
			image.setCopyName();
			image.convertToGrayscale();
		}
		else if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
				|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P6Monochrome"))
	{
		P6Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green") 
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P6Grayscale"))
	{
		P6Grayscale image(fileName, command, maxValue);
		if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P6Colorful"))
	{
		P6Colorful image(fileName, command, maxValue);
		if (0 == strcmp(command, "--grayscale"))
		{
			image.setWidthAndHeight();
			image.setCopyName();
			image.convertToGrayscale();
		}
		else if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P2Monochrome"))
	{
		P2Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P2Grayscale"))
	{
		P2Grayscale image(fileName, command, maxValue);
		if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P5Monochrome"))
	{
		P5Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P5Grayscale"))
	{
		P5Grayscale image(fileName, command, maxValue);
		if (0 == strcmp(command, "--monochrome"))
		{
			image.setCopyName();
			image.convertToMonochrome();
		}
		else if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P1Monochrome"))
	{
		maxValue = 1;
		P1Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}

	else if (0 == strcmp(imageType, "P4Monochrome"))
	{
		maxValue = 1;
		P4Monochrome image(fileName, command, maxValue);
		if ((0 == strcmp(command, "--histogram=red")) || 0 == strcmp(command, "--histogram=green")
			|| 0 == strcmp(command, "--histogram=blue"))
		{
			image.setCopyName();
			image.createHistogram();
		}
	}


}
void Distributor::setMaxValue()
{
	ifstream image(fileName);
	if (!image)
	{
		cout << "error opening image in setMaxValue()" << endl;
		return;
	}
	char line[COMMENT_LENGTH];
	image.getline(line, COMMENT_LENGTH);//preskacham purvi red
	

	/*char line[COMMENT_LENGTH];
	image.get(c);
	for (; c == '#'; image.get(c))
	image.getline(line, COMMENT_LENGTH);
	image.seekg(-1, ios::cur);*/
	char c;
	image.get(c);
	while (c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	

	int skippedNumber;
	image >> skippedNumber; //preskacham width
	image >> skippedNumber; //preskacham heigth
	image >> maxValue;

	image.close();
}
bool Distributor::isP3ImageMonochrome()
{
	ifstream image(fileName);
	if (!image)
	{
		cout << "error in opening image for isP3ImageMonochrome" << endl;
		image.close();
		return false;
	}
	if (0 == maxValue)
	{
		cout << "Please use setMaxValue() before using isP3ImageMonochrome()!" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	int numToCheck;
	while (false == image.eof()) //proverka za razlichni chisla ot 0 i maxvalue
	{
		image >> numToCheck;
		if (numToCheck != 0 && numToCheck != maxValue)
		{
			image.close();
			return false;
		}
	}

	image.clear();
	image.seekg(0);
	skipHeader(image);

	int numToCheck1, numToCheck2, numToCheck3;
	while (false == image.eof()) //proverka za 255 0 0, 0 255 0 i 0 0 255
	{
		image >> numToCheck1;
		image >> numToCheck2;
		image >> numToCheck3;

		if (numToCheck1 != numToCheck2 || numToCheck2 != numToCheck3)
		{
			image.close();
			return false;
		}
	}
	image.close();
	return true;
}
bool Distributor::isP3ImageGrayscale()
{
	ifstream image(fileName);
	if (!image)
	{
		cout << "error in opening image for isP3ImageGrayscale()" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	int numToCheck1, numToCheck2, numToCheck3;
	while (false == image.eof())
	{
		image >> numToCheck1;
		image >> numToCheck2;
		image >> numToCheck3;

		if (numToCheck1 != numToCheck2 || numToCheck2 != numToCheck3)
		{
			image.close();
			return false;
		}
	}
	image.close();
	return true;
}
bool Distributor::isP2ImageMonochrome()
{
	ifstream image(fileName);
	if (!image)
	{
		cout << "error in opening image for isP2ImageMonochrome()" << endl;
		image.close();
		return false;
	}
	if (0 == maxValue)
	{
		cout << "Please use setMaxValue() before using isP2ImageMonochrome()!" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	int numToCheck;
	while (false == image.eof())
	{
		image >> numToCheck;
		if (numToCheck != 0 && numToCheck != maxValue)
		{
			image.close();
			return false;
		}
	}
	image.close();
	return true;
}
bool Distributor::isP6ImageMonochrome()
{
	ifstream image(fileName, ios::binary);
	if (!image)
	{
		cout << "error in opening image for isP6ImageMonochrome()" << endl;
		image.close();
		return false;
	}
	if (0 == maxValue)
	{
		cout << "Please use setMaxValue() before using isP6ImageMonochrome()!" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	unsigned char numToCheck[1];
	while (false == image.eof())
	{
		image.read((char*)numToCheck, 1); //
		if (numToCheck[0] != 0 && numToCheck[0] != maxValue)
		{
			image.close();
			return false;
		}
	}

	image.clear();
	image.seekg(0);
	skipHeader(image);

	unsigned char numToCheck1[1], numToCheck2[1], numToCheck3[1];
	while (false == image.eof()) 
	{
		image.read((char*)numToCheck1, 1);
		image.read((char*)numToCheck2, 1);
		image.read((char*)numToCheck3, 1);

		if (numToCheck1 != numToCheck2 || numToCheck2 != numToCheck3) //proverqva vsqka troika komponenti na piksela dali sa ravni pomejdu si
		{
			image.close();
			return false;
		}
	}

	image.close();
	return true;
}
bool Distributor::isP6ImageGrayscale()
{
	ifstream image(fileName, ios::binary);
	if (!image)
	{
		cout << "error in opening image for isP6ImageMonochrome()" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	unsigned char numToCheck1[1], numToCheck2[1], numToCheck3[1];
	while (false == image.eof()) 
	{
		image.read((char*)numToCheck1, 1);
		image.read((char*)numToCheck2, 1);
		image.read((char*)numToCheck3, 1);

		if (numToCheck1 != numToCheck2 || numToCheck2 != numToCheck3) //proverqva vsqka troika komponenti na piksela dali sa ravni pomejdu si
		{
			image.close();
			return false;
		}
	}

	image.close();
	return true;
}
bool Distributor::isP5ImageMonochrome()
{
	ifstream image(fileName, ios::binary);
	if (!image)
	{
		cout << "error in opening image for isP5ImageMonochrome()" << endl;
		image.close();
		return false;
	}
	if (0 == maxValue)
	{
		cout << "Please use setMaxValue() before using isP5ImageMonochrome()!" << endl;
		image.close();
		return false;
	}

	skipHeader(image);

	unsigned char numToCheck[1];
	while (false == image.eof())
	{
		image.read((char*)numToCheck, 1); //proverqva vseki pixel dali e 0 ili 255
		if (numToCheck[0] != 0 && numToCheck[0] != maxValue)
		{
			image.close();
			return false;
		}
	}
	image.close();
	return true;
}
void Distributor::skipHeader(ifstream& image)
{
	char c;
	char line[COMMENT_LENGTH];
	image.getline(line, COMMENT_LENGTH);//preskacham purvi red
		
	image.get(c);
	while (c == '#') //preskacham komentarite
	{
		image.getline(line, COMMENT_LENGTH);
		image.get(c);
	}
	image.unget();

	int skippedNumber;
	image >> skippedNumber; //preskacham width
	image >> skippedNumber; //preskacham heigth
	image >> skippedNumber; //preskacham maxValue
}

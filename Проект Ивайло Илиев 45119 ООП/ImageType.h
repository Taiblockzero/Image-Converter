#pragma once

#include<fstream>
#include<iostream>
#include<exception>
#include"setCopyName.h"
using namespace std;

const int COMMENT_LENGTH = 71;

class ImageType
{
protected:
	char* fileName;
	char* command;
	char* fileCopyName;
	int maxValue;
	double coefficient; //when you multiply maxValue by this coefficient, you get 255
	int width;
	int height;
public:
	ImageType();
	virtual ~ImageType();
public:
	virtual void convertToGrayscale() = 0;
	virtual void convertToMonochrome() = 0;
	virtual void createHistogram() = 0;
	virtual void setCopyName() = 0; 
	//virtual void copyFile() = 0;
public:
	void copyHeader(ofstream& imageDestination, ifstream& imageSource);
	void copyHeaderInBinary(ofstream& imageDestination, ifstream& imageSource);
	void skipHeader(fstream& image);
	void skipHeaderInPBM(fstream& image);
	void skipHeaderInBinary(fstream& image); //ne sum siguren dali ima izobshto nqkakuv smisul tazi funkciq da ima binary variant sushto
	int getPositionAfterHeader(fstream& image);
	void setWidthAndHeight();
public:
	int* readPixelsIntoArray(char* header); //arr is array of color percents
	void drawHistogram(int* arr, char* header);
	void drawHeader(fstream& image);
	void drawHeaderBinary(fstream& image); //check to see if it works okay with "image << something"
	void drawPixmap(fstream& image, int* arr);
	void drawPixmapBinary(fstream& image, int* arr);
};

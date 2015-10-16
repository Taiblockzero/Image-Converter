#pragma once
#include"P3Image.h"


class P3Colorful : public P3Image
{
public:
	P3Colorful(char* fileName, char* command, int maxValue);
	~P3Colorful();
public:
	virtual void convertToGrayscale();
	virtual void convertToMonochrome();
	virtual void createHistogram();
	//virtual void copyFile();
	virtual void setCopyName();
	//void copyHeader(ofstream& imageDestination, ifstream& imageSource);
};
